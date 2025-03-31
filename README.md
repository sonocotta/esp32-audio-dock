# ESP32 Audio Docks and Louder ESP

![Open Source Hardware](/images/open-source-hardware-logo.png)
![Open Source Software](/images/open-source-software-logo.png)
<a href="https://www.tindie.com/stores/sonocotta/?ref=offsite_badges&utm_source=sellers_andrey-malyshenko&utm_medium=badges&utm_campaign=badge_medium"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-mediums.png" alt="I sell on Tindie" width="150" height="78"></a>
<br />
[![Dev Chat](https://img.shields.io/discord/1233306441469657140?logo=discord&label=discord&style=flat-square)](https://discord.gg/PtnaAaQMpS)

ESP32 Audio Docks is a range of development boards (earlier docks) that allow you to develop Audio solutions based on ESP32 chips. These were created to make Audio development entry as easy and inexpensive as possible. 

<details>
  <summary>First generation docks</summary>
  
![image](https://user-images.githubusercontent.com/5459747/225271619-35ba0f99-fdd1-496b-b305-26e397df4460.png)

</details>

| **HiFi-ESP32** | **Loud-ESP32** |
|---|---|
| ![DSC_0009](https://github.com/user-attachments/assets/0ac16dd2-0bd2-42e4-9e07-c2dd8b2b0266) | ![DSC_0017](https://github.com/user-attachments/assets/94ffe10e-e206-4ced-aa2c-32b60508b280) | 
| **Amped-ESP32** | **Louder-ESP32** |
| ![DSC_0005](https://github.com/user-attachments/assets/e457b78c-c841-4764-90db-f25091f652ad) | ![DSC_0019](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/26c98a87-cd12-466d-990c-05dfb163390c)

## Table of Contents

- [ESP32 Audio Docks and Louder ESP](#esp32-audio-docks-and-louder-esp)
  - [Table of Contents](#table-of-contents)
  - [Motivation](#motivation)
  - [Features](#features)
    - [Onboard PSRAM](#onboard-psram)
  - [Boards Pinout](#boards-pinout)
    - [ESP Audio Solo](#esp-audio-solo)
    - [ESP Audio Duo](#esp-audio-duo)
    - [HiFi-ESP](#hifi-esp)
    - [Louder ESP](#louder-esp)
    - [HiFi-ESP32 and Amped-ESP32](#hifi-esp32-and-amped-esp32)
    - [Loud-ESP32](#loud-esp32)
    - [Louder-ESP32](#louder-esp32)
    - [Ethernet (all boards)](#ethernet-all-boards)
    - [Optional peripheral (all boards)](#optional-peripheral-all-boards)
  - [Software samples](#software-samples)
    - [Platformio IDE](#platformio-ide)
    - [Arduino IDE](#arduino-ide)
    - [ESPHome and Home Assistant](#esphome-and-home-assistant)
      - [Bonus - automation example](#bonus---automation-example)
    - [Squeezelite-ESP32](#squeezelite-esp32)
      - [How to flash and configure ("ESP Audio Duo", "HiFi-ESP" and "Louder ESP")](#how-to-flash-and-configure-esp-audio-duo-hifi-esp-and-louder-esp)
      - [Ethernet configuration](#ethernet-configuration)
        - [ESP32](#esp32)
        - [ESP32S3](#esp32s3)
  - [Hardware](#hardware)
    - [ESP Audio Solo](#esp-audio-solo-1)
    - [ESP Audio Duo](#esp-audio-duo-1)
    - [HiFi-ESP](#hifi-esp-1)
    - [Louder ESP](#louder-esp-1)
    - [HiFi-ESP32](#hifi-esp32)
    - [Loud-ESP32](#loud-esp32-1)
    - [Amped-ESP32](#amped-esp32)
    - [Louder-ESP32](#louder-esp32-1)
    - [Optional SPI Ethernet module](#optional-spi-ethernet-module)
        - [ESP32](#esp32-1)
        - [ESP32S3](#esp32s3-1)
    - [BTL and PBTL mode (TAS5805M DAC)](#btl-and-pbtl-mode-tas5805m-dac)
    - [TAS5805M DSP capabilities](#tas5805m-dsp-capabilities)
    - [Louder-ESP32 and Amped-ESP32 power considerations](#louder-esp32-and-amped-esp32-power-considerations)
    - [Case](#case)
  - [Where to buy](#where-to-buy)

## Motivation

I spent the last few years developing different solutions based on ESP devices. It all started with ESP8266, where CPU power is not really sufficient to do real-time decoding, so you're limited to a rather simple ding-dong business. Then ESP32 came, bringing two much more capable cores, so you have a powerhouse to handle communication and decoding at the same time. Perhaps most importantly, it also came with SPIRAM, so you can do decent buffering (essential for streamed content). Now, new ESP32 C-Series and S-Series chips are entering the market, and their potential is mostly unrealized as of today.

I created those docks and subsequently development boards to be able to quickly prototype for the whole range of ESP8266 and ESP32 chips, starting with the simplest finger-sized toys and going all the way up to full-sized speakers.

## HiFi-ESP32 

The HiFi-ESP32 is a first-in-line product that uses the legendary PCM5100 series DAC with supreme audio quality. It exposes line-level output that you can plug into a stereo amplifier. Analog power comes through an Ultra-low-noise LDO, making sure no interference from the MCU comes through to your speakers. Spend as much as you need on the external amp to deliver the sound you like (personally I prefer late 80's audio gear).

![DSC_0002](https://github.com/user-attachments/assets/d025ef42-daa3-4ad0-aeec-6ddf309c267b)

## Loud-ESP32

The Loud-ESP32 uses a dual MAX98357 HiFi DAC with a built-in highly efficient D-class amp to deliver 3 to 5W of music power directly to your speakers. It is not too loud, but also very simple to use and fun to play with. When DAC is not in use, it goes into shutdown mode, making sure no hissing will keep you up at night. It powers from a standard USB-C power source, like a phone charger, etc.

![DSC_0002](https://github.com/user-attachments/assets/7d351d02-7e7f-4974-9a12-ee353c239654) 

## Amped-ESP32

The PCM5100 HiFi DAC is combined with a highly efficient TPA3110D2 D-class amplifier. It brings all the best from the HiFi model and adds an onboard amp to form a complete solution that can be paired with speakers directly. It uses an external power source to feed hungry amps and the host MCU using an onboard drop-down converter. It has similar power capabilities to the Louder model, but it is much simpler to use since it only needs a valid I2S signal to operate, so a simple book example code will do it.

![DSC_0003](https://github.com/user-attachments/assets/447a628c-9225-4beb-b8cc-054cc1d1a20d)

## Louder-ESP32

The Louder-ESP32 is a top-of-the-range model that uses a modern, highly capable TAS5805M DAC and is aimed to be paired with medium-to-large speaker systems. With 25W per channel stereo output, it packs a punch and can easily enliven living quarters or dorm rooms. It is highly efficient, but much more demanding for power when cranked; therefore, it also uses an external power adapter using a standard barrel jack. This DAC has a built-in DSP, so you can have a lot of fun with complex EQ, soft-clipping, DRC compression, and AGL tools among other things.

![DSC_0013](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/46ea4f10-c363-4623-b5d6-29e1135e5983)

## Features

<details>
  <summary>First generation docks</summary>

| ESP Audio Solo | ESP Audio Duo | Hifi ESP | Louder ESP |
|---|---|---|---|
| ![image](https://user-images.githubusercontent.com/5459747/225271839-3844b043-f3f4-4cb1-8a11-72c4f02aedce.png) | ![image](https://user-images.githubusercontent.com/5459747/225271977-fd333283-66f0-448f-b748-e0ac94e25680.png) | ![image](https://user-images.githubusercontent.com/5459747/225272052-c36d5b87-1b9a-439c-be69-94077135e72a.png) | ![image](https://user-images.githubusercontent.com/5459747/225272110-9433ff86-8912-47c5-a9f2-12bd7a0fe5a0.png) |
| ESP8266, ESP32C3, ESP32S2 Mini modules | ESP32 Mini Module | ESP32 Mini Module | ESP32 Mini Module |
| Single I2S DAC ([MAX98357](https://www.analog.com/en/products/max98357a.html)) with built in D-Class amp | Dual I2S DAC ([MAX98357](https://www.analog.com/en/products/max98357a.html)) with built in D-Class amp | [PCM5100A](https://www.ti.com/product/PCM5100A) 32bit Stereo DAC  -100 dB typical noise level | Stereo I2S DAC ([TAS5805M](https://www.ti.com/product/TAS5805M)) with   built in D-Class amp |
| 3W | 2x 3W | Non-amplified stereo output | 2x 32W (4Ω, 1% THD+N) |
| 1.5W | 2x 1.5W | Non-amplified stereo output | 2x 22W (8Ω, 1% THD+N) |
|  | 8MB PSRAM (4MB usable) | 8MB PSRAM (4MB usable) | 8MB PSRAM (4MB usable) |
| WiFi (ESP8266, ESP32S2)  WiFi + BT5.0 (ESP32C3) | WiFi + BT4.2 + BLE | WiFi + BT4.2 + BLE | WiFi + BT4.2 + BLE  Ethernet |

</details>

|  | HiFi-ESP32 | Loud-ESP32 | Amped-ESP32 | Louder-ESP32 |
|---|---|---|---|---|
| Image (ESP32 | ![DSC_0002](https://github.com/user-attachments/assets/d025ef42-daa3-4ad0-aeec-6ddf309c267b) | ![DSC_0002](https://github.com/user-attachments/assets/7d351d02-7e7f-4974-9a12-ee353c239654) | ![DSC_0003](https://github.com/user-attachments/assets/447a628c-9225-4beb-b8cc-054cc1d1a20d) | ![DSC_0013](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/46ea4f10-c363-4623-b5d6-29e1135e5983) |
| MCU | ESP32-WROVER-N8R8 onboard | ESP32-WROVER-N8R8 onboard | ESP32-WROVER-N8R8 onboard | ESP32-WROVER-N8R8 onboard |
| Image (ESP32-S3) | ![DSC_0005](https://github.com/user-attachments/assets/6f0482a2-7e08-475c-b6f0-0fe631a8e2f4) | ![DSC_0009](https://github.com/user-attachments/assets/e732f7a9-77e5-4182-b808-bf12ff35a8b7) | coming soon | ![DSC_0012](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/0e0c2146-79da-41e7-96da-63cf37637bce) |
| MCU (S3) | ESP32-S3-WROOM-N8R8 onboard | ESP32-S3-WROOM-N8R8 onboard | ESP32-S3-WROOM-N8R8 onboard | ESP32-S3-WROOM-N8R8 onboard |
| DAC | [PCM5100A](https://www.ti.com/product/PCM5100A) 32bit Stereo DAC  -100 dB typical noise level | Dual I2S DAC ([MAX98357](https://www.analog.com/en/products/max98357a.html)) with built in D-Class amp | [PCM5100A](https://www.ti.com/product/PCM5100A) 32bit Stereo DAC working with <br /> [TPA3110D2](https://www.ti.com/product/TPA3110D2) D-Class amp | Stereo I2S DAC ([TAS5805M](https://www.ti.com/product/TAS5805M)) with   built in D-Class amp |
| Output (4Ω) | Non-amplified stereo output, 2.1V RMS | 2x 5W | 2x 22W (4Ω, 1% THD+N) at 16V <br /> 2x 32W (4Ω, 1% THD+N) at 20V <br/> 1x 40W (4Ω, 1% THD+N) at 20V (bridged) | 2x 22W (4Ω, 1% THD+N) at 16V <br /> 2x 32W (4Ω, 1% THD+N) at 20V <br/> 1x 40W (4Ω, 1% THD+N) at 20V (bridged) |
| Output (8Ω) | Non-amplified stereo output | 2x 3W | 2x 25W (8Ω, 1% THD+N) at 22V | 2x 25W (8Ω, 1% THD+N) at 22V |
| PSRAM | ESP32: 8MB PSRAM (4MB usable) over 40MHz SPI<br/>ESP32S3: 8MB PSRAM over 80MHz QSPI | ESP32: 8MB PSRAM (4MB usable) over 40MHz SPI<br/>ESP32S3: 8MB PSRAM over 80MHz QSPI | ESP32: 8MB PSRAM (4MB usable) over 40MHz SPI<br/>ESP32S3: 8MB PSRAM over 80MHz QSPI | ESP32: 8MB PSRAM (4MB usable) over 40MHz SPI<br/>ESP32S3: 8MB PSRAM over 80MHz QSPI |
| Power | 5V over USB-C, 2x [LP5907](https://www.ti.com/lit/ds/symlink/lp5907.pdf) 3.3 V Ultra-Low-Noise LDO for analog section | 5V (up to 2.5A) from USB-C | Up to 26V from external PSU | Up to 26V from external PSU |
| Connectivity | WiFi + BT4.2 (except S3) + BLE <br/> Ethernet (optional module) | WiFi + BT4.2 (except S3) + BLE <br/> Ethernet (optional module) | WiFi + BT4.2 (except S3) + BLE <br/> Ethernet (optional module) | WiFi + BT4.2 (except S3) + BLE <br/> Ethernet (optional module) |

### Onboard PSRAM

Audio streaming requires proper buffering to work, even with ESP32 500K of RAM it is a challenging task. For that reason, most of the projects will require WROVER modules that have onboard PSRAM chips.  All ESP32 Audio boards have an 8MB PSRAM chip onboard, connected via a high-speed interface. Any code using PSRAM with just work out-of-the box.

## Boards Pinout

<details>
  <summary>First generation docks</summary>

### ESP Audio Solo

|         | I2S CLK | I2S DATA | I2S WS |
|---------|---------|----------|--------|
| ESP8266 | 15      | 3        | 2      |
| ESP32-C3 | 5       | 20       | 6      |
| ESP32-S2 | 12      | 37       | 16     |

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
| ESP32-S3 | 14      | 16       | 15     | -       | -        | 8          | 9          | 17           | 18            |

</details>

### HiFi-ESP32 and Amped-ESP32

|       | I2S CLK | I2S DATA | I2S WS | PSRAM RESERVED | 
|-------|---------|----------|--------|----------|
| ESP32 | 26      | 22       | 25     | 16, 17        |
| ESP32-S3 | 14      | 16       | 15     | 35, 36, 37 | 


### Loud-ESP32

|       | I2S CLK | I2S DATA | I2S WS | DAC EN | PSRAM RESERVED | 
|-------|---------|----------|--------|----------|--------------|
| ESP32 | 26      | 22       | 25     |    13    |  16, 17      |
| ESP32-S3 | 14   | 16       | 15     |     8    |   35, 36, 37 | 


### Louder-ESP32

|       | I2S CLK | I2S DATA | I2S WS | PSRAM RESERVED |  TAS5805 SDA | TAS5805 SCL | TAS5805 PWDN | TAS5805 FAULT |
|-------|---------|----------|--------|----------------|--------------|-------------|--------------|---------------|
| ESP32 | 26      | 22       | 25     | 16, 1          | 21           | 27          | 33           | 34            |
| ESP32-S3 | 14   | 16       | 15     | 35, 36, 37     | 8            | 9           | 17           | 18            |

### Ethernet (all boards)

|       | SPI CLK | SPI MOSI | SPI MISO | SPI CS | SPI HOST/SPEED | ETH INT     | ETH RST     |  
|-------|---------|----------|--------|----------|----------------|-------------|-------------|
| ESP32 | 18      | 23       | 19     | 05       | 2/20MHz        | 35          | 14          | 
| ESP32-S3 | 12   | 11       | 13     | 10       | SPI2/20MHz     | 6           | 5           |  

### Optional peripheral (all boards)

|       |  IR IN  | RGB OUT  | OLED SPI HOST/SPEED | OLED SPI CLK | OLED SPI MOSI | OLED SPI MISO | OLED SPI CS | OLED SPI DC | OLED RST | 
|-------|---------|----------|---------------------|--------------|---------------|---------------|-------------|-------------|-------------|
| ESP32 | 39      | 12       | 2/20MHz             | 18           | 23            | 19            | 15          | 4           | 32          |
| ESP32-S3 | 7    | 9        | SPI2/20MHz          | 12           | 11            | 13            | 39          | (37)        | 38          |


## Software samples

In the [software](/firmware) section two firmware examples are provided.

- [esp32-i2s-bare](/firmware/esp32-i2s-bare/) is base I2S implementation based on ESP-IDF implementation directly.
- [esp32-i2s-esp8266audio](/firmware/esp32-i2s-esp8266audio/) is based on excellent [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio) library (it works with the whole ESP range, don't get fooled by the name), providing minimum code implementation. 
- [esp32-i2s-web-radio](/firmware/esp32-i2s-web-radio/) is based on the [same library](https://github.com/earlephilhower/ESP8266Audio), providing minimum web-readio stream player. It expects a playlist as an input in the 'data' folder.
- [Squeezelite-ESP32](https://github.com/sle118/squeezelite-esp32) - see more details [below](#Squeezelite-ESP32)

### Platformio IDE
 
All samples are provided as [Plarformio IDE](https://platformio.org/platformio-ide) projects. After installing it, open the sample project. Select the proper environment based on your dock. Run the `Build` and `Upload` commands to install necessary tools and libraries, and build and upload the project to the board. Communication and proper upload method selection will be handled by IDE automatically. 

### Arduino IDE

Follow the [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio) library guide. Default settings will work out of the box with ESP8266 and ESP32 boards. For ESP32C3 and ESP32S2 board please adjust the pinout according to the above section

### ESPHome and Home Assistant

Being an ESP32-based device, you can easily integrate it into your Home Assistant using ESPHome. Start with [esphome web installer](https://web.esphome.io/), which will give you ESPHome base install and WiFi configuration in minutes. Some S2/S3 boards have issues with we-installer, you may need to use [Adafruit flasher](https://adafruit.github.io/Adafruit_WebSerial_ESPTool/) instead with binaries pulled from the HA.

<details>
  <summary>Install instructions</summary>
  
![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/abde451b-5619-4b32-a024-3f680999567f)
![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/fc567914-0d0a-4402-a5c5-ddfad77f2b83)


Next, navigate to your Home Assistant (assuming you have your [ESPHome integration](https://esphome.io/guides/getting_started_hassio.html) installed), and adopt the newly created node

![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/299fb7ab-003e-4259-b0c1-9d13dd3e54ba)

[ESPHome](/firmware/esphome/) will give you ESPHome configs for Solo board running with ESP32-S2/S3, as well as Duo/HiFi-ESP and Louder ESP working with ESP32.

A few words of explanation.

- `media_player` publishes the media player into the Home Assistant, so you can use it together with the native player or Music Assistant. You have a volume knob in the HA as well.
- ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/f73a7347-672f-4dfc-afb8-35c7eb78e464)
- Volume is set up to 50% at the start of the player's play. Especially for Louder-ESP32, this is helpful :) 

#### Bonus - automation example

The true power of the native speaker in the eHA is the use of automation. One example that I find useful. This simple automation will be pronounced every hour between 8 AM and 9 PM. Another one is used to pronounce bedtime, you get the point...

![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/fd25fb6a-19a7-4957-a2cb-a723723fde4d)

</details>

### Squeezelite-ESP32

Squeezelite-ESP32 is a multimedia software suite that started as a renderer (or player) of LMS (Logitech Media Server). Now it is extended with 
- **Spotify** over-the-air player using SpotifyConnect (thanks to cspot)
- **AirPlay** controller (iPhone, iTunes ...) and enjoy synchronization multiroom as well (although it's AirPlay 1 only)
- Traditional **Bluetooth** device (iPhone, Android)

And LMS itself
- Streams your local music and connects to all major online music providers (Spotify, Deezer, Tidal, Qobuz) using Logitech Media Server - a.k.a LMS with **multi-room** audio synchronization.
- LMS can be extended by numerous plugins and can be controlled using a Web browser or dedicated applications (iPhone, Android).
- It can also send audio to UPnP, Sonos, Chromecast, and AirPlay speakers/devices.

All ESP32-based boards are tested with [Squeezelite-ESP32](https://github.com/sle118/squeezelite-esp32) software, which can be flashed using nothing but a web browser. You can use [Squeezelite-ESP32 installer](https://sonocotta.github.io/esp32-audio-dock/) for that purpose.

#### How to flash and configure ("ESP Audio Duo", "HiFi-ESP" and "Louder ESP")

Use [Installer for ESP Audio Dock](https://sonocotta.github.io/esp32-audio-dock/) to flash firmware first. It has been preconfigured to work with ESP Audio boards and will configure all hardware automatically.

<details>
  <summary>Install instructions</summary>
  
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

</details>

#### Ethernet configuration

If you have optional Ethernet on the board, please put this config in the NVS settings

##### ESP32

```
eth_config = model=w5500,cs=5,speed=20000000,intr=35,rst=14
spi_config = mosi=23,clk=18,host=2,miso=19
```

##### ESP32S3

```
eth_config = model=w5500,cs=10,speed=20000000,intr=6,rst=5
spi_config = mosi=11,clk=12,host=2,miso=13
```

## Hardware

Please visit the [hardware](/hardware/) section for board schematics and PCB designs. Note that PCBs are shared as multi-layer PDFs.

<details>
  <summary>First generation docks</summary>

![image](https://user-images.githubusercontent.com/5459747/225272625-777fa75d-bccc-427c-a861-e01784543c87.png)

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

</details>

### HiFi-ESP32

| ESP32  | ESP32-S3
|---|---|
| ![image](https://github.com/user-attachments/assets/6cb02a5b-a0ef-4dce-b101-1cd92f6addc8)  | ![image](https://github.com/user-attachments/assets/17c488ec-65b1-46df-a6f6-c0abaa99830c)  |

### Loud-ESP32

| ESP32  | ESP32-S3
|---|---|
| ![image](https://github.com/user-attachments/assets/eb558181-9d9a-4b62-9acb-b8de41450554) | ![image](https://github.com/user-attachments/assets/99a27eb2-72de-4a96-8b84-8d4426176222)

### Amped-ESP32

| ESP32  | ESP32-S3
|---|---|
| ![image](https://github.com/user-attachments/assets/6fd602a7-909f-4b33-8be1-623d2fec443b) | coming soon

### Louder-ESP32

| ESP32  | ESP32-S3
|---|---|
| ![DSC_0013_small JPG-mh](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/c4947d1b-76f1-468b-81d9-68b46ef42851) | ![DSC_0012_small JPG-mh](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/6716a624-e44d-4f83-a8ee-91ab67b8411a)


### Optional SPI Ethernet module

Every board has a header that allows for soldering in a W5500 SPI Ethernet module, which is very easy to find. The only downside is that with the module installed board will not fit the case, unless it is cut to accommodate extra height.

| HiFi-ESP32(S3) | Loud-ESP32(S3) | 
|---|---|
| ![DSC_0015](https://github.com/user-attachments/assets/7c71f12a-744c-4d25-bb3b-492df4cf5c78) | ![DSC_0026](https://github.com/user-attachments/assets/e688d75d-8e5d-4e58-8fec-fd900e44b3d8)

squeezelite-esp32 nvs settings that you need to apply to enable it

##### ESP32

```
eth_config = model=w5500,cs=5,speed=20000000,intr=35,rst=14
spi_config = mosi=23,clk=18,host=2,miso=19
```

##### ESP32S3

```
eth_config = model=w5500,cs=10,speed=20000000,intr=6,rst=5
spi_config = mosi=11,clk=12,host=2,miso=13
```

### BTL and PBTL mode (TAS5805M DAC)

[TAS5805M DAC](https://www.ti.com/lit/ds/symlink/tas5805m.pdf?ts=1701767947387) Allows 2 modes of operation - BTL (stereo) and PBTL (parallel, or mono). In Mono, the amp will use a completely different modulation scheme and basically will fully synchronize output drivers. Jumpers on the board allow both output drivers to connect to the same speaker. The most important step is to inform the Amp to change modulation in the first place via I2C command. In the case of sqeezelite DAC control set value is the following:
```
dac_controlset: `{"init":[{"reg":3,"val":2},{"reg":3,"val":3},{"reg":2,"val":4}],"poweron":[{"reg":3,"val":3}],"poweroff":[{"reg":3,"val":0}]}`
```
compared to the default:
```
dac_controlset: `{"init":[{"reg":3,"val":2},{"reg":3,"val":3}],"poweron":[{"reg":3,"val":3}],"poweroff":[{"reg":3,"val":0}]}`

```

One can test audio with a single speaker connected between L and R terminals (plus on one side and minus on the other). Optionally, jumpers on the board will effectively connect the second driver in parallel, doubling the current capability.

Important point, this simple setup will send only one channel to the output, that’s just how the basic DAC setup works. In case you want true mono (L + R)/2 or pure R or L audio, you need to apply a mixer configuration. Full config looks like below (thanks @frdfsnlght for helping me [here](https://github.com/sonocotta/esp32-audio-dock/issues/27))

Single speaker (PBTL mode), mono mix (L+R)/2:
```
{"init":[{"reg":3,"val":2},{"reg":3,"val":3},{"reg":2,"val":4},{"reg":0,"val":0},{"reg":127,"val":140},{"reg":0,"val":41},{"reg":24,"val":[0,64,38,231]},{"reg":28,"val":[0,64,38,231]},{"reg":32,"val":[0,0,0,0]},{"reg":36,"val":[0,0,0,0]},{"reg":0,"val":0},{"reg":127,"val":0}],"poweron":[{"reg":3,"val":3}],"poweroff":[{"reg":3,"val":0}]} 
```

Single speaker (PBTL mode), right input only:
```
{"init":[{"reg":3,"val":2},{"reg":3,"val":3},{"reg":2,"val":4},{"reg":0,"val":0},{"reg":127,"val":140},{"reg":0,"val":41},{"reg":24,"val":[0,128,0,0]},{"reg":28,"val":[0,0,0,0]},{"reg":32,"val":[0,0,0,0]},{"reg":36,"val":[0,0,0,0]},{"reg":0,"val":0},{"reg":127,"val":0}],"poweron":[{"reg":3,"val":3}],"poweroff":[{"reg":3,"val":0}]} 
```

Single speaker (PBTL mode), left input only:
```
{"init":[{"reg":3,"val":2},{"reg":3,"val":3},{"reg":2,"val":4},{"reg":0,"val":0},{"reg":127,"val":140},{"reg":0,"val":41},{"reg":24,"val":[0,0,0,0]},{"reg":28,"val":[0,128,0,0]},{"reg":32,"val":[0,0,0,0]},{"reg":36,"val":[0,0,0,0]},{"reg":0,"val":0},{"reg":127,"val":0}],"poweron":[{"reg":3,"val":3}],"poweroff":[{"reg":3,"val":0}]} 
```

|  | BTL | PBTL |
|---|---|---|
| Descriotion | Bridge Tied Load, Stereo | Parallel Bridge Tied Load, Mono |
| Rated Power | 2×23W (8-Ω, 21 V, THD+N=1%) | 45W (4-Ω, 21 V, THD+N=1%) |
| Schematics | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/e7ada8c0-c906-4c08-ae99-be9dfe907574) | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/55f5315a-03eb-47c8-9aea-51e3eb3757fe)
| Speaker Connection | ![image](https://github.com/user-attachments/assets/8e5e9c38-2696-419b-9c5b-d278c655b0db) | ![image](https://github.com/user-attachments/assets/8aba6273-84c4-45a8-9808-93317d794a44)

Starting from Rev E, an additional header is exposed to allow datasheet-specified connectivity 

| Image  | Legend  |
|---|---|
| Stereo Mode - leave open | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/8c06f495-f551-46ef-86c0-e390a6a63241) |
| Mono (PBTL) Mode, close horisontally | ![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/a5c78b6a-84c3-4546-afc8-5f65ca268157)

### TAS5805M DSP capabilities

The TAS5805M DAC has a very powerful DSP, which allows doing lots of data processing on the silicon, that otherwise would take a considerable part of your CPU time. As of the moment of writing, it is mostly an undiscovered part of the DAC, since unfortunately, TI is not making it very easy for developers. (A minute of complaint) To be more specific, you need to be (A) a proven hardware manufacturer to get access to the configuration software, namely PurePath. (B) You need to apply for a personal license and go through an approval process, and after a few weeks of waiting, you get access to the DAC configuration you asked for. (C) You find out that it will work with TI's own evaluation board, which will set you back $250 if you'd be able to find one. Otherwise, all you have is a list of I2C commands that you need to transfer to the device at your own cost. No wonder no one knows how to use it.

But moanings aside, what do you get after:

- Flexible input mixer with gain corrections
- 15 EQ with numerous filter configurations
- 3-band Dynamic Range Compression with flexible curve configuration
- Automatic Gain Limiter with flexible configuration
- Soft clipper
- and a few other things

At this moment, it is very experimental. In the perfect world, you should be able to adjust all of those settings to make your speaker-enclosure setup work the best it can, and even apply your room factors into the equation. But with the above disclaimer I can only deliver a limited set of configurations corresponding to the most common use cases:

- Stereo mode with enabled DRC (Loudness) and AGL settings
- Full range Mono mode with DRC (Loudness) and AGL settings
- Subwoofer Mono mode with a few filter frequency options
- Bi-Amp configuration with a few crossover frequency options

All of the above are available right now for experimentation. I'm keen to hear your feedback while I move forward with porting this to other software options

- [X] - Bare [I2S TAS5805M library](https://github.com/sonocotta/esp32-tas5805m-dac)
- [X] - [espragus-snapclient](https://sonocotta.github.io/esparagus-snapclient/) software
- [ ] - [squeezelite-esp32](https://sonocotta.github.io/esp32-audio-dock/) <- to do
- [ ] - flexible configurations with on-the-fly configuration changes

### Louder-ESP32 and Amped-ESP32 power considerations

[Barrel jack used](https://www.lcsc.com/product-detail/AC-DC-Power-Connectors_XKB-Connectivity-DC-044D-2-5A-2-0-SMT_C397342.html) is spaced at 6mm hole/2mm pin, which is typically 5.5/2.5mm jack on the male side. 

![image](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/0b18f215-e4ce-4335-9217-d8859566c3a4)

The screw terminal is connected parallel to the barrel jack, you can use either interchangeably.

On the latest boards (starting from Amped-ESP32), I switched to [barrel jack with thick middle pin](https://atta.szlcsc.com/upload/public/pdf/source/20200812/C720576_7B83670454B7C7E493B4E29DD30CFE1F.pdf) with a **2.5mm pin**, it’s a bit unusual but still common enough in the laptop world. It is far more comfortable in handling high currents, and importantly, much more sturdy and resistant to desoldering. 

![image](https://github.com/user-attachments/assets/59acba9e-b447-4724-a6a1-bf777f053787)

The power adapter specs depend on the speaker you're planning to use. DAC efficiency is close to 100%, so just take the power rating of your speaker (say 2x10w), and impedance (say 8 ohms), and you'd need  at least 9 volts rated at 1.2 amps per channel, round up to 3 total amps. 

It is not recommended to go beyond the voltage your speakers can handle, otherwise, the amp will blow your speakers in no time. 

### Case

HiFi-ESP32(S3), Loud-ESP32(S3), Amped-ESP32 and Louder-ESP32(S3) are mechanically compatible with Raspberry Pi 3/4 cases, tested with transparent ones. 

| Hifi-ESP32 | Loud-ESP32 |
|---|---|
| ![DSC_0013](https://github.com/user-attachments/assets/3eb6bb16-e103-40e1-8142-a239dc5271ca) | ![DSC_0019](https://github.com/user-attachments/assets/79b78c61-b6bf-454d-91f6-9eb513bc06d8) | 
|Amped-ESP32 | Louder-ESP32 |
| ![DSC_0007](https://github.com/user-attachments/assets/afc3c4b4-3f50-4755-b970-ad58130ec94d) | ![DSC_0001](https://github.com/sonocotta/esp32-audio-dock/assets/5459747/68d5c2ab-d5f7-4f66-8ff7-4301ddaab7ed)

Also, community members created a few 3-D printable designs for Louder-ESP32 boards that can be found below 

| #  | Image |
|----|----|
| [#1](https://www.printables.com/model/1058552-louder-esp32-s3-playeramplifier-case/comments) | ![image](https://github.com/user-attachments/assets/ad4a30d6-953b-461e-b108-9c6155ce2477)
| [#2](https://www.thingiverse.com/thing:6333131) | ![image](https://github.com/user-attachments/assets/6e37b6ce-443e-4067-8a7a-e3b49e5e8ad3)
| [#3](https://www.thingiverse.com/thing:6326927) | ![image](https://github.com/user-attachments/assets/cf2983fa-0c92-4798-9cb5-5e4e97d70970)


## Where to buy

You may support my work by ordering these products at Tindie and Elecrow
- [ESP Audio Dock](https://www.tindie.com/products/sonocotta/esp-audio-dock/) at Tindie
- [HiFi-ESP32 and HiFi-ESP32S3](https://www.tindie.com/products/sonocotta/hifi-esp32/)
- [Loud-ESP32 and Loud-ESP32S3](https://www.tindie.com/products/sonocotta/loud-esp32/)
- Amped-ESP32 - coming soon
- [Louder-ESP32 and Louder-ESP32S3](https://www.tindie.com/products/sonocotta/louder-esp32/) at Tindie
- [Louder ESP32](https://www.elecrow.com/louder-esp32.html) at Elecrow
