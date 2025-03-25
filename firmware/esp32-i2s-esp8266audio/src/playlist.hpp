#pragma once

#include <LittleFS.h>

class Playlist
{
private:
    static inline const char *TAG = "PLAYLST";

public:
    String* entries;
    uint8_t entriesCount = 0;

    esp_err_t init()
    {
        if (!filesystem.begin())
        {
            ESP_LOGE(TAG, "An Error has occurred while mounting filesystem");
            return ESP_FAIL;
        }
        else
            ESP_LOGI(TAG, "Filesystem mounted");

        File root = filesystem.open("/");
        if (!root)
        {
            ESP_LOGE(TAG, "Filesystem mount failed!");
            return ESP_FAIL;
        }

        uint8_t fileCount = 0;
        File file = root.openNextFile();
        while (file)
        {
            if (!file.isDirectory())
            {
                char *filename = (char *)file.name();
                int8_t len = strlen(filename);
                if (strstr(strlwr(filename + (len - 4)), ".wav"))
                {
                    fileCount++;
                }
            }
            file = root.openNextFile();
        }

        if (fileCount == 0)
        {
            ESP_LOGE(TAG, "No .wav files found in the filesystem");
            return false;
        }

        entries = new String[fileCount];
        entriesCount = fileCount;

        root.rewindDirectory();
        fileCount = 0;
        file = root.openNextFile();
        while (file)
        {
            if (!file.isDirectory())
            {
                char *filename = (char *)file.name();
                int8_t len = strlen(filename);
                if (strstr(strlwr(filename + (len - 4)), ".wav"))
                {
                    entries[fileCount] = "/" + String(filename);
                    fileCount++;
                }
            }
            file = root.openNextFile();
        }

        ESP_LOGI(TAG, "Found %d .wav files", entriesCount);
        for (uint8_t i = 0; i < entriesCount; i++)
        {
            ESP_LOGI(TAG, "File %d: %s", i + 1, entries[i].c_str());
        }

        return ESP_OK;
    }

    esp_err_t list()
    {
        if (entriesCount == 0)
        {
            ESP_LOGE(TAG, "No tracks found");
            return ESP_FAIL;
        }

        ESP_LOGI(TAG, "Listing all tracks:");
        for (uint8_t i = 0; i < entriesCount; i++)
        {
            ESP_LOGI(TAG, "File %d: %s", i + 1, entries[i].c_str());
        }
        return ESP_OK;
    }
};