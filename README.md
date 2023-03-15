# ESP32 Audio Docks

![Open Source Hardware](/images/open-source-hardware-logo.png)
![Open Source Software](/images/open-source-software-logo.png)

ESP32 Audio Docks is a range of extension boards (i.e. docks) that allow you to develop Audio solutions based on ESP32 chips. These were created to make Audio development entry as easy and inexpensive as possible. 

@image

## Motivation

I spent last few years developing different solutions based on ESP delices. It all started with ESP8266, where CPU power is not really sufficient to do real-time decoding, so you're limited to rather simple ding-dong business. Then ESP32 came, bringing two much more capable cores, so you have powerhouse to handle communication and decoding at the same time. Perhaps most importantly it also came with SPIRAM, so you can do decent buffering (essential for streamed content). 

Now new ESP32 C-Series and S-Series chips are entering the market, and their potential is mostly unrealized as for today.

I created those docks, to be able quick prototype for whole range of ESP8266 and ESP32 chips, starting with the simplest finger-sized toys and going all the way up to full-sized speakers.

## Features

|             | ESP Audio Solo                                      | ESP Audio Duo                                     | Hifi ESP                    | Louder ESP                                            |
|-------------|-----------------------------------------------------|---------------------------------------------------|-----------------------------|-------------------------------------------------------|
| Image       | ?image                                              | ?image                                            | ?image                      | ?image                                                |
| Docks with  | ESP8266, ESP32C3, ESP32S2 Mini modules              | ESP32 Mini Module                                 | ESP32 Mini Module           | ESP32 Mini Module                                     |
| DAC         | Single I2S DAC ([MAX98357](https://www.analog.com/en/products/max98357a.html)) with built in D-Class amp | Dual I2S DAC ([MAX98357](https://www.analog.com/en/products/max98357a.html)) with built in D-Class amp | PCM5100A 32bit Stereo DAC   | Stereo I2S DAC ([TAS5805M](https://www.ti.com/product/TAS5805M)) with   built in D-Class amp |
| Output (4Ω) | 3W                                                  | 2x 3W                                             | Non-amplified stereo output | 2x 15W at 12V Vin                                     |
| Output (8Ω) | 1.5W                                                | 2x 1.5W                                           | Non-amplified stereo output | 2x 23W at 22V Vin                                     |
| Adds        |                                                     | 8Mb PSRAM (4Mb usable)                            | 8Mb PSRAM (4Mb usable)      | 8Mb PSRAM (4Mb usable)                                |

### Onboard PSRAM

Audio streaming require proper buffering to work, even with ESP32 500K of RAM it is a challending task. For that reason most of the projects will require WROVER modules that have onboard PSRAM chip. 

All ESP32 Docks has 8M PSRAM chip onboard, connected via high-speed SDIO interface. This effectively turn your regular WROOM module into WROVER module with no effort required. Any code using PSRAM with just work out-of-the box.

## Boards Pinout

?image and description 

## Software samples

In the [software](/firmware) section two firmware examples provided.

- [esp32-i2s-bare](/firmware/esp32-i2s-bare/) is base I2S implementation based on ESP-IDF implementation directly.
- [esp32-i2s-esp8266audio](/firmware/esp32-i2s-esp8266audio/) is based on excellent [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio) library (it works with the whole ESP range, don't get fooled by the name), providing minimum code implementation. 

### Platformio IDE
 
All samples are provided as [Plarformio IDE](https://platformio.org/platformio-ide) projects. After installing it, open sample project. Select proper environment based on your dock. Run `Build` and `Upload` commands to install necessary tools and libraries, build and upload prject to the board. Communication and proper upload method selection will be handled by IDE automatically. 

## Arduino IDE

Follow the [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio) library guide. Default settings will work out of the box with ESP8266 and ESP32 boards. For ESP32C3 and ESP32S2 board please adjust pinout according to the above section

## Hardware

Please visit [hardware](/hardware/) section for board schematics and PCB designs. Note that PCB are shared as multi-layer PDFs.

## Where to buy

In limited quantities possible to buy at [Tindie](https://www.tindie.com/products/sonocotta/).

## Links
