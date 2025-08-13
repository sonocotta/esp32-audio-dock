#include <Arduino.h>

const char *TAG = "MAIN";

#ifdef CONFIG_DAC_TAS5805M
#include <tas5805m.hpp>
tas5805m Tas5805m(&Wire);
#endif

#include <generator.hpp>
Generator generator;

#include <commandline.hpp>
CommandLine cmd;

#include "commands/tone.hpp"
ToneCommand toneCmd;

void setup()
{
  Serial.begin(SERIAL_BAUD);
#if ARDUINO_USB_CDC_ON_BOOT
  delay(3000);
#else
  delay(500);
#endif

  esp_log_level_set("*", ESP_LOG_INFO);

  // initializes I2S, important!
  generator.init();

#ifdef CONFIG_DAC_TAS5805M
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  // This will send default DSP init sequence
  Tas5805m.init();

  // I2S must be initialized by this time for DSP settings to apply
  uint8_t newVolume = 100;
  ESP_LOGI(TAG, "Setting VOLUME to: %d%", newVolume);
  ESP_ERROR_CHECK(Tas5805m.setVolume100(newVolume));

  ESP_LOGI(TAG, "Setting GAIN value to: -15.5Db");
  ESP_ERROR_CHECK(Tas5805m.setAnalogGain(TAS5805M_MIN_GAIN));
#endif

  cmd.init();
  cmd.registerCommandHandler(&toneCmd);

  
}

void loop()
{
  cmd.loop();
}