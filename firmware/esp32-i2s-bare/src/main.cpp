#ifdef DAC_TAS5805M
#include <Wire.h>
#include <tas5805m.hpp>
tas5805m Tas5805m(&Wire);
#endif

#include <I2S.h>
const int frequency = 512;  // frequency of square wave in Hz
const int amplitude = 256;   // amplitude of square wave
const int sampleRate = 8000; // sample rate in Hz
const int bps = 16;

const int halfWavelength = (sampleRate / frequency); // half wavelength of square wave

int32_t sample = amplitude; // current sample value
int count = 0;

i2s_mode_t mode = I2S_PHILIPS_MODE; // I2S decoder is needed
// i2s_mode_t mode = ADC_DAC_MODE; // Audio amplifier is needed

// Mono channel input
// This is ESP specific implementation -
//   samples will be automatically copied to both channels inside I2S driver
//   If you want to have true mono output use I2S_PHILIPS_MODE and interlay
//   second channel with 0-value samples.
//   The order of channels is RIGH followed by LEFT
// i2s_mode_t mode = I2S_RIGHT_JUSTIFIED_MODE; // I2S decoder is needed

void setup()
{
  Serial.begin(SERIAL_BAUD);
#if ARDUINO_HW_CDC_ON_BOOT
  delay(2000);
#else
  delay(100);
#endif

  #ifdef DAC_TAS5805M
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  Tas5805m.init();
  #endif

  log_i("I2S simple tone");

  // start I2S at the sample rate with 16-bits per sample
  if (!I2S.begin(mode, sampleRate, bps))
  {
    log_e("Failed to initialize I2S!");
    while (1)
      ; // do nothing
  }

#ifdef DAC_TAS5805M
  Tas5805m.begin();
#endif
}

void loop()
{
  if (count % halfWavelength == 0)
  {
    // invert the sample every half wavelength count multiple to generate square wave
    sample = -1 * sample;
  }

  if (mode == I2S_PHILIPS_MODE || mode == ADC_DAC_MODE)
  {                    // write the same sample twice, once for Right and once for Left channel
    I2S.write(sample); // Right channel
    I2S.write(sample); // Left channel
  }
  else if (mode == I2S_RIGHT_JUSTIFIED_MODE || mode == I2S_LEFT_JUSTIFIED_MODE)
  {
    // write the same only once - it will be automatically copied to the other channel
    I2S.write(sample);
  }

  // increment the counter for the next sample
  count++;
}
