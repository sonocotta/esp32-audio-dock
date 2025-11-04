#include <Arduino.h>

#define filesystem LittleFS

#ifdef CONFIG_DAC_TAS5805M
#include <Wire.h>
#include <tas5805m.hpp>
#include <Ticker.h>
tas5805m Tas5805m(&Wire);
Ticker ticker;
#endif

#ifdef CONFIG_DAC_PCM5122
#include <Wire.h>
#include "PCM51xx.h"
PCM51xx Pcm5122(Wire);
#endif

const char *TAG = "MAIN";

#include "player.hpp"
Player player;

#include "playlist.hpp"
Playlist playlist;

#include <commandline.hpp>
CommandLine cmd;

#ifdef CONFIG_DAC_TAS5805M
void ticker_callback()
{
  TAS5805M_FS_FREQ freq;
  uint8_t ratio;
  Tas5805m.getFsFreq(&freq);
  Tas5805m.getBckRatio(&ratio);

  TAS5805M_CTRL_STATE state;
  Tas5805m.getPowerState(&state);

  bool is_r_muted, is_l_muted;
  Tas5805m.getAutomuteState(&is_r_muted, &is_l_muted);

  ESP_LOGI(TAG, "FS Frequency: %s, BCK ratio: %d; Power state: %s; Automute: R: %d, L: %d",
           tas5805m_map_fs_freq(freq), ratio,
           tas5805m_map_amp_state(state),
           is_r_muted, is_l_muted);

  TAS5805M_FAULT fault;
  Tas5805m.getFaultState(&fault);
  Tas5805m.decodeFaults(fault);

  if (fault.err0 || fault.err1 || fault.err2 || fault.ot_warn)
  {
    ESP_LOGI(TAG, "Clearing fault states");
    Tas5805m.clearFaultState();
  }
}
#endif

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
  WiFi.mode(WIFI_OFF);

  Serial.begin(SERIAL_BAUD);
  Serial.println(F("Starting up...\n"));

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
  uint8_t newVolume = 78; //(-15 Db default volume)
  ESP_LOGI(TAG, "Setting VOLUME value to: %d", newVolume);
  ESP_ERROR_CHECK(Tas5805m.setVolume(newVolume));

  ESP_LOGI(TAG, "Setting GAIN value to: -15.5Db");
  ESP_ERROR_CHECK(Tas5805m.setAnalogGain(TAS5805M_MIN_GAIN));
#endif

#ifdef CONFIG_DAC_PCM5122
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  // This will send default DSP init sequence
  Pcm5122.begin(PCM51xx::SAMPLE_RATE_44_1K, PCM51xx::BITS_PER_SAMPLE_16);
  // begin() returns false currently, but DAC is working. Why?
  #ifdef PIN_PCM5122_MUTE
  pinMode(PIN_PCM5122_MUTE, OUTPUT);
  digitalWrite(PIN_PCM5122_MUTE, HIGH); // unmute
  #endif
#endif

  ESP_ERROR_CHECK(player.play());
  init_cmd_line();
}

void loop()
{
  player.loop();
}