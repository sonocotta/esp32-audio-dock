# ESP32 Audio Docks and Louder ESP

![Open Source Hardware](/images/open-source-hardware-logo.png)
![Open Source Software](/images/open-source-software-logo.png)

ESP32 Audio Docks is a range of extension boards (i.e. docks) that allow you to develop Audio solutions based on ESP32 chips. These were created to make Audio development entry as easy and inexpensive as possible. 

![image](https://user-images.githubusercontent.com/5459747/225271619-35ba0f99-fdd1-496b-b305-26e397df4460.png)

## Motivation

I spent the last few years developing different solutions based on ESP devices. It all started with ESP8266, where CPU power is not really sufficient to do real-time decoding, so you're limited to a rather simple ding-dong business. Then ESP32 came, bringing two much more capable cores, so you have a powerhouse to handle communication and decoding at the same time. Perhaps most importantly it also came with SPIRAM, so you can do decent buffering (essential for streamed content). 

Now new ESP32 C-Series and S-Series chips are entering the market, and their potential is mostly unrealized as of today.

I created those docks, to be able to quickly prototype for the whole range of ESP8266 and ESP32 chips, starting with the simplest finger-sized toys and going all the way up to full-sized speakers.

## Features

|             | ESP Audio Solo                                      | ESP Audio Duo                                     | Hifi ESP                    | Louder ESP                                            |
|-------------|-----------------------------------------------------|---------------------------------------------------|-----------------------------|-------------------------------------------------------|
| Image       | ![image](https://user-images.githubusercontent.com/5459747/225271839-3844b043-f3f4-4cb1-8a11-72c4f02aedce.png)                                              | ![image](https://user-images.githubusercontent.com/5459747/225271977-fd333283-66f0-448f-b748-e0ac94e25680.png)                                            | ![image](https://user-images.githubusercontent.com/5459747/225272052-c36d5b87-1b9a-439c-be69-94077135e72a.png)                      | ![image](https://user-images.githubusercontent.com/5459747/225272110-9433ff86-8912-47c5-a9f2-12bd7a0fe5a0.png)                                                |
| Docks with  | ESP8266, ESP32C3, ESP32S2 Mini modules              | ESP32 Mini Module                                 | ESP32 Mini Module           | ESP32 Mini Module                                     |
| DAC         | Single I2S DAC ([MAX98357](https://www.analog.com/en/products/max98357a.html)) with built in D-Class amp | Dual I2S DAC ([MAX98357](https://www.analog.com/en/products/max98357a.html)) with built in D-Class amp | [PCM5100A](https://www.ti.com/product/PCM5100A) 32bit Stereo DAC <br/> -100 dB typical noise level   | Stereo I2S DAC ([TAS5805M](https://www.ti.com/product/TAS5805M)) with   built in D-Class amp |
| Output (4Ω) | 3W                                                  | 2x 3W                                             | Non-amplified stereo output | 2x 15W at 12V Vin                                     |
| Output (8Ω) | 1.5W                                                | 2x 1.5W                                           | Non-amplified stereo output | 2x 23W at 22V Vin                                     |
| Adds        |                                                     | 8MB PSRAM (4MB usable)                            | 8MB PSRAM (4MB usable)      | 8MB PSRAM (4MB usable)                                |
| Connectivity | WiFi (ESP8266, ESP32S2) <br/> WiFi + BT5.0 (ESP32C3) |  WiFi + BT4.2 + BLE |  WiFi + BT4.2 + BLE |  WiFi + BT4.2 + BLE </br> Ethernet

### Onboard PSRAM

Audio streaming requires proper buffering to work, even with ESP32 500K of RAM it is a challenging task. For that reason, most of the projects will require WROVER modules that have onboard PSRAM chips. 

All ESP32 Docks have an 8MB PSRAM chip onboard, connected via a high-speed SDIO interface. This effectively **turns your regular WROOM module into WROVER module** with no effort required. Any code using PSRAM with just work out-of-the box.

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

Starting from revision E, Louder ESP exposes an Ethernet header, compatible with the popular [W5500](https://www.wiznet.io/product-item/w5500/) module 

|       | SPI CLK | SPI MOSI | SPI MISO | SPI CS | SPI HOST/SPEED | ETH INT | ETH RST | 
|-------|---------|----------|--------|----------|-----------|-------------|-------------|
| ESP32 | 18      | 23       | 19     | 05       | 2/20MHz        | 35          | 14          |

## Software samples

In the [software](/firmware) section two firmware examples are provided.

- [esp32-i2s-bare](/firmware/esp32-i2s-bare/) is base I2S implementation based on ESP-IDF implementation directly.
- [esp32-i2s-esp8266audio](/firmware/esp32-i2s-esp8266audio/) is based on excellent [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio) library (it works with the whole ESP range, don't get fooled by the name), providing minimum code implementation. 
- [esp32-i2s-web-radio](/firmware/esp32-i2s-web-radio/) is based on the [same library](https://github.com/earlephilhower/ESP8266Audio), providing minimum web-readio stream player. It expects a playlist as an input in the 'data' folder.
- [Squeezelite-ESP32](https://github.com/sle118/squeezelite-esp32) - see more details [below](#Squeezelite-ESP32)

### Platformio IDE
 
All samples are provided as [Plarformio IDE](https://platformio.org/platformio-ide) projects. After installing it, open the sample project. Select the proper environment based on your dock. Run the `Build` and `Upload` commands to install necessary tools and libraries, and build and upload the project to the board. Communication and proper upload method selection will be handled by IDE automatically. 

## Arduino IDE

Follow the [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio) library guide. Default settings will work out of the box with ESP8266 and ESP32 boards. For ESP32C3 and ESP32S2 board please adjust the pinout according to the above section

## Squeezelite-ESP32

Squeezelite-ESP32 is a multimedia software suite, that started as a renderer (or player) of LMS (Logitech Media Server). Now it is extended with 
- **Spotify** over-the-air player using SpotifyConnect (thanks to cspot)
- **AirPlay** controller (iPhone, iTunes ...) and enjoy synchronization multiroom as well (although it's AirPlay 1 only)
- Traditional **Bluetooth** device (iPhone, Android)

And LMS itself
- Streams your local music and connects to all major online music providers (Spotify, Deezer, Tidal, Qobuz) using Logitech Media Server - a.k.a LMS with **multi-room** audio synchronization.
- LMS can be extended by numerous plugins and can be controlled using a Web browser or dedicated applications (iPhone, Android).
- It can also send audio to UPnP, Sonos, Chromecast, and AirPlay speakers/devices.

All ESP32-based boards are tested with [Squeezelite-ESP32](https://github.com/sle118/squeezelite-esp32) software, which can be flashed using nothing but a web browser. You can use [Squeezelite-ESP32 installer](https://sonocotta.github.io/esp32-audio-dock/) for that purpose.

### How to flash and configure ("ESP Audio Duo", "HiFi-ESP" and "Louder ESP")

Use [Installer for ESP Audio Dock](https://sonocotta.github.io/esp32-audio-dock/) to flash firmware first. It has been preconfigured to work with ESP Audio boards and will configure all hardware automatically.

|   |   |
|---|---|
| Select the correct device first	 | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/47626d0a-c47a-4df7-80c1-e5aa82c9ab16)
| Connect the device to the USB port and select it from the list | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/def64924-7a93-41d1-a5e8-49f33285b31a)
| Press `Flash` and wait around 2 minutes  | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/ccdb0813-b5bc-43b1-b516-20e52849c5c4)
| (Optional) You may enter the serial console to get more information | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/89832ed4-4314-486f-b6a3-66efb46d3587)
| Device is in recovery mode. Connect to `squeezelite-299fac` wifi network with `squeezelite` password (your network name suffix will be different) | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/2763663c-dbc9-4c71-af12-0a6fb9c2d94d) |
| When redirected to the captive portal let the device scan wifi network and provide valid credentials | <img src="https://github.com/sonocotta/esp32-audio-dock/assets/5459747/d2540ffb-d1d1-4441-a2b1-bbd6b8ad608f" width="30%" /> <img src="https://github.com/sonocotta/esp32-audio-dock/assets/5459747/b21f30e6-8899-46bc-b047-23281cae52b8" width="30%" /> <img src="https://github.com/sonocotta/esp32-audio-dock/assets/5459747/5dd1a1f6-0c6d-4045-b135-1d8cdd077161" width="30%" /> |
| You can use provided IP address (http://192.168.1.99/ on the screenshot) to access settings page |  ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/e3bbf910-1a5c-4c58-bd4e-c348ef0a91e5)
| (Optional) You may change device names to something close to your heart| ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/962c2ced-c7c4-4a8a-b58f-72ad2f1f6b94)
| Exit recovery | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/0fa0bab1-c225-47c7-ab26-29d9eb98ffcf)

You can use it now
| Bluetooth  | Spotify Connect  | AirPlay | LMS Renderer  |
|---|---|---|---|
| ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/cd0e7cb2-4a15-48fc-b308-0281e414619e)| ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/edcb5a3b-bead-44d8-b51d-4c36ed19b7da)| ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/20586bb4-bc51-4cfb-802a-c6072987c1da)| ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/dfdb89dd-755b-42fe-a381-a92011f9c681)


## Hardware

![image](https://user-images.githubusercontent.com/5459747/225272625-777fa75d-bccc-427c-a861-e01784543c87.png)

Please visit the [hardware](/hardware/) section for board schematics and PCB designs. Note that PCBs are shared as multi-layer PDFs.

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

### Louder Optional SPI Ethernet module

| Image  | Legend  |
|---|---|
| Optional Ethernet header is exposed on the bottom side of the PCB | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/762bfea5-ffbf-493f-8217-8a47c146b304) |
| Use popular W5500 based module as displayed on the picture | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/090520a2-1ee7-45ec-81e4-86343b0aef25)

### BTL and PBTL mode

[TAS5805M DAC](https://www.ti.com/lit/ds/symlink/tas5805m.pdf?ts=1701767947387) Allows 2 modes of operation. 

|  | BTL | PBTL |
|---|---|---|
| Descriotion | Bridge Tied Load, Stereo | Parallel Bridge Tied Load, Stereo |
| Rated Power | 2×23W (8-Ω, 21 V, THD+N=1%) | 45W (4-Ω, 21 V, THD+N=1%) |
| Schematics | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/e7ada8c0-c906-4c08-ae99-be9dfe907574) | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/55f5315a-03eb-47c8-9aea-51e3eb3757fe)
| Speaker Connection | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/eca2cf1e-ebe0-4684-9aa2-1cc193e0982f) | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/ee5b4517-3799-43a7-8d10-0a2f3a425c81) 

