# ESPHome Firmware Configurations

This directory contains ESPHome firmware configurations for all ESP32 Audio Dock devices. Each device has multiple configuration variants optimized for different use cases.

## Table of Contents

- [ESPHome Firmware Configurations](#esphome-firmware-configurations)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Hardware Variants](#hardware-variants)
    - [1. HiFi-ESP32](#1-hifi-esp32)
    - [2. Loud-ESP32](#2-loud-esp32)
    - [3. Louder-ESP32](#3-louder-esp32)
    - [4. Amped-ESP32](#4-amped-esp32)
    - [5. HiFi-ESP32-Plus](#5-hifi-esp32-plus)
    - [7. Louder-ESP32-Plus](#7-louder-esp32-plus)
    - [8. Amped-ESP32-Plus](#8-amped-esp32-plus)
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
    - [Feature Packages](#feature-packages)
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

Most boards are available in both **ESP32** and **ESP32-S3** variants within the same directory, the S3 variants carry `-s3-` in their filename. Plus-series boards (`5-`, `7-`, `8-`) are ESP32-S3 only unless noted otherwise.

Each hardware variant has 3-4 firmware options depending on your use case.

---

## Hardware Variants

### 1. HiFi-ESP32

**DAC**: PCM5100 (I2S)  
**MCU**: ESP32 / ESP32-S3  
**Target**: High-quality line-level audio output, 2.1V RMS  
**Features**: RGB LED, IR receiver

**Directory**: `1-hifi-esp32/`

**Configurations:**
- `hifi-esp32-idf.yaml` / `hifi-esp32-s3-idf.yaml` - Standard media player with mixer/resampler
- `hifi-esp32-idf-snapclient.yaml` / `hifi-esp32-s3-idf-snapclient.yaml` - Snapcast client with software DSP controls
- `hifi-esp32-idf-sendspin.yaml` / `hifi-esp32-s3-idf-sendspin.yaml` - Sendspin synchronized playback, very much experimental but working quite impressively well

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

**Note**: Experimental feature, firmware version 2026.2.0+ required

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

**Available on**: Louder-ESP32-Plus (`7-louder-esp32-plus/`), Amped-ESP32-Plus (`8-amped-esp32-plus/`)

**Requirements**: Home Assistant with voice assistant configured, ESPHome firmware 2026.1.4+

---

## Quick Start

1. **Choose your hardware variant** from the directories:
   - `1-hifi-esp32/` - PCM5100 line-level output
   - `2-loud-esp32/` - MAX98357A built-in amp
   - `3-louder-esp32/` - TAS5805M high-power with DSP
   - `4-amped-esp32/` - PCM5100 + TPA3110 amp
   - `5-hifi-esp32-plus/` - PCM5122 with DSP
   - `7-louder-esp32-plus/` - TAS5825M high-power with DSP (ESP32 / ESP32-S3)
   - `8-amped-esp32-plus/` - PCM5122 + amp + voice assist (ESP32 / ESP32-S3)

2. **Choose your MCU variant** (where applicable):
   - `*-esp32-*` - ESP32 variant
   - `*-esp32-s3-*` - ESP32-S3 variant

3. **Choose your configuration variant**:
   - Standard: `*-idf.yaml`
   - Snapclient: `*-snapclient.yaml`
   - Sendspin: `*-sendspin.yaml`
   - Voice Assistant: `*-voice-assist.yaml` (Plus boards only)

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
2. **DAC-specific packages**: `packages/dac-tas5805m.yaml`, `packages/dac-pcm5122.yaml`, `packages/dac-tas58xx.yaml`
3. **Feature addons**: `packages/media-player-addon-*.yaml`, `packages/sendspin-addon-*.yaml`
4. **Optional features**: `packages/ethernet-w5500.yaml`, `packages/oled.yaml`

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
- **`sendspin-audio.yaml`**: I2S audio stack for Sendspin — defines `i2s_speaker_id` for Sendspin
- **`sendspin.yaml`**: Sendspin multi-room player — defines `external_media_player` and `sendspin_group_media_player`
- **`snapclient.yaml`**: Snapcast client
- **`snapclient-with-dsp.yaml`**: Snapcast client with 18-band software EQ
- **`light.yaml`**: RGB LED support (WS2812)
- **`ir-receiver.yaml`**: Infrared remote control
- **`monitoring.yaml`**: Debug and system monitoring
- **`oled.yaml`**: SSD1306 OLED display

### DAC Packages

- **`dac-switch.yaml`**: Simple GPIO enable/disable switch for MAX98357A (Loud-ESP32)
- **`dac-pcm5122.yaml`**: PCM5122 DAC via I2C with volume, EQ and DSP controls (HiFi-ESP32-Plus, Amped-ESP32-Plus)
- **`dac-tas58xx.yaml`**: TAS5805M/TAS5825M DAC using the unified `tas58xx` driver — 15-band EQ, mixer, gain control (Louder-ESP32, Louder-ESP32-Plus)
- **`dac-tas58xx-biamp.yaml`**: TAS58xx in bi-amp mode with per-channel EQ
- **`dac-tas58xx-presets.yaml`**: TAS58xx with high/low frequency filter presets for subwoofer/satellite setups

### Audio Addon Packages

These addon packages extend the base audio stack to connect an external DAC component:

- **`audio-addon-external-dac.yaml`**: Extends `i2s_speaker_id` to add `audio_dac: external_dac` — needed for Louder-ESP32 and HiFi-ESP32-Plus
- **`sendspin-audio-addon-external-dac.yaml`**: Same as above but extends the Sendspin audio stack

### Media Player Addon Packages

These addon packages extend `external_media_player` with board-specific behavior:

- **`media-player-addon-dac-enable.yaml`**: Turns DAC GPIO on when playback starts, off when idle — used on Loud-ESP32, HiFi-ESP32-Plus
- **`media-player-addon-amp-unmute.yaml`**: Unmutes the TPA3110/TPA3128 amplifier on playback — used on Amped-ESP32
- **`media-player-addon-tas58xx.yaml`**: TAS58xx-specific playback hooks — plays startup sync sound on boot, enables DAC on play, overtemp monitoring

### Sendspin Addon Packages

These addon packages extend Sendspin player components with board-specific behavior:

- **`sendspin-addon-dac-enable.yaml`**: Turns DAC GPIO on/off with Sendspin playback state
- **`sendspin-addon-amp-unmute.yaml`**: Unmutes amplifier with Sendspin playback
- **`sendspin-addon-tas58xx.yaml`**: TAS58xx hooks for Sendspin — startup sync sound on boot, DAC enable on play
- **`sendspin-addon-oled.yaml`**: Scrolling track info on OLED display during Sendspin playback

### Feature Packages

- **`ethernet-w5500.yaml`**: W5500 SPI Ethernet module (replaces Wi-Fi config when used)
- **`amp-unmute.yaml`**: GPIO switch definition for TPA3110/TPA3128 amplifier mute control
- **`monitoring-wifi.yaml`**: Extended Wi-Fi diagnostics — signal strength, IP address, and connection state sensors

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

Uncomment this block and remove the local `!include` imports to use the latest published packages from the repository automatically.

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
