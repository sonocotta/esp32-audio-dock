# ESP32 Audio Dock Test Firmware

This folder contains the test firmware for the ESP32 Audio Dock, a project designed to provide high-quality audio playback using the ESP32 microcontroller and the TAS5805M digital audio amplifier.

I use this code to test different aspects of the boards, mostly TAS5805M DAC capabilities.

There are few different ways this can be used
- [esp32-i2s-bare](/esp32-i2s-bare/) implementation, used bare naked I2S driver to sent samples to the DAC. I implemented a simple tone generator for testing purposes
- [esp32-i2s-esp8266audio](/esp32-i2s-esp8266audio/) implements basic playback controls for a few WAV files stored at the device. These are timple tone and channel test files, that I use for board testing
- [esp32-i2s-web-radio](/esp32-i2s-web-radio/), similar to the `esp32-i2s-esp8266audio` this example implements basic playback controls to play an audio stream from the web
- [esphome](/esphome/) - ESPHome yaml config files that can be used with board with minimal changes
- [squeezelite-esp32](/squeezelite-esp32/) - sdkconfig file for building `squeezelite-esp32` project for ESP32-S3

## Software Requirements

- [PlatformIO](https://platformio.org/) installed in your development environment.
- ESP-IDF or Arduino framework (configured via PlatformIO).

## Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/esp32-audio-dock.git
cd esp32-audio-dock/firmware/esp32-i2s-bare
```

### 2. Install Dependencies

PlatformIO will automatically install the required dependencies listed in platformio.ini when you build the project.

### 3. Configure the Build

Edit the platformio.ini file to select the appropriate environment for your board. For example:

```ini
[env:louder-esp32]
board = wemos_d1_mini32
build_flags =
    -D CONFIG_DAC_TAS5805M
    -D PIN_I2C_SDA=21
    -D PIN_I2C_SCL=27
    -D PIN_I2S_FS=25
    -D PIN_I2S_SCK=26
    -D PIN_I2S_SD=22
```

### 4. Build and Upload

To build and upload the firmware to your ESP32 board, run:

```bash
pio run --target upload
```

### 5. Monitor Serial Output

To monitor the serial output, run:

```bash
pio device monitor
```

## Usage

### Command Line Interface (CLI)

Below details are mostly applies to first 3 folders for clear reasons.

All of them built as a command line tool that allows controlling the board functions with the terminal inputs. Below is a quick summary, while more information available by typing `help` in the ESP32 console

- `play`, `pause`, `resume`, `stop`, `prev`, `next` are the playback controls
- `list` will display the items in the playlist
- `loop` will toggle looping through the current track
- `help` command will display a handy help

Specific to the `esp32-i2s-bare` code
- `tone` command will play a square wave tone, with given frequency in Hz and amplitude in bits [0..16], `16` would mean rail-to-rail.

Specific to TAS5805M DAC (more details at my [library](https://github.com/sonocotta/esp32-tas5805m-dac) repo)
- `amp` will set an amp mode: play, mute, highz, sleep etc
- `volume` and `vol` are digital volume controls in 8bit and percent values accordingly
- `gain` controls DAC analog gain
- `dacmode` swtches between 2-channel and bridge mode
- `eq` reads and write equilizer states for given band in the range of -15..15Db
- `mod` controls the modulation and switching frequency
- `mixer` switches between MONO, STEREO, LEFT, RIGHT modes
- `fault` allows for reading DAC self seported errors and clearing them

![image](https://github.com/user-attachments/assets/83bab272-22bd-4fff-a174-ef4a81678c3e)

### Example CLI Commands

```bash
amp play          # Set amplifier to play mode
amp highz         # Set amplifier to high-impedance mode
amp sleep         # Put amplifier into sleep mode
amp deepsleep     # Put amplifier into deep sleep mode
```

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests to improve the project.

## License

This project is licensed under the Apache License v2.0 License. See the LICENSE file for details.
