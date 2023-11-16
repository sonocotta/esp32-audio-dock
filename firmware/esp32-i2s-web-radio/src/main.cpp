#include <Arduino.h>

#include "connect.hpp"
Connect connect;

#include "player.hpp"
Player player;

#include "playlist.hpp"
Playlist playlist;

uint32_t playlistEntryIndex = 0;

void bailOut(String status)
{
  log_e("%s. Reboot in 5 seconds", status);
  delay(5000);
  ESP.restart();
}

void setup()
{
  Serial.begin(SERIAL_BAUD);
  log_i("Starting up...");

#if defined(ARDUINO_USB_CDC_ON_BOOT) && (CORE_DEBUG_LEVEL >= ARDUHAL_LOG_LEVEL_DEBUG)
  delay(3000);
#endif

  if (!playlist.init())
  {
    bailOut("Failed to initialize playlist");
  }

  connect.init();
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

    switch (player.state)
    {
    case STATE_PLAY_INIT:
      player.audioInit();
      break;

    case STATE_PLAY_READY:
      player.play(playlist.entries[++playlistEntryIndex % playlist.entriesCount]);
      break;

    case STATE_PLAY:
      player.process();
      break;

    case STATE_PLAY_STOPPED:
      player.play(playlist.entries[++playlistEntryIndex % playlist.entriesCount]);
      break;
    }

    break;
  }
}
