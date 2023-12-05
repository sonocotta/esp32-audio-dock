# ESP32 Audio Docks

![Open Source Hardware](/images/open-source-hardware-logo.png)
![Open Source Software](/images/open-source-software-logo.png)

ESP32 Audio Docks is a range of extension boards (i.e. docks) that allow you to develop Audio solutions based on ESP32 chips. These were created to make Audio development entry as easy and inexpensive as possible. 

![image](https://user-images.githubusercontent.com/5459747/225271619-35ba0f99-fdd1-496b-b305-26e397df4460.png)

## Motivation

I spent last few years developing different solutions based on ESP delices. It all started with ESP8266, where CPU power is not really sufficient to do real-time decoding, so you're limited to rather simple ding-dong business. Then ESP32 came, bringing two much more capable cores, so you have powerhouse to handle communication and decoding at the same time. Perhaps most importantly it also came with SPIRAM, so you can do decent buffering (essential for streamed content). 

Now new ESP32 C-Series and S-Series chips are entering the market, and their potential is mostly unrealized as for today.

I created those docks, to be able quick prototype for whole range of ESP8266 and ESP32 chips, starting with the simplest finger-sized toys and going all the way up to full-sized speakers.

## Features

|             | ESP Audio Solo                                      | ESP Audio Duo                                     | Hifi ESP                    | Louder ESP                                            |
|-------------|-----------------------------------------------------|---------------------------------------------------|-----------------------------|-------------------------------------------------------|
| Image       | ![image](https://user-images.githubusercontent.com/5459747/225271839-3844b043-f3f4-4cb1-8a11-72c4f02aedce.png)                                              | ![image](https://user-images.githubusercontent.com/5459747/225271977-fd333283-66f0-448f-b748-e0ac94e25680.png)                                            | ![image](https://user-images.githubusercontent.com/5459747/225272052-c36d5b87-1b9a-439c-be69-94077135e72a.png)                      | ![image](https://user-images.githubusercontent.com/5459747/225272110-9433ff86-8912-47c5-a9f2-12bd7a0fe5a0.png)                                                |
| Docks with  | ESP8266, ESP32C3, ESP32S2 Mini modules              | ESP32 Mini Module                                 | ESP32 Mini Module           | ESP32 Mini Module                                     |
| DAC         | Single I2S DAC ([MAX98357](https://www.analog.com/en/products/max98357a.html)) with built in D-Class amp | Dual I2S DAC ([MAX98357](https://www.analog.com/en/products/max98357a.html)) with built in D-Class amp | [PCM5100A](https://www.ti.com/product/PCM5100A) 32bit Stereo DAC <br/> -100 dB typical noise level   | Stereo I2S DAC ([TAS5805M](https://www.ti.com/product/TAS5805M)) with   built in D-Class amp |
| Output (4Ω) | 3W                                                  | 2x 3W                                             | Non-amplified stereo output | 2x 15W at 12V Vin                                     |
| Output (8Ω) | 1.5W                                                | 2x 1.5W                                           | Non-amplified stereo output | 2x 23W at 22V Vin                                     |
| Adds        |                                                     | 8MB PSRAM (4MB usable)                            | 8MB PSRAM (4MB usable)      | 8MB PSRAM (4MB usable)                                |

### Onboard PSRAM

Audio streaming require proper buffering to work, even with ESP32 500K of RAM it is a challenging task. For that reason most of the projects will require WROVER modules that have onboard PSRAM chip. 

All ESP32 Docks has 8MB PSRAM chip onboard, connected via high-speed SDIO interface. This effectively **turns your regular WROOM module into WROVER module** with no effort required. Any code using PSRAM with just work out-of-the box.

## Boards Pinout

### ESP Audio Solo

|         | I2S CLK | I2S DATA | I2S WS |
|---------|---------|----------|--------|
| ESP8266 | 15      | 3        | 2      |
| ESP32C3 | 5       | 20       | 6      |
| ESP32S2 | 12      | 37       | 16     |

### ESP Audio Duo

|       | I2S CLK | I2S DATA | I2S WS | PSRAM CE | PSRAM CLK |
|-------|---------|----------|--------|----------|-----------|
| ESP32 | 26      | 22       | 25     | 16       | 17        |

### HiFi-ESP

|       | I2S CLK | I2S DATA | I2S WS | PSRAM CE | PSRAM CLK |
|-------|---------|----------|--------|----------|-----------|
| ESP32 | 26      | 22       | 25     | 16       | 17        |

### Louder ESP

|       | I2S CLK | I2S DATA | I2S WS | PSRAM CE | PSRAM CLK | TAS5805 SDA | TAS5805 SCL | TAS5805 PWDN | TAS5805 FAULT |
|-------|---------|----------|--------|----------|-----------|-------------|-------------|--------------|---------------|
| ESP32 | 26      | 22       | 25     | 16       | 17        | 21          | 27          | 33           | 34            |

## Software samples

In the [software](/firmware) section two firmware examples provided.

- [esp32-i2s-bare](/firmware/esp32-i2s-bare/) is base I2S implementation based on ESP-IDF implementation directly.
- [esp32-i2s-esp8266audio](/firmware/esp32-i2s-esp8266audio/) is based on excellent [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio) library (it works with the whole ESP range, don't get fooled by the name), providing minimum code implementation. 
- [esp32-i2s-web-radio](/firmware/esp32-i2s-web-radio/) is based on the [same library](https://github.com/earlephilhower/ESP8266Audio), providing minimum web-readio stream player. It expects playlist as an input in 'data' folder. 

### Platformio IDE
 
All samples are provided as [Plarformio IDE](https://platformio.org/platformio-ide) projects. After installing it, open sample project. Select proper environment based on your dock. Run `Build` and `Upload` commands to install necessary tools and libraries, build and upload prject to the board. Communication and proper upload method selection will be handled by IDE automatically. 

## Arduino IDE

Follow the [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio) library guide. Default settings will work out of the box with ESP8266 and ESP32 boards. For ESP32C3 and ESP32S2 board please adjust pinout according to the above section

## Squeezelite-ESP32

Squeezelite-ESP32 is a multimedia software suite, that started as renderer (or player) of LMS (Logitech Media Server). Now it is extended with 
- **Spotify** over-the-air player using SpotifyConnect (thanks to cspot)
- **AirPlay** controller (iPhone, iTunes ...) and enjoy synchronization multiroom as well (although it's AirPlay 1 only)
- Traditional **Bluetooth** device (iPhone, Android)

And LMS itself
- Streams your local music and connect to all major on-line music providers (Spotify, Deezer, Tidal, Qobuz) using Logitech Media Server - a.k.a LMS with **multi-room** audio synchronization.
- LMS can be extended by numerous plugins and can be controlled using a Web browser or dedicated applications (iPhone, Android).
- It can also send audio to UPnP, Sonos, ChromeCast and AirPlay speakers/devices.

All ESP32 based boards are tested with [Squeezelite-ESP32](https://github.com/sle118/squeezelite-esp32) software, that can be flashed using nothing but web-browser. You can use [Squeezelite-ESP32 installer](https://sle118.github.io/squeezelite-esp32-installer/) for that purpose.

### How to flash and configure ("ESP Audio Duo", "HiFi-ESP" and "Louder ESP")

Use [Squeezelite-ESP32 installer](https://sle118.github.io/squeezelite-esp32-installer/) to flash firmware first. 

|   |   |
|---|---|
| Use `Generic/I2S` profile | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/134eea60-149b-48d6-90cb-e68b421b61b2) |  
| Connect device to USB port and select if from the list | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/5cb87b71-ff9c-4aa6-acdc-602b9c918e67) ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/38a313c6-5b38-4b63-9e4b-209ffd960c6b)| 
| Press `Flash` and wait around 2 minutes  | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/e93f2106-b6e2-4625-92d1-a906c8375fd7) | 
| (Optional) You may enter serial console to get more information | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/2d9c3b58-f4bf-49a5-8c6b-fc12c8cc8d10) |
| Device is in recovery mode. Connect to `squeezelite-299fac` wifi network with `squeezelite` password (your network name suffix will be different) | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/2763663c-dbc9-4c71-af12-0a6fb9c2d94d) |
| When redirected to captive portal let device scan wifi network and provide valid credentials | <img src="https://github.com/sonocotta/esp32-audio-dock/assets/5459747/d2540ffb-d1d1-4441-a2b1-bbd6b8ad608f" width="30%" /> <img src="https://github.com/sonocotta/esp32-audio-dock/assets/5459747/b21f30e6-8899-46bc-b047-23281cae52b8" width="30%" /> <img src="https://github.com/sonocotta/esp32-audio-dock/assets/5459747/5dd1a1f6-0c6d-4045-b135-1d8cdd077161" width="30%" /> |
| You can use provided IP address (http://192.168.1.99/ on the screenshot) to access settings page |  ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/e3bbf910-1a5c-4c58-bd4e-c348ef0a91e5)
| ["ESP Audio Duo", "HiFi-ESP"] <br /><br /> Navigate to **Hardware** section and provide following updates in the **DAC Options** <br/><br /> DAC model: `I2S` <br/> Clock GPIO: `26` <br/> Word Select GPIO: `25` <br/> Data GPIO: `22` <br/> <br /> Press `Save` button |  ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/f52e3a05-abe6-40d7-98ac-212bff6c431f)
| ["Louder ESP"] <br /><br /> Navigate to **NVS Editor** section and provide following updates <br /><br /> dac_config: `model=I2S,bck=26,ws=25,do=22,sda=21,scl=27,i2c=45` <br /> (STEREO, [BTL mode](#btl-and-pbtl-mode)) dac_controlset: `{"init":[{"reg":3,"val":2},{"reg":3,"val":3}],"poweron":[{"reg":3,"val":3}],"poweroff":[{"reg":3,"val":0}]}` <br /> (MONO, [PBTL mode](#btl-and-pbtl-mode)) dac_controlset: `{"init":[{"reg":3,"val":2},{"reg":3,"val":3},{"reg":2,"val":4}],"poweron":[{"reg":3,"val":3}],"poweroff":[{"reg":3,"val":0}]}` <br /> i2c_config: `scl=27,sda=21,speed=400000,port=1` <br /> set_GPIO: `33=vcc` <br/><br /> Press `Commit` button |  ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/cac2a1cc-7216-47c9-97b2-6a72c6559165)
| (Optional) You may change device names to something close to you heart| ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/adc1fff1-8572-4fe5-9d88-943d86a3fb11)
| Exit recovery | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/c54b18fa-c995-4e67-bced-820f8bce5fe6)
  
You can use it now
| Bluetooth  | Spotify Connect  | AirPlay | LMS Renderer  |
|---|---|---|---|
| ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/cd0e7cb2-4a15-48fc-b308-0281e414619e)| ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/edcb5a3b-bead-44d8-b51d-4c36ed19b7da)| ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/20586bb4-bc51-4cfb-802a-c6072987c1da)| ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/dfdb89dd-755b-42fe-a381-a92011f9c681)


