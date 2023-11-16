# esp32-i2s-web-radio example firmware (wip)

Simple example demonstrates how to use [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio) library to play internet radio stream.

To make it work you need to flash SPIFFS image bcontaining playlist file by using `Upload Filesystem Image` task. It will automatically pick up all files from `data` folder.

Software will find first playlist file (*.pls) and parse list of stations. It plays first one automatically, and continue cycling through in case of error.

After applying power audio starts automatically.

## To do

- Use SPIRAM for buffer. Library's implementation not using ESP32 native communication, so it requires different implementation
- Add self-hosted web UI