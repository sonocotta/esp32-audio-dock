#pragma once

#include <Arduino.h>
#include <I2S.h>
#include <vector>
#include <cmath>

class Generator
{
private:
    static constexpr const char *TAG = "GENERATOR";

protected:

    // I2SClass i2s;

    const int sampleRate        = 16000; // sample rate in Hz
    const int maxFreq           = 8000; // maximum frequency in Hz
    //i2s_data_bit_width_t bps    = I2S_DATA_BIT_WIDTH_16BIT;
    const int bps               = 16;
    i2s_mode_t mode             = I2S_PHILIPS_MODE;
    //i2s_mode_t mode             = I2S_MODE_STD;
    //i2s_slot_mode_t slot        = I2S_SLOT_MODE_STEREO;
    uint32_t frequency          = 440;    // frequency of square wave in Hz
    uint8_t amplitude           = 10;     // amplitude bit-shift (0..16)

public:

    Generator() = default;

    virtual uint8_t getAmplitude()
    {
        return amplitude;
    };

    virtual void setAmplitude(uint8_t amp) {
        if (amp > 16) amp = 16;
        amplitude = amp;
    };

    virtual void setFrequency(uint32_t freq) {
        frequency = freq;
    };
    
    virtual uint32_t getFrequency()
    {
        return frequency;
    };

    void init()
    {
        if (!I2S.begin(mode, sampleRate, bps))
        {
            ESP_LOGE(TAG, "Failed to initialize I2S!");
        }
        else
        {
            ESP_LOGI(TAG, "I2S initialized");
        }
    };

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void loop() = 0; 
};

class SquareGenerator: public Generator
{
private:
    static constexpr const char *TAG = "TONE";

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
    SquareGenerator(uint32_t freq = 440, uint8_t amp = 10) : Generator()
    {
        setFrequency(freq);
        setAmplitude(amp);
    };

    void setFrequency(uint32_t freq) override
    {
        frequency = freq;
        halfWavelength = (sampleRate / frequency);
    };

    void setAmplitude(uint8_t amp) override
    {
        if (amp > 16) amp = 16;
        amplitude = amp;
        sample = 1 << amplitude; // update sample value based on amplitude
    };

    void start() override
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

    void stop() override
    {
        count = 0;
        enabled = false;
    }

    void loop() override
    {
        if (enabled) {
            if (count % halfWavelength == 0)
            {
                sample = -1 * sample;
            }

            // if (slot == I2S_SLOT_MODE_STEREO)
            // {
                I2S.write(sample); // Right channel
                I2S.write(sample); // Left channel
            // }
            // else if (slot == I2S_SLOT_MODE_MONO)
            // {
            //     i2s.write(sample);
            // }
            count++;
        } else {
            I2S.write((int32_t)0);
        }
    }
};

class SineGenerator: public Generator
{
private:
    static constexpr const char *TAG = "SINE";

    bool enabled = false;

    std::vector<int16_t> wavetable;
    size_t wavetableSize = 1024;   // default size, power of two recommended
    uint32_t phase = 0;            // fixed-point phase accumulator
    uint32_t phaseIncrement = 0;   // step per sample (Q16.16 fixed-point)

    TaskHandle_t taskHandle = NULL; // Task handle for stopping the task

    static void taskLoop(void *pvParameters)
    {
        SineGenerator *instance = static_cast<SineGenerator *>(pvParameters);
        while (1) instance->loop();
    }

    void updatePhaseIncrement()
    {
        // fixed-point increment (Q16.16 format)
        phaseIncrement = (uint32_t)((((uint64_t)frequency << 16) * wavetableSize) / sampleRate);
    }

    void buildWavetable()
    {
        wavetable.resize(wavetableSize);
        int32_t maxAmp = (1 << amplitude);
        for (size_t i = 0; i < wavetableSize; i++)
        {
            float t = (2.0f * M_PI * i) / wavetableSize;
            wavetable[i] = static_cast<int16_t>(std::sin(t) * maxAmp);
        }
    }

public:
    SineGenerator(uint32_t freq = 440, uint8_t amp = 10, size_t tableSize = 1024)
        : wavetableSize(tableSize), Generator()
    {
        setFrequency(freq);
        setAmplitude(amp);
        buildWavetable();
        updatePhaseIncrement();
    };

    void setFrequency(uint32_t freq) override
    {
        if (freq < 10) freq = 10;
        if (freq > maxFreq) freq = maxFreq;
        frequency = freq;
        updatePhaseIncrement();
    }

    void setAmplitude(uint8_t amp) override
    {
        if (amp > 16) amp = 16;
        amplitude = amp;
        buildWavetable(); // rebuild table with new amplitude
    }

    void start() override
    {
        enabled = true;
        if (taskHandle == NULL)
        {
            ESP_LOGD(TAG, "Starting sine task");
            xTaskCreatePinnedToCore(
                taskLoop,
                "SineTask",
                4096,
                this,
                1,
                &taskHandle,
                1
            );
        }
    }

    void stop() override
    {
        enabled = false;
        phase = 0;
    }

    void loop() override
    {
        if (enabled)
        {
            // lookup table with fixed-point phase
            size_t index = (phase >> 16) % wavetableSize;
            int32_t sample = wavetable[index];

            // if (slot == I2S_SLOT_MODE_STEREO)
            // {
                I2S.write(sample); // Right channel
                I2S.write(sample); // Left channel
            // }
            // else if (slot == I2S_SLOT_MODE_MONO)
            // {
            //     i2s.write(sample);
            // }

            // increment phase
            phase += phaseIncrement;
        }
        else
        {
            I2S.write((int32_t)0);
        }
    }
};