#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <I2S.h>

i2s_mode_t mode = I2S_PHILIPS_MODE; // I2S decoder is needed

class Generator
{
private:
    static inline const char *TAG = "TONE";

    const int sampleRate = 16000; // sample rate in Hz
    const int bps = 16;
    uint32_t frequency = 32; // frequency of square wave in Hz
    uint8_t amplitude = 10;  // amplitude of square wave
    int32_t sample = 1 << amplitude;
    bool enabled = false;

    int halfWavelength = (sampleRate / frequency); // half wavelength of square wave
    int count = 0;

    TaskHandle_t taskHandle = NULL; // Task handle for stopping the task

    static void taskLoop(void *pvParameters)
    {
        Generator *instance = static_cast<Generator *>(pvParameters);
        while (1) instance->loop();
    }

public:
    Generator() {};

    void setFrequency(uint32_t freq)
    {
        frequency = freq;
        halfWavelength = (sampleRate / frequency);
    };

    uint32_t getFrequency()
    {
        return frequency;
    };

    void setAmplitude(uint8_t amp)
    {
        amplitude = amp;
        sample = 1 << amplitude;
    };

    uint8_t getAmplitude()
    {
        return amplitude;
    };

    void init()
    {
        // start I2S at the sample rate with 16-bits per sample
        if (!I2S.begin(mode, sampleRate, bps))
        {
            ESP_LOGE(TAG, "Failed to initialize I2S!");
        }
        else
        {
            ESP_LOGI(TAG, "I2S initialized");
        }
    };

    void start()
    {
        enabled = true;
        if (taskHandle == NULL)
        {
            ESP_LOGD(TAG, "Starting tone task");
            xTaskCreatePinnedToCore(
                taskLoop,    // Task function
                "ToneTask",  // Task name
                2048,        // Stack size
                this,        // Task parameters (pass the instance)
                1,           // Priority (1 is normal)
                &taskHandle, // Task handle
                1            // Run on Core 1
            );
        }
    }

    void stop()
    {
        count = 0;
        enabled = false;
    }

    void loop()
    {
        if (enabled) {
            if (count % halfWavelength == 0)
            {
                sample = -1 * sample;
            }

            if (mode == I2S_PHILIPS_MODE || mode == ADC_DAC_MODE)
            {
                I2S.write(sample); // Right channel
                I2S.write(sample); // Left channel
            }
            else if (mode == I2S_RIGHT_JUSTIFIED_MODE || mode == I2S_LEFT_JUSTIFIED_MODE)
            {
                I2S.write(sample);
            }
            count++;
        } else {
            I2S.write((int32_t)0);
        }
    }
};

#endif