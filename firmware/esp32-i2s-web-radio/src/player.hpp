#pragma once

// #ifdef BOARD_HAS_PSRAM
// #include "AudioFileSourceSPIRAMBuffer.h"
// #define AudioFileSourceBufferClass AudioFileSourceSPIRAMBuffer
// #define AudioFileSourceBufferSize 1048576ull
// #else
#include "AudioFileSourceBuffer.h"
#define AudioFileSourceBufferClass AudioFileSourceBuffer
#define AudioFileSourceBufferSize 4096
// #endif

#include "AudioFileSourceICYStream.h"
#include "AudioGeneratorMP3.h"
#include <AudioOutputI2S.h>
#include "AudioOutputMixer.h"

#ifdef DAC_TAS5805M
#include <Wire.h>
#include <tas5805m.hpp>
#endif

#include "playlist.hpp"

enum PlayerState
{
  STATE_PLAY_INIT = 0,
  STATE_PLAY_READY = 10,
  STATE_PLAY = 11,
  STATE_PLAY_STOPPED = 12
};

static int lastms = 0;

class Player
{
private:
  AudioFileSourceICYStream *file;
  AudioFileSourceBufferClass *buff;
  AudioGeneratorMP3 *mp3;
  AudioOutputI2S *out = new AudioOutputI2S();
  AudioOutputMixer *mixer = new AudioOutputMixer(64, out);
  AudioOutputMixerStub *stubs[1] = {
    mixer->NewInput()
  };

#ifdef DAC_TAS5805M
  tas5805m* Tas5805m = new tas5805m(&Wire);
#endif
  static void statusCallback(void *cbData, int code, const char *string);
  static void mdCallback(void *cbData, const char *type, bool isUnicode, const char *string);
  void setState(PlayerState _state)
  {
    log_d("State changed to %d", _state);
    state = _state;
  }

public:
  PlayerState state = STATE_PLAY_INIT;

  void audioInit();
  void play(PlaylistEntry);
  void process();
};

void Player::play(PlaylistEntry entry)
{
  log_i("Start playing '%s'", entry.title);
  log_i("Url = %s", entry.url);

  audioLogger = &Serial;
  file = new AudioFileSourceICYStream(entry.url.c_str());
  file->RegisterMetadataCB(Player::mdCallback, (void *)"ICY");
  buff = new AudioFileSourceBufferClass(file, AudioFileSourceBufferSize);
  buff->RegisterStatusCB(Player::statusCallback, (void *)"buffer");

  // stubs[0] = mixer->NewInput();
  // stubs[0]->SetGain(volume);

  mp3 = new AudioGeneratorMP3();
  // mp3->RegisterStatusCB(Player::statusCallback, (void *)"mp3");
  mp3->begin(buff, stubs[0]);

#ifdef DAC_TAS5805M
  Tas5805m->begin();
#endif
  setState(STATE_PLAY);
}

void Player::process()
{
  if (mp3->isRunning())
  {
    if (millis() - lastms > 5000)
    {
      lastms = millis();
      log_d("Running for %d ms", lastms);
    }
    if (!mp3->loop())
      mp3->stop();
  }
  else
  {
    log_i("MP3 done");
    delete file;
    delete buff;
    setState(STATE_PLAY_STOPPED);
  }
}

// Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
void Player::mdCallback(void *cbData, const char *type, bool isUnicode, const char *string)
{
  const char *ptr = reinterpret_cast<const char *>(cbData);
  (void)isUnicode; // Punt this ball for now
  // Note that the type and string may be in PROGMEM, so copy them to RAM for printf
  char s1[32], s2[64];
  strncpy_P(s1, type, sizeof(s1));
  s1[sizeof(s1) - 1] = 0;
  strncpy_P(s2, string, sizeof(s2));
  s2[sizeof(s2) - 1] = 0;
  log_d("METADATA(%s) '%s' = '%s'", ptr, s1, s2);
}

// Called when there's a warning or error (like a buffer underflow or decode hiccup)
void Player::statusCallback(void *cbData, int code, const char *string)
{
  const char *ptr = reinterpret_cast<const char *>(cbData);
  // Note that the string may be in PROGMEM, so copy it to RAM for printf
  char s1[64];
  strncpy_P(s1, string, sizeof(s1));
  s1[sizeof(s1) - 1] = 0;
  log_d("STATUS(%s) '%d' = '%s'", ptr, code, s1);
}

void Player::audioInit()
{
#ifdef DAC_TAS5805M
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  Tas5805m->init();
#endif
  setState(STATE_PLAY_READY);
}