#include <Arduino.h>

const char *TAG = "MAIN";

#ifdef CONFIG_DAC_TAS5805M
#include <tas5805m.hpp>
tas5805m Tas5805m(&Wire);
#endif

#include "generators/generator.hpp"
SquareGenerator squareGenerator;
SineGenerator sineGenerator;

#include <commandline.hpp>
CommandLine cmd;

#include "commands/squaretone.hpp"
SquareToneCommand toneCmd1;

#include "commands/sinetone.hpp"
SineToneCommand toneCmd2;

void setup()
{
  Serial.begin(SERIAL_BAUD);
#if ARDUINO_USB_CDC_ON_BOOT
  delay(3000);
#else
  delay(500);
#endif

  // esp_log_level_set("*", ESP_LOG_DEBUG);

  // initializes I2S, important!
  squareGenerator.init();

#ifdef CONFIG_DAC_TAS5805M
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  // This will send default DSP init sequence
  Tas5805m.init();

  // I2S must be initialized by this time for DSP settings to apply
  uint8_t newVolume = 100; // 0...124, where 100 is max voltage swing without risk of clipping (assuming analog gain is set appropriately)
  ESP_LOGI(TAG, "Setting VOLUME to: %d%", newVolume);
  ESP_ERROR_CHECK(Tas5805m.setVolume100(newVolume));

  // If you power from onboard USB, you must set gain to minimum to avoid clipping
  // ESP_LOGI(TAG, "Setting GAIN value to: -15.5dB");
  // ESP_ERROR_CHECK(Tas5805m.setAnalogGain(TAS5805M_MIN_GAIN));

  // If you power from external 15V+ supply, you can set gain to max
  ESP_LOGI(TAG, "Setting GAIN value to: 0dB");
  ESP_ERROR_CHECK(Tas5805m.setAnalogGain(TAS5805M_MAX_GAIN));
  #endif

  cmd.init();
  cmd.registerCommandHandler(&toneCmd1);
  cmd.registerCommandHandler(&toneCmd2);

  // Spin up tone automatically for demo purposes
  // sineGenerator.setFrequency(100);
  // sineGenerator.setAmplitude(14);
  // sineGenerator.start();

  // squareGenerator.setFrequency(1000);
  // squareGenerator.setAmplitude(14);
  // squareGenerator.start();

}

void loop()
{
  cmd.loop();
}