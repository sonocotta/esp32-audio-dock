#pragma once

// #include "SPIFFS.h"
#include <LittleFS.h>

#define filesystem LittleFS
#define FSROOT "/littlefs"

struct PlaylistEntry {
    String url = "";
    String title = "";
};

class Playlist
{
private:
public:
    PlaylistEntry* entries;
    uint8_t entriesCount = 0;

    bool init();
};

bool Playlist::init()
{

    if (!filesystem.begin())
    {
        log_e("An Error has occurred while mounting filesystem");
        return false;
    }
    else
        log_i("Filesystem mounted");

    File root = filesystem.open("/");
    if (!root)
    {
        log_e("Filesystem mount failed!");
        return false;
    }
    else
    {
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
                    log_i("Reading: %s, %d bytes", fullFilename, playlist.size());

                    if (!playlist) {
                        log_e("Failed to open file for reading");
                        return false;
                    }
                    
                    while (playlist.available())
                    {
                        String line = playlist.readStringUntil('\n');
                        log_v("read: %s", line);

                        if (line.indexOf("numberofentries=") >= 0)
                        {
                            String counts = line.substring(line.indexOf("=") + 1);
                            log_d("numberofentries = %s", counts.c_str());
                            entriesCount = atoi(counts.c_str());
                            entries = new PlaylistEntry[entriesCount];
                        } else if (line.indexOf("=") >= 0) {  
                            String key = line.substring(0, line.indexOf("="));
                            String value =  line.substring(line.indexOf("=") + 1);
                            log_d("%s = %s", key.c_str(), value.c_str());

                            if (key.startsWith("File")) {
                                String index_s = key.substring(4);
                                uint8_t index = atoi(index_s.c_str()) - 1;
                                if ((index >=0) && (index < entriesCount))
                                {
                                    entries[index].url = value;
                                }
                            } else if (key.startsWith("Title")) {
                                String index_s = key.substring(5);
                                uint8_t index = atoi(index_s.c_str()) - 1;
                                if ((index >=0) && (index < entriesCount))
                                {
                                    entries[index].title = value;
                                }
                            }
                        }
                    }

                    log_d("Closing file");
                    file.close();
                    
                    break;
                }
            }

            file = root.openNextFile();
        }

        if (!foundPls)
        {
            log_e("Failed to find playlist file, please copy playlist file to data folder and upload with \"Upload Filesystem Image\"");
            return false;
        }
    }

    return true;
}