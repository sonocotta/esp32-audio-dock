#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif
#ifdef ESP32
#include <WiFi.h>
#endif
#include <SD.h>
#ifdef ESP32
#include "SPIFFS.h"
#endif

#ifdef DAC_TAS5805M
#include <Wire.h>
#include <tas5805m.hpp>
#include <Ticker.h>
tas5805m Tas5805m(&Wire);
Ticker ticker;
#endif

#include <AudioOutputI2S.h>
#include <AudioFileSourceSPIFFS.h>
#include <AudioGeneratorWAV.h>

AudioOutputI2S *out;
AudioFileSourceSPIFFS *file;
AudioGeneratorWAV *wav;

const uint8_t audio_files_length = 1;
const char **audio_files = (const char **)malloc(audio_files_length * sizeof(char *));

enum State
{
  STOP,
  WAIT,
  PLAY,
  ERR,
  END
};

State state = STOP;
int seq = 0;

#ifdef DAC_TAS5805M
void ticker_callback()
{
  uint8_t h70 = 0, h71 = 0, h72 = 0;
  ESP_ERROR_CHECK(Tas5805m.getFaultState(&h70, &h71, &h72));
  log_i("Fault registers: h70 = %d, h71 = %d, h72 = %d", h70, h71, h72);

  if (h70 || h71 || h72)
  {
    log_i("Sending CLEAR FAULT");
    ESP_ERROR_CHECK(Tas5805m.clearFaultState());
  }

  uint8_t gain = 0, volume = 0;
  ESP_ERROR_CHECK(Tas5805m.getGain(&gain));
  ESP_ERROR_CHECK(Tas5805m.getVolume(&volume));
  log_i("Current GAIN value = %d; VOLUME value = %d", gain, volume);
}
#endif

void setup()
{
  WiFi.mode(WIFI_OFF);

  Serial.begin(SERIAL_BAUD);
  Serial.println(F("Starting up...\n"));

  if (!SPIFFS.begin())
  {
    Serial.println(F("An Error has occurred while mounting SPIFFS"));
    while (1)
      ;
  }
  else
    Serial.println(F("SPIFFS mounted"));

#ifdef DAC_TAS5805M
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  Tas5805m.init();
#endif

  out = new AudioOutputI2S();
#ifdef ESP32
  Serial.printf("Setting I2S pins: clk = %d, ws = %d, data = %d\n", PIN_I2S_SCK, PIN_I2S_FS, PIN_I2S_SD);
  if (!out->SetPinout(PIN_I2S_SCK, PIN_I2S_FS, PIN_I2S_SD))
  {
    Serial.println("Failed to set pinout");
  }
#endif

#ifdef DAC_TAS5805M
  Tas5805m.begin();
  // Tas5805m.begin(TAS5805M_MONO);
  ticker.attach_ms(1000, ticker_callback);

  uint8_t newVolume = 100;
  log_i("Setting VOLUME value to: %d", newVolume);
  ESP_ERROR_CHECK(Tas5805m.setVolume(newVolume));
#endif

  wav = new AudioGeneratorWAV();

  audio_files[0] = "/audiotest.wav";

  file = new AudioFileSourceSPIFFS(audio_files[seq % audio_files_length]);
  if (wav->begin(file, out))
    log_i("Start playing: %s", audio_files[seq % audio_files_length]);
}

void loop()
{
  if (wav->isRunning())
  {
    if (!wav->loop())
    {
      wav->stop();
      state = WAIT;
    }
  }
}