Starting from Rev E, an additional header is exposed to allow datasheet-speced connectivity

| Image  | Legend  |
|---|---|
| Stereo Mode - leave open | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/8c06f495-f551-46ef-86c0-e390a6a63241) |
| Mono (PBTL) Mode, close horisontally | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/a5c78b6a-84c3-4546-afc8-5f65ca268157)

### Louder ESP power considerations

[Barrel jack used](https://www.lcsc.com/product-detail/AC-DC-Power-Connectors_XKB-Connectivity-DC-044D-2-5A-2-0-SMT_C397342.html) is spaced at 6mm hole/2mm pin, which is typically 5.5/2.5mm jack on the male side. 

![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/0b18f215-e4ce-4335-9217-d8859566c3a4)

The screw terminal is connected parallel to the barrel jack, you can use either interchangeably.

The power adapter specs depend on the speaker you're planning to use. DAC efficiency is close to 100%, so just take the power rating of your speaker (say 2x10w), and impedance (say 8 ohm) and you'd need  at least 9 volts rated at 1.2 amps per channel, round up to 3 total amps. 

It is not recommended to go beyond the voltage your speakers can take, otherwise amp will blow your speakers in no time. 

## Where to buy

You may support my work by ordering these products at Tindie and Elecrow
- [ESP Audio Dock](https://www.tindie.com/products/sonocotta/esp-audio-dock/) at Tindie
- [Louder ESP32](https://www.tindie.com/products/sonocotta/louder-esp32/) at Tindie
- [Louder ESP32](https://www.elecrow.com/louder-esp32.html) at Elecrow
