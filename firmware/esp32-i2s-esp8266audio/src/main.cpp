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
tas5805m Tas5805m(&Wire);
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
  if (!out->SetPinout(PIN_I2S_SCK, PIN_I2S_FS, PIN_I2S_SD)) {
    Serial.println("Failed to set pinout");
  }
  #endif

#ifdef DAC_TAS5805M
  Tas5805m.begin();
#endif

  wav = new AudioGeneratorWAV();

  audio_files[0] = "/audiotest.wav";

  file = new AudioFileSourceSPIFFS(audio_files[seq % audio_files_length]);
  if (wav->begin(file, out))
    Serial.print(audio_files[seq % audio_files_length]);
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