## Hardware

![image](https://user-images.githubusercontent.com/5459747/225272625-777fa75d-bccc-427c-a861-e01784543c87.png)

Please visit [hardware](/hardware/) section for board schematics and PCB designs. Note that PCB are shared as multi-layer PDFs.

### ESP Audio Solo

| Image  | Legend  |
|---|---|
| ![image](https://user-images.githubusercontent.com/5459747/225284415-e778cd0f-4549-46fb-a25a-a7e58b23b6f8.png) | ![image](https://user-images.githubusercontent.com/5459747/225284233-da43e71b-976a-4356-a562-d97d42c3e817.png) [MAX98357](https://www.analog.com/en/products/max98357a.html) DAC <br/> ![image](https://user-images.githubusercontent.com/5459747/225284300-ff5c3ced-1a0f-4658-bafc-9b5ab7c43811.png) Speaker Terminal  |

### ESP Audio Duo

| Image  | Legend  |
|---|---|
| ![image](https://user-images.githubusercontent.com/5459747/225284680-72c9de9e-d5bc-4b68-9aa6-d070b52da3e0.png) | ![image](https://user-images.githubusercontent.com/5459747/225284233-da43e71b-976a-4356-a562-d97d42c3e817.png) [MAX98357](https://www.analog.com/en/products/max98357a.html) DAC <br/> ![image](https://user-images.githubusercontent.com/5459747/225284300-ff5c3ced-1a0f-4658-bafc-9b5ab7c43811.png) Speaker Terminals <br/> ![image](https://user-images.githubusercontent.com/5459747/225284781-8a9ab413-24d4-49c4-b7b6-f21593f564be.png) 8MB PSRAM IC  |

### HiFi-ESP

| Image  | Legend  |
|---|---|
| ![image](https://user-images.githubusercontent.com/5459747/225285266-be88b0ee-0d24-4246-86ed-d6f48b8b53f0.png) | ![image](https://user-images.githubusercontent.com/5459747/225284233-da43e71b-976a-4356-a562-d97d42c3e817.png) [PCM5100A](https://www.ti.com/product/PCM5100A) DAC <br/> ![image](https://user-images.githubusercontent.com/5459747/225284300-ff5c3ced-1a0f-4658-bafc-9b5ab7c43811.png) Speaker Terminals <br/> ![image](https://user-images.githubusercontent.com/5459747/225284781-8a9ab413-24d4-49c4-b7b6-f21593f564be.png) 8MB PSRAM IC <br/> ![image](https://user-images.githubusercontent.com/5459747/225285323-7fb37cfd-da4e-4ec3-bc1e-34ffdee6af7e.png) Ultra-Low noise LDO 3V3 Voltage regulator |

### Louder ESP

| Image  | Legend  |
|---|---|
| ![image](https://user-images.githubusercontent.com/5459747/225285681-2a0c9948-7879-4eba-aa25-e042851eddf0.png) | ![image](https://user-images.githubusercontent.com/5459747/225284233-da43e71b-976a-4356-a562-d97d42c3e817.png) [TAS5805M](https://www.ti.com/product/TAS5805M) DAC <br/> ![image](https://user-images.githubusercontent.com/5459747/225284300-ff5c3ced-1a0f-4658-bafc-9b5ab7c43811.png) Speaker Terminals <br/> ![image](https://user-images.githubusercontent.com/5459747/225284781-8a9ab413-24d4-49c4-b7b6-f21593f564be.png) 8MB PSRAM IC <br/> ![image](https://user-images.githubusercontent.com/5459747/225285323-7fb37cfd-da4e-4ec3-bc1e-34ffdee6af7e.png) 3V3 Drop-Down voltage regulator (powers ESP32) <br/> ![image](https://user-images.githubusercontent.com/5459747/225285837-a7c99f60-7faa-4250-8168-b10ac963df1c.png) Input Voltage terminal |
| ![image](https://github.com/sonocotta/esp32-audio-dock/assets/98712315/6de133de-de03-4f95-bf70-996191733ec4) (REV B, C, D) |![image](https://user-images.githubusercontent.com/5459747/225284233-da43e71b-976a-4356-a562-d97d42c3e817.png) [TAS5805M](https://www.ti.com/product/TAS5805M) DAC <br/> ![image](https://user-images.githubusercontent.com/5459747/225284300-ff5c3ced-1a0f-4658-bafc-9b5ab7c43811.png) Speaker Terminals <br/> - 8MB PSRAM IC (Hidden under ESP32 module) <br/> - 3V3 Drop-Down voltage regulator (powers ESP32, hidden under ESP32 module) <br/> ![image](https://user-images.githubusercontent.com/5459747/225285837-a7c99f60-7faa-4250-8168-b10ac963df1c.png) Input Voltage terminal 

### BTL and PBTL mode

[TAS5805M DAC](https://www.ti.com/lit/ds/symlink/tas5805m.pdf?ts=1701767947387) Allows 2 modes of operation. 

|  | BTL | PBTL |
|---|---|---|
| Descriotion | Bridge Tied Load, Stereo | Parallel Bridge Tied Load, Stereo |
| Rated Power | 2×23W (8-Ω, 21 V, THD+N=1%) | 45W (4-Ω, 21 V, THD+N=1%) |
| Schematics | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/e7ada8c0-c906-4c08-ae99-be9dfe907574) | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/55f5315a-03eb-47c8-9aea-51e3eb3757fe)
| Speaker Connection | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/eca2cf1e-ebe0-4684-9aa2-1cc193e0982f) | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/ee5b4517-3799-43a7-8d10-0a2f3a425c81) 


## Where to buy

In limited quantities possible to buy at Tindie
- [ESP Audio Dock](https://www.tindie.com/products/sonocotta/esp-audio-dock/)
- [Louder ESP32](https://www.tindie.com/products/sonocotta/louder-esp32/)

## Links
