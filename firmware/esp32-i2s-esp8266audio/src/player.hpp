#pragma once

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif
#ifdef ESP32
#include <WiFi.h>
#endif
#include <SD.h>
#include <LittleFS.h>

#include <AudioOutputI2S.h>
#include <AudioFileSourceFS.h>
#include <AudioGeneratorWAV.h>

#include "playlist.hpp"
extern Playlist playlist;

#include <I2S.h>

enum PlayerState
{
    STOP,
    PLAY,
    PAUSE,
};

class Player
{

private:
    static inline const char *TAG = "PLAYER";

    AudioOutputI2S out;
    AudioFileSourceFS *file;
    AudioGeneratorWAV *wav;

    int seq = 0;
    bool isLooped = false;

public:
    PlayerState state = STOP;

    esp_err_t init()
    {
#ifdef ESP32
        #ifdef PIN_I2S_MCLK
        ESP_LOGD(TAG, "Setting I2S pins: clk=%d, ws=%d, data=%d, mclk=%d", PIN_I2S_SCK, PIN_I2S_FS, PIN_I2S_SD, PIN_I2S_MCLK);
        if (!out.SetPinout(PIN_I2S_SCK, PIN_I2S_FS, PIN_I2S_SD, PIN_I2S_MCLK))
        #else
        ESP_LOGD(TAG, "Setting I2S pins: clk=%d, ws=%d, data=%d", PIN_I2S_SCK, PIN_I2S_FS, PIN_I2S_SD);
        if (!out.SetPinout(PIN_I2S_SCK, PIN_I2S_FS, PIN_I2S_SD))
        #endif
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
        switch (state)
        {
        case PAUSE:
            return resume();
        case PLAY:
            ESP_LOGD(TAG, "Player is already playing");
            return ESP_OK;
        case STOP:
            file = new AudioFileSourceFS(LittleFS, playlist.entries[seq % playlist.entriesCount].c_str());
            wav = new AudioGeneratorWAV();
            wav->begin(file, &out);
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

            if (wav) {
                wav->stop();
                delete wav;
            }
            if (file) {
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
            if (wav->isRunning())
            {
                if (!wav->loop())
                {
                    stop();
                    if (isLooped) play();
                }
            }
        }
    }
};
