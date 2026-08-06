# ESPHome Firmware Configurations

This directory contains ESPHome firmware configurations for all ESP32 Audio Dock devices. Each device has multiple configuration variants optimized for different use cases.

## Table of Contents

- [ESPHome Firmware Configurations](#esphome-firmware-configurations)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Hardware Variants](#hardware-variants)
    - [0. Legacy Boards](#0-legacy-boards)
    - [1. HiFi-ESP32](#1-hifi-esp32)
    - [2. Loud-ESP32](#2-loud-esp32)
    - [3. Louder-ESP32](#3-louder-esp32)
    - [4. Amped-ESP32](#4-amped-esp32)
    - [5. HiFi-ESP32-Plus](#5-hifi-esp32-plus)
    - [6. Loud-ESP32-Plus](#6-loud-esp32-plus)
    - [7. Louder-ESP32-Plus](#7-louder-esp32-plus)
    - [8. Amped-ESP32-Plus](#8-amped-esp32-plus)
    - [9. Louder-ESP32-Mini](#9-louder-esp32-mini)
    - [10. Louder-ESP32-Pro](#10-louder-esp32-pro)
  - [Configuration Variants](#configuration-variants)
    - [Standard Media Player](#standard-media-player)
    - [Snapclient](#snapclient)
    - [Sendspin](#sendspin)
    - [Voice Assistant](#voice-assistant)
  - [Quick Start](#quick-start)
  - [Building and Flashing](#building-and-flashing)
    - [Using VS Code Tasks (Fast, as long as you have good hardware)](#using-vs-code-tasks-fast-as-long-as-you-have-good-hardware)
    - [Using Docker CLI](#using-docker-cli)
    - [Initial Flash via Serial](#initial-flash-via-serial)
    - [GitHub Actions CI/CD](#github-actions-cicd)
    - [Building ESPHome on Windows with WSL (Alternative Method)](#building-esphome-on-windows-with-wsl-alternative-method)
      - [Step 1 — Install and Configure WSL 2](#step-1--install-and-configure-wsl-2)
      - [Step 2 — Install Dependencies](#step-2--install-dependencies)
      - [Step 3 — Build](#step-3--build)
      - [Step 4 — Flash the Firmware from Windows](#step-4--flash-the-firmware-from-windows)
  - [Configuration](#configuration)
    - [Customizing Device Name](#customizing-device-name)
    - [Customizing Pinout](#customizing-pinout)
    - [Advanced Configuration](#advanced-configuration)
  - [Secrets Management](#secrets-management)
    - [Setup Secrets File](#setup-secrets-file)
  - [Package System](#package-system)
    - [Core Packages](#core-packages)
    - [DAC Packages](#dac-packages)
    - [Audio Addon Packages](#audio-addon-packages)
    - [Media Player Addon Packages](#media-player-addon-packages)
    - [Sendspin Addon Packages](#sendspin-addon-packages)
    - [Snapclient Addon Packages](#snapclient-addon-packages)
    - [Feature Packages](#feature-packages)
    - [Voice Assistant Packages](#voice-assistant-packages)
    - [Using Packages](#using-packages)
    - [Remote Package Import](#remote-package-import)
  - [Additional Resources](#additional-resources)
  - [Contributing](#contributing)
  - [License](#license)

---

## Overview

All configurations use:
- **ESP-IDF framework** for better audio performance and stability. I used to provide Arduino-based examples as well, but they proved to be a poor user experience.
- **Modular package system** for code reusability (see `packages/` directory)
- **Shared secrets** for Wi-Fi credentials and API keys
- **Common features**: Wi-Fi, OTA updates, API, debug logging, RGB LED, IR receiver

Most boards are available in both **ESP32** and **ESP32-S3** variants within the same directory, the S3 variants carry `-s3-` in their filename. Plus-series boards (`5-`, `6-`, `7-`, `8-`) are available in both ESP32 and ESP32-S3 unless noted otherwise. Mini (`9-`) and Pro (`10-`) boards are ESP32-S3 only.

Each hardware variant has 3-4 firmware options depending on your use case.

---

## Hardware Variants

### 0. Legacy Boards

**DAC**: PCM5100 (I2S) or external I2S DAC  
**MCU**: ESP32 / ESP32-S2 / ESP32-S3  
**Target**: Simple reference/example implementations using Arduino framework  
**Features**: Basic I2S media player, no modular packages

**Directory**: `0-legacy-boards/`

**Configurations:**
- `esp32-duo-media-player.yaml` — Dual-core ESP32 with I2S
- `esp32-s2-solo-media-player.yaml` — ESP32-S2 single-core with I2S
- `esp32-s3-solo-media-player.yaml` — ESP32-S3 with I2S

> **Note**: These are early reference implementations using the Arduino framework. They are not recommended for new builds — use the IDF-based configurations for better performance.

---

### 1. HiFi-ESP32

**DAC**: PCM5100 (I2S)  
**MCU**: ESP32 / ESP32-S3  
**Target**: High-quality line-level audio output, 2.1V RMS  
**Features**: RGB LED, IR receiver, optional OLED display, optional Ethernet (W5500)

**Directory**: `1-hifi-esp32/`

**Configurations:**
- `hifi-esp32-idf.yaml` / `hifi-esp32-s3-idf.yaml` - Standard media player with mixer/resampler
- `hifi-esp32-idf-snapclient.yaml` / `hifi-esp32-s3-idf-snapclient.yaml` - Snapcast client with software DSP controls
- `hifi-esp32-idf-sendspin.yaml` / `hifi-esp32-s3-idf-sendspin.yaml` - Sendspin synchronized playback, very much experimental but working quite impressively well
- `hifi-esp32-s3-idf-voice-assist.yaml` - Voice assistant with wake word detection (S3 only)
- `hifi-esp32-s3-idf-voice-assist-sendspin.yaml` - Voice assistant with Sendspin synchronized playback (S3 only)

**Packages used**: `audio.yaml`, `media-player.yaml`, `light.yaml`, `ir-receiver.yaml`, `monitoring.yaml`, `oled.yaml`  
**Optional**: `ethernet-w5500.yaml`

<img width="923" height="1224" alt="image" src="https://github.com/user-attachments/assets/add2bcec-46a6-4068-b173-084b964fcf83" />

---

### 2. Loud-ESP32

**DAC**: Dual MAX98357A (I2S)  
**MCU**: ESP32 / ESP32-S3  
**Target**: Built-in stereo amplifier for direct speaker connection (small speakers ~5W)  
**Features**: RGB LED, IR receiver, DAC enable control

**Directory**: `2-loud-esp32/`

**Configurations:**
- `loud-esp32-idf.yaml` / `loud-esp32-s3-idf.yaml` - Standard media player with mixer/resampler
- `loud-esp32-idf-snapclient.yaml` / `loud-esp32-s3-idf-snapclient.yaml` - Snapcast client with software DSP controls
- `loud-esp32-idf-sendspin.yaml` / `loud-esp32-s3-idf-sendspin.yaml` - Sendspin synchronized playback, very much experimental but working quite impressively well

**Packages used**: `audio.yaml`, `media-player.yaml`, `dac-switch.yaml`, `media-player-addon-dac-enable.yaml`, `light.yaml`, `ir-receiver.yaml`, `monitoring.yaml`, `oled.yaml`  
**Optional**: `ethernet-w5500.yaml`

<img width="923" height="1224" alt="image" src="https://github.com/user-attachments/assets/a6aea826-c532-450e-8944-e5b7e8b16f27" />

---

### 3. Louder-ESP32

**DAC**: TAS5805M (I2C + I2S) with built-in DSP  
**MCU**: ESP32 / ESP32-S3  
**Target**: High-power output with advanced audio processing  
**Features**: RGB LED, IR receiver, optional OLED display, optional Ethernet (W5500)

**Directory**: `3-louder-esp32/`

**Configurations:**
- `louder-esp32-idf.yaml` / `louder-esp32-s3-idf.yaml` - Standard media player with TAS5805M DSP
- `louder-esp32-idf-snapclient.yaml` / `louder-esp32-s3-idf-snapclient.yaml` - Snapcast client with DSP controls, software DSP makes less sense since hardware DSP is much more efficient here
- `louder-esp32-idf-sendspin.yaml` / `louder-esp32-s3-idf-sendspin.yaml` - Sendspin synchronized playback, very much experimental but working quite impressively well, especially in combination with built-in DSP

**Packages used**: `dac-tas58xx.yaml`, `audio.yaml`, `audio-addon-external-dac.yaml`, `media-player.yaml`, `media-player-addon-dac-enable.yaml`, `media-player-addon-tas58xx.yaml`, `light.yaml`, `ir-receiver.yaml`, `monitoring.yaml`, `oled.yaml`  
**Optional**: `ethernet-w5500.yaml`

<img width="923" height="1224" alt="image" src="https://github.com/user-attachments/assets/36084c57-3cf2-4ce3-bc2d-26e8d5b52b04" />

---

### 4. Amped-ESP32

**DAC**: PCM5100 (I2S) + TPA3110 amplifier  
**MCU**: ESP32 / ESP32-S3  
**Target**: High-quality audio with built-in amplification  
**Features**: RGB LED, IR receiver, optional OLED display, optional Ethernet (W5500)

**Directory**: `4-amped-esp32/`

**Configurations:**
- `amped-esp32-idf.yaml` / `amped-esp32-s3-idf.yaml` - Standard media player with amplifier
- `amped-esp32-idf-snapclient.yaml` / `amped-esp32-s3-idf-snapclient.yaml` - Snapcast client with software DSP controls
- `amped-esp32-idf-sendspin.yaml` / `amped-esp32-s3-idf-sendspin.yaml` - Sendspin synchronized playback

**Packages used**: `audio.yaml`, `media-player.yaml`, `amp-unmute.yaml`, `media-player-addon-amp-unmute.yaml`, `light.yaml`, `ir-receiver.yaml`, `monitoring.yaml`, `oled.yaml`  
**Optional**: `ethernet-w5500.yaml`

<img width="923" height="1224" alt="image" src="https://github.com/user-attachments/assets/2b68df50-4e4d-4217-b161-adc9de40eb6e" />

---

### 5. HiFi-ESP32-Plus

**DAC**: PCM5122 (I2C + I2S) with entry-level DSP  
**MCU**: ESP32 / ESP32-S3  
**Target**: High-quality audio with software-configurable volume, tone and DSP controls  
**Features**: RGB LED, IR receiver, optional OLED display, optional Ethernet (W5500)

**Directory**: `5-hifi-esp32-plus/`

**Configurations:**
- `hifi-esp32-plus-idf.yaml` / `hifi-esp32-s3-plus-idf.yaml` - Standard media player
- `hifi-esp32-plus-idf-snapclient.yaml` / `hifi-esp32-s3-plus-idf-snapclient.yaml` - Snapcast client with software DSP controls
- `hifi-esp32-plus-idf-sendspin.yaml` / `hifi-esp32-s3-plus-idf-sendspin.yaml` - Sendspin synchronized playback

**Packages used**: `dac-pcm5122.yaml`, `audio.yaml`, `audio-addon-external-dac.yaml`, `media-player.yaml`, `media-player-addon-dac-enable.yaml`, `light.yaml`, `ir-receiver.yaml`, `monitoring.yaml`, `oled.yaml`  
**Optional**: `ethernet-w5500.yaml`

---

### 6. Loud-ESP32-Plus

**DAC**: Infineon MA12070P (I2C + I2S) with built-in DSP  
**MCU**: ESP32 / ESP32-S3  
**Target**: High-efficiency Class-D amplification with entry-level DSP  
**Features**: RGB LED, IR receiver, optional OLED display, optional Ethernet (W5500), I2C volume/mute control

**Directory**: `6-loud-esp32-plus/`

**Configurations:**
- `loud-esp32-plus-idf.yaml` / `loud-esp32-s3-plus-idf.yaml` - Standard media player with MA12070P DSP
- `loud-esp32-plus-idf-sendspin.yaml` / `loud-esp32-s3-plus-idf-sendspin.yaml` - Sendspin synchronized playback
- `loud-esp32-s3-plus-idf-snapclient.yaml` - Snapcast client (S3 only, 32-bit I2S required)

The MA12070P is a high-efficiency Class-D audio amplifier with I2C digital volume control and built-in DSP. It provides software-configurable volume, mute, and enable control via I2C.

> **Note**: The snapclient configuration requires 32-bit I2S data, which is required for this DAC. At this moment snapclient doen't allow this.

**Packages used**: `dac-ma12070p.yaml`, `audio.yaml`, `media-player.yaml`, `media-player-addon-dac-mute.yaml`, `light.yaml`, `ir-receiver.yaml`, `monitoring.yaml`, `monitoring-wifi.yaml`  
**Optional**: `ethernet-w5500.yaml`, `oled.yaml`

---

### 7. Louder-ESP32-Plus

**DAC**: TAS5825M (I2C + I2S) with built-in DSP  
**MCU**: ESP32 / ESP32-S3  
**Target**: High-power output with advanced audio processing and voice assistant support  
**Features**: RGB LED, IR receiver, OLED display, optional Ethernet (W5500), microphone (voice assistant)

**Directory**: `7-louder-esp32-plus/`

**Configurations:**
- `louder-esp32-plus-idf.yaml` / `louder-esp32-s3-plus-idf.yaml` - Standard media player with TAS5825M DSP
- `louder-esp32-plus-idf-snapclient.yaml` / `louder-esp32-s3-plus-idf-snapclient.yaml` - Snapcast client
- `louder-esp32-plus-idf-sendspin.yaml` / `louder-esp32-s3-plus-idf-sendspin.yaml` - Sendspin synchronized playback with OLED display
- `louder-esp32-s3-plus-idf-voice-assist.yaml` - Voice assistant with wake word detection (S3 only)

The TAS5825M DSP allows 3 distinct EQ modes:

- 15-band EQ in ganged mode (both channels share DSP settings)

<img width="374" height="944" alt="image" src="https://github.com/user-attachments/assets/6ef6dd41-05f2-467b-b027-c4c89d00696e" />

- 15-band EQ with individual controls per channel, allows fine-tuning speakers in an asymmetrical setup

<img width="443" height="1132" alt="image" src="https://github.com/user-attachments/assets/f056cda6-a997-4b1d-a702-898c930a6932" />

- High/Low frequency profiles for bi-amp config, allows filtering out subwoofer and satellite channels with a specific frequency in the 60–150 Hz range in 10 Hz steps

<img width="504" height="1039" alt="image" src="https://github.com/user-attachments/assets/ae53213c-0a28-4ed2-bed6-9dbcd960a8c6" />

The DSP also allows adjusting the gain per channel, which is essentially a balance control for speakers with different sensitivity and impedance.

> **Important**: Play sound on boot is required for the TAS5825M DAC to capture the clock signal and enable DSP configuration. Any DSP configs sent before the clock signal is established (EQ, Mixer controls) are silently ignored.

---

### 8. Amped-ESP32-Plus

**DAC**: PCM5122 (I2C + I2S) with entry-level DSP + amplifier  
**MCU**: ESP32 / ESP32-S3  
**Target**: High-quality DSP-controlled audio with built-in amplification and voice assistant support  
**Features**: RGB LED, IR receiver, optional OLED display, optional Ethernet (W5500), microphone (voice assistant)

**Directory**: `8-amped-esp32-plus/`

**Configurations:**
- `amped-esp32-plus-idf.yaml` / `amped-esp32-s3-plus-idf.yaml` - Standard media player
- `amped-esp32-plus-idf-snapclient.yaml` / `amped-esp32-s3-plus-idf-snapclient.yaml` - Snapcast client
- `amped-esp32-plus-idf-sendspin.yaml` / `amped-esp32-s3-plus-idf-sendspin.yaml` - Sendspin synchronized playback
- `amped-esp32-s3-plus-idf-voice-assist.yaml` - Voice assistant with wake word detection (S3 only)

---

### 9. Louder-ESP32-Mini

**DAC**: TAS5805M (I2C + I2S) with built-in DSP  
**MCU**: ESP32-S3  
**Target**: Compact high-power audio in PBTL mono configuration  
**Features**: No RGB LED or IR receiver (minimal footprint design), USB-PD support on some variants

**Directory**: `9-louder-esp32-mini/`

**Configurations:**
- `louder-esp32-s3-mini.yaml` - Standard media player with TAS5805M DSP (no LED)
- `louder-esp32-s3-mini-snapclient.yaml` - Snapcast client (no LED)
- `louder-esp32-s3-mini-sendspin-mono.yaml` - Sendspin synchronized mono playback (no LED)
- `louder-esp32-s3-mini-m-sendspin-mono.yaml` - Sendspin mono with USB-PD detection (external component: husb238, work in progress!)

The Mini boards are designed for compact installations where a full-sized board won't fit. They feature TAS5805M DAC in PBTL (mono) configuration for maximum power from a compact form factor. Mixer mode (MONO/LEFT/RIGHT) can be selected per-config.

---

### 10. Louder-ESP32-Pro

**DAC**: TAS5825M (I2C + I2S) with built-in DSP  
**MCU**: ESP32-S3  
**Target**: High-power audio with TFT display, fan cooling, and voice assistant support  
**Features**: RGB LED, IR receiver, TFT SPI display (ST7789/ILI9341), active fan control, optional Ethernet (W5500), microphone (voice assistant)

**Directory**: `10-louder-esp32-pro/`

**Configurations:**
- `louder-esp32-s3-pro-idf.yaml` - Standard media player with TAS5825M DSP, TFT display, fan control
- `louder-esp32-s3-pro-idf-sendspin.yaml` - Sendspin synchronized playback with TFT display
- `louder-esp32-s3-pro-idf-snapclient.yaml` - Snapcast client with OLED display
- `louder-esp32-s3-pro-idf-voice-assist.yaml` - Voice assistant with wake word detection

The Pro board is a feature-rich platform with:
- **TFT SPI display** (ST7789 or ILI9341) for track info, album art, and clock
- **Active fan control** for thermal management during extended high-power operation
- **I2S microphone** for voice assistant capabilities
- **TAS5825M DAC** with full 15-band EQ, bi-amp mode, and presets

---

## Configuration Variants

### Standard Media Player

**Files**: `*-idf.yaml`

Full-featured ESPHome media player with:

- Native Home Assistant integration
- Media player controls (play/pause/volume)
- Mixer and resampler for announcements
- Text-to-speech (TTS) support, with ducking (lowers background music during announcements)
- IR remote control
- RGB LED status indicator

**Best for**: General Home Assistant integration, TTS announcements, standard audio playback

<img width="854" height="1168" alt="image" src="https://github.com/user-attachments/assets/047d8522-06d5-46bc-834f-3104928591a5" />

---

### Snapclient

**Files**: `*-snapclient.yaml`

Snapcast client implementation with enhanced features:
- Synchronized multi-room audio playback
- 18-band equalizer (software DSP controls, works on every board)
  - Frequencies: 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 200, 315, 500, 800, 1250, 2000, 5000 Hz
  - Range: -15dB to +15dB per band
- Perfect audio synchronization across multiple devices
- Low latency streaming
- Two snapclient implementations available:
  - **Basic** (`snapclient-new.yaml`): @c-MM original port, no DSP controls
  - **With DSP** (`snapclient-with-dsp.yaml`): @farmed-switch fork with software BQ-filters

**Best for**: Multi-room synchronized audio with a central Snapcast server

**Requirements**: Snapcast server (can run in Home Assistant add-on)

**Drawbacks**: Very much experimental at the moment
- do not support hardware mute
- do not support voice announcements
- limitations when using together with TAS58xx DSP (may not apply EQ if it starts without audio)
- do not support displaying audio title
- do not allow control volume from the snapclient node

<img width="872" height="1160" alt="image" src="https://github.com/user-attachments/assets/6117be69-e20f-41f3-be36-fae996044c8e" />

---

### Sendspin

**Files**: `*-sendspin.yaml`

Sendspin synchronized audio playback:

- Multi-room synchronized playback
- ESPHome native implementation
- Simplified setup compared to Snapcast
- Direct integration with Home Assistant
- Very much experimental (in beta currently)
- Allows pulling title, artist, and controlling playback

**Best for**: Multi-room audio without external server infrastructure

**Note**: Experimental feature, firmware version 2026.5.0+ required for latest sendspin features

<img width="846" height="1198" alt="image" src="https://github.com/user-attachments/assets/54a9b535-8296-4267-bf6b-4abd00b070f8" />

---

### Voice Assistant

**Files**: `*-voice-assist.yaml`

Full-featured voice assistant with wake word detection:

- Local wake word detection ("okay Nabu" by default)
- Microphone input via I2S (on supported boards)
- Speaker output with announcement ducking
- Native Home Assistant Voice integration
- Visual feedback via RGB LED phases (idle / listening / thinking / replying / error / muted)
- Also available with Sendspin synchronized playback (`*-voice-assist-sendspin.yaml`)

**Available on**:
- HiFi-ESP32 S3 (`1-hifi-esp32/`) — S3 only
- Louder-ESP32-Plus (`7-louder-esp32-plus/`) — S3 only
- Amped-ESP32-Plus (`8-amped-esp32-plus/`) — S3 only
- Louder-ESP32-Pro (`10-louder-esp32-pro/`) — S3 only

**Requirements**: Home Assistant with voice assistant configured, ESPHome firmware 2026.1.4+, esparagus-echo microphone packages (included via remote import)

---

## Quick Start

1. **Choose your hardware variant** from the directories:
   - `0-legacy-boards/` — Legacy Arduino-based examples (not recommended for new builds)
   - `1-hifi-esp32/` — PCM5100 line-level output
   - `2-loud-esp32/` — MAX98357A built-in amp
   - `3-louder-esp32/` — TAS5805M high-power with DSP
   - `4-amped-esp32/` — PCM5100 + TPA3110 amp
   - `5-hifi-esp32-plus/` — PCM5122 with DSP
   - `6-loud-esp32-plus/` — MA12070P high-efficiency Class-D
   - `7-louder-esp32-plus/` — TAS5825M high-power with DSP (ESP32 / ESP32-S3)
   - `8-amped-esp32-plus/` — PCM5122 + amp + voice assist (ESP32 / ESP32-S3)
   - `9-louder-esp32-mini/` — TAS5805M compact PBTL mono (ESP32-S3)
   - `10-louder-esp32-pro/` — TAS5825M with TFT display and fan (ESP32-S3)

2. **Choose your MCU variant** (where applicable):
   - `*-esp32-*` — ESP32 variant
   - `*-esp32-s3-*` — ESP32-S3 variant

3. **Choose your configuration variant**:
   - Standard: `*-idf.yaml`
   - Snapclient: `*-snapclient.yaml`
   - Sendspin: `*-sendspin.yaml`
   - Voice Assistant: `*-voice-assist.yaml` (selected boards, S3 only)
   - Voice Assistant + Sendspin: `*-voice-assist-sendspin.yaml` (HiFi-ESP32 S3 only)

4. **Configure secrets** (see [Secrets Management](#secrets-management))

5. **Build and flash** (see [Building and Flashing](#building-and-flashing))

---

## Building and Flashing

### Using VS Code Tasks (Fast, as long as you have good hardware)

The project includes VS Code tasks for building with Docker:

1. Open any configuration YAML file
2. Run task: `Tasks > Run Build Task > ESPHome: Build Current File (Stable)`
3. For OTA updates: `ESPHome: Build and Upload OTA (Stable)`

### Using Docker CLI

```bash
# Build
docker run --rm \
  -v "$(pwd)/1-hifi-esp32:/config" \
  -v "$(pwd)/packages:/config/packages" \
  -v "$(pwd)/secrets/secrets.yaml:/config/secrets.yaml" \
  -v "$(pwd)/.esphome-cache:/cache" \
  -e PLATFORMIO_BUILD_CACHE_DIR=/cache/.pio-cache \
  -it esphome/esphome:latest \
  compile /config/hifi-esp32-idf.yaml

# Upload via OTA
docker run --rm \
  --network=host \
  -v "$(pwd)/1-hifi-esp32:/config" \
  -v "$(pwd)/packages:/config/packages" \
  -v "$(pwd)/secrets/secrets.yaml:/config/secrets.yaml" \
  -v "$(pwd)/.esphome-cache:/cache" \
  -it esphome/esphome:latest \
  run /config/hifi-esp32-idf.yaml --device OTA
```

### Initial Flash via Serial

For first-time setup, flash via USB:

```bash
docker run --rm \
  --device=/dev/ttyUSB0 \
  -v "$(pwd)/1-hifi-esp32:/config" \
  -v "$(pwd)/packages:/config/packages" \
  -v "$(pwd)/secrets/secrets.yaml:/config/secrets.yaml" \
  -it esphome/esphome:latest \
  run /config/hifi-esp32-idf.yaml --device /dev/ttyUSB0
```

### GitHub Actions CI/CD

The project includes automated build pipeline (`.github/workflows/build-esphome.yml`) that:
- Automatically discovers all configuration files
- Builds all variants in parallel on pull requests
- Uses caching for faster builds

### Building ESPHome on Windows with WSL (Alternative Method)

> Contributed by [@harrison110](https://github.com/harrison110) in [#123](https://github.com/sonocotta/esp32-audio-dock/issues/123#issuecomment-4255961275)

Building via Docker on Windows without a properly configured WSL can result in **very** long build times (7000+ seconds). Using WSL 2 brings this down to ~3 minutes.

#### Step 1 — Install and Configure WSL 2

1. Install WSL with Ubuntu (or your preferred distro) from **PowerShell**:
   ```powershell
   wsl --install -d Ubuntu
   ```
   Make sure you have at least the minimum recommended version — Docker currently recommends **WSL 2.1.5** or newer. Older versions will cause issues with the build.

2. Create the WSL config file to set resource limits. Without this, WSL may not have enough resources, which will drastically increase build times.

   Create the file `C:\Users\YOUR_USER_NAME\.wslconfig` with the following contents (adjust values to your system):
   ```ini
   [wsl2]
   memory=8GB
   processors=6
   swap=4GB
   localhostForwarding=true
   ```

#### Step 2 — Install Dependencies

Inside WSL, install Python and any other required dependencies. Also install **Docker Desktop** on Windows (it integrates with WSL 2 automatically).

#### Step 3 — Build

Clone the repository inside WSL and follow the standard build instructions. Running the Docker build from within WSL keeps all files on the Linux filesystem, which is the key to fast build times.

#### Step 4 — Flash the Firmware from Windows

Flashing is easier to do from Windows rather than from WSL to avoid USB/hardware access issues.

1. Install `esptool` on Windows:
   ```powershell
   pip install esptool
   ```

2. Flash using the following command (adjust `--chip`, `--port`, and the path to your binary as needed):
   ```powershell
   python -m esptool --chip esp32s3 --port COM7 --baud 460800 write-flash 0x0 "FIRMWARE.FACTORY.BIN_LOCATION"
   ```

3. If the compiled `.bin` file is still on the WSL filesystem, get its Windows path with:
   ```bash
   wslpath -w "$(find ./3-louder-esp32 -name firmware.factory.bin | head -n 1)"
   ```
   Change the folder name to match your target device.

4. To find the correct COM port in PowerShell:
   ```powershell
   Get-CimInstance Win32_SerialPort | Select-Object DeviceID,Name,Description
   ```

---

## Configuration

### Customizing Device Name

Each configuration file has substitutions at the top:

```yaml
substitutions:
  name: esphome-web-dc95a8  # Change this to your device name
  friendly_name: HiFi-ESP32  # Change this to friendly name
```

### Customizing Pinout

All GPIO pins are defined in the `substitutions:` section. Modify these if you have your own hardware:

```yaml
substitutions:
  i2s_lrclk_pin: GPIO25
  i2s_bclk_pin: GPIO26
  i2s_dout_pin: GPIO22
  # ... more pins
```

### Advanced Configuration

Most functionality is imported from packages. To customize:

1. **Base audio packages**: `packages/audio.yaml`, `packages/sendspin-audio.yaml`
2. **DAC-specific packages**: `packages/dac-tas58xx.yaml`, `packages/dac-pcm5122.yaml`, `packages/dac-ma12070p.yaml`, `packages/dac-tas58xx-biamp.yaml`, `packages/dac-tas58xx-presets.yaml`
3. **Feature addons**: `packages/media-player-addon-*.yaml`, `packages/sendspin-addon-*.yaml`, `packages/snapclient-addon-*.yaml`
4. **Optional features**: `packages/ethernet-w5500.yaml`, `packages/oled.yaml`, `packages/tft-spi.yaml`, `packages/fan.yaml`

Feel free to experiment with IR/RGB/Rotary/OLED configuration. Only the most basic configuration is provided to get you started. Don't hesitate to extend it.

---

## Secrets Management

### Setup Secrets File

1. Copy the example: `cp secrets/secrets.yaml.example secrets/secrets.yaml`
2. Edit `secrets/secrets.yaml` with your credentials:

```yaml
# Wi-Fi credentials
esphome_wifi_ssid: "YourWiFiSSID"
esphome_wifi_password: "YourWiFiPassword"
esphome_ap_password: "YourAPPassword"
esphome_ota_password: "YourOTAPassword"
esphome_api_key: "YourAPIKey"

# Alternative naming (also supported)
wifi_ssid: "YourWiFiSSID"
wifi_password: "YourWiFiPassword"
```
---

## Package System

The package system promotes code reusability across different hardware variants. Packages use the `id: !extend` addon pattern, meaning they extend base components without duplicating configuration. This allows mixing and matching features cleanly.

### Core Packages

- **`audio.yaml`**: Base I2S audio configuration — defines `i2s_speaker_id`, mixer, resampler
- **`media-player.yaml`**: Media player with announcement ducking — defines `external_media_player`
- **`media-player-no-light.yaml`**: Media player without RGB LED control — for boards without LEDs (e.g., Louder-ESP32-Mini)
- **`sendspin.yaml`**: Sendspin multi-room player — defines `sendspin_group_media_player`, `external_media_player`, and audio sources
- **`sendspin-no-light.yaml`**: Sendspin without RGB LED control — for boards without LEDs
- **`snapclient-new.yaml`**: Snapcast client (@c-MM original port, basic implementation)
- **`snapclient-with-dsp.yaml`**: Snapcast client with 18-band software EQ (@farmed-switch fork)
- **`light.yaml`**: RGB LED support (WS2812)
- **`ir-receiver.yaml`**: Infrared remote control
- **`monitoring.yaml`**: Debug and system monitoring
- **`monitoring-wifi.yaml`**: Extended Wi-Fi diagnostics — signal strength, IP address, and connection state sensors
- **`oled.yaml`**: SSD1306 OLED display
- **`tft-spi.yaml`**: TFT SPI display (ST7789/ILI9341) — used on Pro boards
- **`fan.yaml`**: Active fan control with temperature sensor — used on Pro boards

### DAC Packages

- **`dac-switch.yaml`**: Simple GPIO enable/disable switch for MAX98357A (Loud-ESP32)
- **`dac-pcm5122.yaml`**: PCM5122 DAC via I2C with volume, EQ and DSP controls (HiFi-ESP32-Plus, Amped-ESP32-Plus)
- **`dac-ma12070p.yaml`**: Infineon MA12070P Class-D amplifier with I2C control — digital volume, mute, enable (Loud-ESP32-Plus)
- **`dac-tas58xx.yaml`**: TAS5805M/TAS5825M DAC using the unified `tas58xx` driver — 15-band EQ, mixer, gain control (Louder-ESP32, Louder-ESP32-Plus, Louder-ESP32-Mini, Louder-ESP32-Pro)
- **`dac-tas58xx-biamp.yaml`**: TAS58xx in bi-amp mode with per-channel EQ
- **`dac-tas58xx-presets.yaml`**: TAS58xx with high/low frequency filter presets for subwoofer/satellite setups

### Audio Addon Packages

These addon packages extend the base audio stack to connect an external DAC component:

- **`audio-addon-external-dac.yaml`**: Extends `i2s_speaker_id` to add `audio_dac: external_dac` — needed for Louder-ESP32, HiFi-ESP32-Plus, and other boards with I2C-controlled DACs
- **`sendspin-audio-addon-external-dac.yaml`**: Same as above but extends the Sendspin audio stack
- **`sendspin-audio-addon-ma12070p.yaml`**: Extends Sendspin audio stack specifically for MA12070P DAC

### Media Player Addon Packages

These addon packages extend `external_media_player` with board-specific behavior:

- **`media-player-addon-dac-enable.yaml`**: Turns DAC GPIO on when playback starts, off when idle — used on Loud-ESP32, HiFi-ESP32-Plus, Louder-ESP32, Louder-ESP32-Mini
- **`media-player-addon-dac-enable-dual.yaml`**: Same as above but for dual DAC configurations
- **`media-player-addon-dac-mute.yaml`**: Controls DAC mute via I2C (MA12070P) or GPIO on play/idle — used on Loud-ESP32-Plus
- **`media-player-addon-amp-unmute.yaml`**: Unmutes the TPA3110/TPA3128 amplifier on playback — used on Amped-ESP32
- **`media-player-addon-tas58xx.yaml`**: TAS58xx-specific playback hooks — plays startup sync sound on boot, enables DAC on play, overtemp monitoring
- **`media-player-addon-tas58xx-dual.yaml`**: Same as above for dual TAS58xx configurations

### Sendspin Addon Packages

These addon packages extend Sendspin player components with board-specific behavior:

- **`sendspin-addon-dac-enable.yaml`**: Turns DAC GPIO on/off with Sendspin playback state
- **`sendspin-addon-dac-mute.yaml`**: Controls DAC mute via I2C (MA12070P) with Sendspin playback
- **`sendspin-addon-amp-unmute.yaml`**: Unmutes amplifier with Sendspin playback
- **`sendspin-addon-tas58xx.yaml`**: TAS58xx hooks for Sendspin — startup sync sound on boot, DAC enable on play
- **`sendspin-addon-esp32.yaml`**: ESP32 (non-S3) specific wifi/audio optimizations for Sendspin
- **`sendspin-addon-oled.yaml`**: Scrolling track info on OLED display during Sendspin playback
- **`sendspin-addon-tft.yaml`**: Track info and display management on TFT SPI display during Sendspin playback (Pro boards)
- **`sendspin-addon-voice-assist-tas58xx.yaml`**: TAS58xx hooks for voice assistant + Sendspin combined configs

### Snapclient Addon Packages

These addon packages extend snapclient with board-specific behavior:

- **`snapclient-addon-dac-enable.yaml`**: Enables DAC GPIO on snapclient play
- **`snapclient-addon-dac-mute.yaml`**: Controls DAC mute via I2C (MA12070P) with snapclient playback
- **`snapclient-addon-external-dac.yaml`**: Extends snapclient to use external I2C DAC
- **`snapclient-addon-tas58xx.yaml`**: TAS58xx EQ control and startup sync for snapclient
- **`snapclient-addon-amp-enable.yaml`**: Enables amplifier with snapclient playback

### Feature Packages

- **`amp-unmute.yaml`**: GPIO switch definition for TPA3110/TPA3128 amplifier mute control
- **`ethernet-w5500.yaml`**: W5500 SPI Ethernet module (replaces Wi-Fi config when used)

### Voice Assistant Packages

Voice assistant packages are sourced from the external [esparagus-echo](https://github.com/sonocotta/esparagus-echo) repository and imported via remote packages:

- **`microphone-i2s.yaml`**: I2S microphone configuration
- **`microphone.yaml`**: Microphone sensor entity
- **`voice-assist.yaml`**: Full voice assistant with wake word detection
- **`voice-assist-sendspin.yaml`**: Voice assistant combined with Sendspin synchronized playback
- **`media-player-addon-voice-assist.yaml`**: Media player hooks for voice assistant integration

### Using Packages

Packages are imported in each config file's `packages:` block:

```yaml
packages:
  audio: !include packages/audio.yaml
  media_player: !include packages/media-player.yaml
  light: !include packages/light.yaml
  ir_receiver: !include packages/ir-receiver.yaml
  monitoring: !include packages/monitoring.yaml
  oled: !include packages/oled.yaml
```

This keeps device-specific configs clean and maintainable.

### Remote Package Import

All config files include a commented-out remote import block that allows pulling packages directly from GitHub without a local clone:

```yaml
packages:
  esparagus_remote:
    url: https://github.com/sonocotta/esp32-audio-dock
    ref: main
    files:
      - firmware/esphome/packages/audio.yaml
      - firmware/esphome/packages/media-player.yaml
      - firmware/esphome/packages/light.yaml
      - firmware/esphome/packages/ir-receiver.yaml
      - firmware/esphome/packages/monitoring.yaml
      - firmware/esphome/packages/oled.yaml
```

Uncomment this block and remove the local `!include` imports to use the latest published packages from the repository automatically. Many configs already use the remote import method by default.

---

## Additional Resources

- **Main Project**: [ESP32 Audio Dock Repository](../../README.md)
- **ESPHome Documentation**: https://esphome.io
- **Home Assistant**: https://www.home-assistant.io
- **Snapcast**: https://github.com/badaix/snapcast
- **Discord Community**: Join our [Discord](https://discord.gg/PtnaAaQMpS) for support

---

## Contributing

ESPHome is very dynamic ecosystem at the moment, when it comes to Sendspin, things are changing literally every day. Found an issue - let me know, create PR, create issue. Help others to figure it out.

---

## License

See [LICENSE](../../LICENSE) in the root directory.