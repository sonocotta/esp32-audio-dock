#pragma once

#include "AudioFileSourceBuffer.h"
#ifdef BOARD_HAS_PSRAM
#define AudioFileSourceBufferSize (1024 * 1024)
#else
#define AudioFileSourceBufferSize (4096)
#endif

#include "AudioFileSourceICYStream.h"
#include "AudioGeneratorMP3.h"
#include <AudioOutputI2S.h>
#include "AudioOutputMixer.h"

#include "playlist.hpp"
extern Playlist playlist;

enum PlayerState
{
  STOP,
  PLAY,
  PAUSE,
};

static int lastms = 0;

class Player
{
private:
  static inline const char *TAG = "PLAYER";

  AudioFileSourceICYStream *file;
  AudioFileSourceBuffer *buff;
  AudioGeneratorMP3 *mp3;
  AudioOutputI2S out;

  // Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
  static void mdCallback(void *cbData, const char *type, bool isUnicode, const char *string)
  {
    const char *ptr = reinterpret_cast<const char *>(cbData);
    (void)isUnicode; // Punt this ball for now
    // Note that the type and string may be in PROGMEM, so copy them to RAM for printf
    char s1[32], s2[64];
    strncpy_P(s1, type, sizeof(s1));
    s1[sizeof(s1) - 1] = 0;
    strncpy_P(s2, string, sizeof(s2));
    s2[sizeof(s2) - 1] = 0;
    ESP_LOGD(TAG, "METADATA(%s) '%s' = '%s'", ptr, s1, s2);
  }

  // Called when there's a warning or error (like a buffer underflow or decode hiccup)
  static void statusCallback(void *cbData, int code, const char *string)
  {
    const char *ptr = reinterpret_cast<const char *>(cbData);
    // Note that the string may be in PROGMEM, so copy it to RAM for printf
    char s1[64];
    strncpy_P(s1, string, sizeof(s1));
    s1[sizeof(s1) - 1] = 0;
    ESP_LOGD(TAG, "STATUS(%s) '%d' = '%s'", ptr, code, s1);
  }

public:
  volatile PlayerState state = STOP;

  int seq = 0;
  bool isLooped = false;

  esp_err_t init()
  {
#ifdef ESP32
    ESP_LOGI(TAG, "Setting I2S pins: clk = %d, ws = %d, data = %d\n", PIN_I2S_SCK, PIN_I2S_FS, PIN_I2S_SD);
    if (!out.SetPinout(PIN_I2S_SCK, PIN_I2S_FS, PIN_I2S_SD))
    {
      ESP_LOGE(TAG, "Failed to set pinout");
      return ESP_FAIL;
    }
#endif
    audioLogger = &Serial;
    out.begin();

    return ESP_OK;
  }

  esp_err_t play()
  {

    PlaylistEntry entry = playlist.entries[seq % playlist.entriesCount];

    switch (state)
    {
    case PAUSE:
      return resume();
    case PLAY:
      ESP_LOGD(TAG, "Player is already playing");
      return ESP_OK;
    case STOP:
      ESP_LOGI(TAG, "Start playing '%s' : '%s'", entry.title.c_str(), entry.url.c_str());

      file = new AudioFileSourceICYStream(entry.url.c_str());
      file->RegisterMetadataCB(Player::mdCallback, (void *)"ICY");

#ifdef BOARD_HAS_PSRAM
      uint8_t *spiBuffer = (uint8_t *)ps_malloc(AudioFileSourceBufferSize);
      buff = new AudioFileSourceBuffer(file, spiBuffer, AudioFileSourceBufferSize);
#else
      buff = new AudioFileSourceBuffer(file, AudioFileSourceBufferSize);
#endif

      buff->RegisterStatusCB(Player::statusCallback, (void *)"buffer");

      mp3 = new AudioGeneratorMP3();
      // mp3->RegisterStatusCB(Player::statusCallback, (void *)"mp3");
      mp3->begin(buff, &out);

      state = PLAY;
      return ESP_OK;
    }
    return ESP_FAIL;
  }

  esp_err_t stop()
  {
    switch (state)
    {
    case STOP:
      ESP_LOGD(TAG, "Player is already stopped");
      return ESP_OK;
    case PAUSE:
    case PLAY:

      state = STOP;

      if (buff)
      {
        buff->close();
        delete buff;
      }

      if (mp3)
      {
        mp3->stop();
        delete mp3;
      }

      if (file)
      {
        file->close();
        delete file;
      }
      return ESP_OK;
    }
    return ESP_FAIL;
  }

  esp_err_t pause()
  {
    switch (state)
    {
    case STOP:
      ESP_LOGD(TAG, "Player is stopped");
      return ESP_OK;
    case PAUSE:
      ESP_LOGD(TAG, "Player is already paused");
      return ESP_OK;
    case PLAY:
      state = PAUSE;
      ESP_LOGD(TAG, "Pausing playback");
    }
    return ESP_FAIL;
  }

  esp_err_t resume()
  {
    switch (state)
    {
    case STOP:
      return play();
    case PAUSE:
      ESP_LOGD(TAG, "Resuming playback");
      state = PLAY;
      return ESP_OK;
    case PLAY:
      ESP_LOGD(TAG, "Player is already playing");
      return ESP_OK;
    }
    return ESP_FAIL;
  }

  esp_err_t next()
  {
    seq++;
    switch (state)
    {
    case PAUSE:
    case PLAY:
      stop();
    case STOP:
      return play();
    }
    return ESP_FAIL;
  }

  esp_err_t prev()
  {
    seq--;
    switch (state)
    {
    case PAUSE:
    case PLAY:
      stop();
    case STOP:
      return play();
    }
    return ESP_FAIL;
  }

  esp_err_t toggleLoop()
  {
    if (isLooped)
    {
      ESP_LOGI(TAG, "Disabling loop");
      isLooped = false;
    }
    else
    {
      ESP_LOGI(TAG, "Enabling loop");
      isLooped = true;
    }
    return ESP_OK;
  }

  void loop()
  {
    if (state == PLAY)
    {
      if (mp3->isRunning())
      {
        if (!mp3->loop())
        {
          if (isLooped)
            play();
          else
            stop();
        }
      }
      else
        stop();
    }
  }
};