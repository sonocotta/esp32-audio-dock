#pragma once

// #include "SPIFFS.h"
#include <LittleFS.h>

#define filesystem LittleFS
#define FSROOT "/littlefs"

struct PlaylistEntry
{
    String url = "";
    String title = "";
};

class Playlist
{
private:
    static inline const char *TAG = "PLAYLST";

public:
    PlaylistEntry *entries;
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

        bool foundPls = false;

        File file = root.openNextFile();
        while (file)
        {
            if (!file.isDirectory())
            {
                char *filename = (char *)file.name();
                int8_t len = strlen(filename);
                if (strstr(strlwr(filename + (len - 4)), ".pls"))
                {
                    foundPls = true;
                    char fullFilename[256];
                    sprintf(fullFilename, "/%s", filename);

                    // read file line by line to fill playlist
                    File playlist = filesystem.open(fullFilename, "r");
                    ESP_LOGI(TAG, "Reading: %s, %d bytes", fullFilename, playlist.size());

                    if (!playlist)
                    {
                        ESP_LOGE(TAG, "Failed to open file for reading");
                        return ESP_FAIL;
                    }

                    while (playlist.available())
                    {
                        String line = playlist.readStringUntil('\n');
                        ESP_LOGV(TAG, "read: %s", line);

                        if (line.indexOf("numberofentries=") >= 0)
                        {
                            String counts = line.substring(line.indexOf("=") + 1);
                            log_d("numberofentries = %s", counts.c_str());
                            entriesCount = atoi(counts.c_str());
                            entries = new PlaylistEntry[entriesCount];
                        }
                        else if (line.indexOf("=") >= 0)
                        {
                            String key = line.substring(0, line.indexOf("="));
                            String value = line.substring(line.indexOf("=") + 1);
                            ESP_LOGD(TAG, "%s = %s", key.c_str(), value.c_str());

                            if (key.startsWith("File"))
                            {
                                String index_s = key.substring(4);
                                uint8_t index = atoi(index_s.c_str()) - 1;
                                if ((index >= 0) && (index < entriesCount))
                                {
                                    entries[index].url = value;
                                }
                            }
                            else if (key.startsWith("Title"))
                            {
                                String index_s = key.substring(5);
                                uint8_t index = atoi(index_s.c_str()) - 1;
                                if ((index >= 0) && (index < entriesCount))
                                {
                                    entries[index].title = value;
                                }
                            }
                        }
                    }

                    ESP_LOGI(TAG, "Closing file");
                    file.close();

                    break;
                }
            }

            file = root.openNextFile();
        }

        if (!foundPls)
        {
            ESP_LOGE(TAG, "Failed to find playlist file, please copy playlist file to data folder and upload with \"Upload Filesystem Image\"");
            return ESP_FAIL;
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
            ESP_LOGI(TAG, "[%d] Station %s: %s", i + 1, entries[i].title.c_str(), entries[i].url.c_str());   
        }
        return ESP_OK;
    }
};