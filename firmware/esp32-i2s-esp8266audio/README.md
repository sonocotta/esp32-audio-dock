# esp32-i2s-esp8266audio example firmware

Simple example demonstrates how to use [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio) library to initialize the DAC and generate audio.

Library has plenty of examples on it's own, I selected self contained example, that plays test audio from flash storage

To make it work you need to flash SPIFFS image by using `Upload Filesystem Image` task. It will automatically pick up all files from `data` folder.

After applying power audio starts automatically.