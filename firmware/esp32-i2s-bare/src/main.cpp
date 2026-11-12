#include <Arduino.h>

const char *TAG = "MAIN";

#ifdef CONFIG_DAC_TAS5805M
#include <tas5805m.hpp>
tas5805m Tas5805m(&Wire);
#endif

#ifdef CONFIG_DAC_PCM5122
#include <Wire.h>
#include "PCM51xx.h"
// I2C address is set by the ADR1/ADR2 pins and may be 0x4C..0x4F.
// HiFi-ESP32-Plus (rev H) uses 0x4C, Amped-ESP32(-S3)-Plus use 0x4D.
#ifndef PCM5122_I2C_ADDRESS
#define PCM5122_I2C_ADDRESS 0x4C
#endif
PCM51xx Pcm5122(Wire, PCM5122_I2C_ADDRESS);
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

#ifdef CONFIG_DAC_PCM5122
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);

  Wire.beginTransmission(PCM5122_I2C_ADDRESS);
  if (Wire.endTransmission() != 0)
    ESP_LOGE(TAG, "No PCM5122 ACK at I2C address 0x%02X (SDA=%d SCL=%d)",
             PCM5122_I2C_ADDRESS, PIN_I2C_SDA, PIN_I2C_SCL);

  // The rate passed here MUST match the rate I2S actually runs at: the PCM5122
  // sources its PLL from BCK, and these settings program the PLL and every
  // derived clock for that exact rate. A mismatch leaves the PLL out of lock,
  // which is silent on some parts and (marginally) works on others.
  ESP_LOGI(TAG, "Initializing PCM5122 at 0x%02X, %d Hz / 16 bit (BCK %d Hz)",
           PCM5122_I2C_ADDRESS, I2S_SAMPLE_RATE, I2S_SAMPLE_RATE * 16 * 2);
  Pcm5122.begin((PCM51xx::SamplingRate)I2S_SAMPLE_RATE, PCM51xx::BITS_PER_SAMPLE_16);

  // begin() programs the clock tree but never touches the standby/powerdown
  // register, so a part left in standby by whatever ran before (ESPHome parks
  // the DAC there on shutdown) stays mute forever. Ask for ACTIVE explicitly.
  Pcm5122.setPowerMode(PCM51xx::POWER_MODE_ACTIVE);

  // Clear the L/R soft mute (register 3) and restore a known volume. begin()
  // touches neither, and both survive a CPU reset because the DAC itself is
  // never power cycled - so a part left muted or attenuated by whatever ran
  // before (ESPHome mutes the DAC when the media player goes idle) stays
  // silent here no matter how many times you reflash the ESP32. This was the
  // actual cause of "works on some boards, dead quiet on others": measured
  // register 3 = 0x11 (both channels muted) and volume = 0x80 (-40 dB).
  Pcm5122.writeRegister(PCM51xx::MUTE, 0x00);
  Pcm5122.setVolume(0x30); // 0 dB (0 = +24 dB, 0.5 dB per step)

  // Power-up, calibration and volume ramp take far longer than the 10 ms that
  // begin() waits before sampling the state, so poll instead of trusting it.
  PCM51xx::PowerState state = PCM51xx::POWER_STATE_STANDBY;
  for (int i = 0; i < 20 && state != PCM51xx::POWER_STATE_RUN; i++)
  {
    delay(25);
    state = Pcm5122.getPowerState();
  }

  if (state == PCM51xx::POWER_STATE_RUN)
    ESP_LOGI(TAG, "PCM5122 is in RUN state");
  else
    ESP_LOGE(TAG, "PCM5122 did not reach RUN state, power state = 0x%02X", state);

  #ifdef PIN_PCM5122_MUTE
  pinMode(PIN_PCM5122_MUTE, OUTPUT);
  digitalWrite(PIN_PCM5122_MUTE, HIGH); // unmute
  #endif
#endif

  // External power amplifier enable/unmute line (active high), present on the
  // Amped-* boards where the class-D amp is a separate chip from the DAC.
#ifdef PIN_AMP_ENABLE
  ESP_LOGI(TAG, "Enabling AMP on pin %d", PIN_AMP_ENABLE);
  pinMode(PIN_AMP_ENABLE, OUTPUT);
  digitalWrite(PIN_AMP_ENABLE, HIGH);
#endif

  cmd.init();
  cmd.registerCommandHandler(&toneCmd1);
  cmd.registerCommandHandler(&toneCmd2);

  // Spin up tone automatically for demo purposes
  // sineGenerator.setFrequency(500);
  // sineGenerator.setAmplitude(10);
  // sineGenerator.start();

  squareGenerator.setFrequency(100);
  squareGenerator.setAmplitude(10);
  squareGenerator.start();

}

void loop()
{
  cmd.loop();
}