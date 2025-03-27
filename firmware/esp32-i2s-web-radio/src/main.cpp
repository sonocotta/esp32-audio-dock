#include <Arduino.h>

#include "connect.hpp"
Connect connect;

#include "player.hpp"
Player player;

#include "playlist.hpp"
Playlist playlist;

#include <commandline.hpp>
CommandLine cmd;

#ifdef CONFIG_DAC_TAS5805M
#include <Wire.h>
#include <tas5805m.hpp>
tas5805m Tas5805m(&Wire);
#endif

const char *TAG = "MAIN";

void bailOut(String status)
{
  log_e("%s. Reboot in 5 seconds", status);
  delay(5000);
  ESP.restart();
}

void init_cmd_line()
{
  cmd.init();

  cmd.addCommand("play", "Play the current track", [](int argc, char **argv)
                 { return player.play(); });

  cmd.addCommand("pause", "Pause the current track", [](int argc, char **argv)
                 { return player.pause(); });

  cmd.addCommand("resume", "Resume the current track", [](int argc, char **argv)
                 { return player.resume(); });

  cmd.addCommand("stop", "Stop the current track", [](int argc, char **argv)
                 { return player.stop(); });

  cmd.addCommand("next", "Play the next track", [](int argc, char **argv)
                 { return player.next(); });

  cmd.addCommand("prev", "Play the previous track", [](int argc, char **argv)
                 { return player.prev(); });

  cmd.addCommand("list", "List all tracks", [](int argc, char **argv)
                 { return playlist.list(); });

  cmd.addCommand("loop", "Loop the current track", [](int argc, char **argv)
                 { return player.toggleLoop(); });

  cmd.startLoopAsync();
}

void setup()
{
  Serial.begin(SERIAL_BAUD);
  Serial.setDebugOutput(true);
  log_i("Starting up...");

#if defined(ARDUINO_USB_CDC_ON_BOOT) && (CORE_DEBUG_LEVEL >= ARDUHAL_LOG_LEVEL_DEBUG)
  delay(3000);
#endif

esp_log_level_set("*", ESP_LOG_DEBUG);

ESP_ERROR_CHECK(playlist.init());

// This should start I2S clock
ESP_ERROR_CHECK(player.init());

#ifdef CONFIG_DAC_TAS5805M
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  // This will send default DSP init sequence
  Tas5805m.init();

  // alternative way is to run 'fault on' command
  // ticker.attach_ms(10000, ticker_callback);

  // I2S must be initialized by this time for DSP settings to apply
  uint8_t newVolume = 78; // (-15 Db default volume)
  ESP_LOGI(TAG, "Setting VOLUME value to: %d", newVolume);
  ESP_ERROR_CHECK(Tas5805m.setVolume(newVolume));

  ESP_LOGI(TAG, "Setting GAIN value to: -15.5Db");
  ESP_ERROR_CHECK(Tas5805m.setAnalogGain(TAS5805M_MIN_GAIN));
#endif

  connect.init();
  init_cmd_line();
}

void loop()
{
  switch (connect.state)
  {
  case STATE_WIFI_INIT:
    break;

  case STATE_WIFI_CONFIG_PORTAL:
    connect.process();
    break;

  case STATE_WIFI_FAILED:
    bailOut("Failed to connect");
    break;

  case STATE_WIFI_CONNECTED:
    player.loop();
    break;

  }
}
