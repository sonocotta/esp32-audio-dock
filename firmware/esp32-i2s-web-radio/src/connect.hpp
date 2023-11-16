#pragma once

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif
#ifdef ESP32
#include <WiFi.h>
#endif

#include <WiFiManager.h>

enum ConnectState
{
    STATE_WIFI_INIT = 0,
    STATE_WIFI_CONFIG_PORTAL = 1,
    STATE_WIFI_FAILED = 2,
    STATE_WIFI_CONNECTED = 3,
};

class Connect
{
private:
    WiFiManager *wm = new WiFiManager();

    // void configPortalCallback(WiFiManager *wm);
    // void saveConfigCallback();
    void setState(ConnectState _state)
    {
        log_d("State changed to %d", _state);
        state = _state;
    }

public:
    ConnectState state = STATE_WIFI_INIT;

    void init();
    void process() {
        wm->process();
    }
};

void Connect::init()
{
#ifdef ARDUINO_LOLIN_C3_MINI
    // https://github.com/tzapu/WiFiManager/issues/1422
    log_d("Set WIFI_POWER_8_5dBm");
    WiFi.setTxPower(WIFI_POWER_8_5dBm); 
#endif
    
    // For DEBUG purposes only, resets known network
    // wm->resetSettings();

    wm->setConnectTimeout(10);
    wm->setConfigPortalBlocking(false);
#if defined(WIFI_SSID) && defined(WIFI_PASS)
    wm->preloadWiFi(WIFI_SSID, WIFI_PASS);
#endif
    wm->setAPCallback([&](WiFiManager *)
    {
        log_i("Config portal started on %s AP", wm->getWiFiHostname().c_str());
        setState(STATE_WIFI_CONFIG_PORTAL); 
    });

    wm->setSaveConfigCallback([&]()
    {
        log_i("Config portal stopped");
        setState(WiFi.isConnected() ? STATE_WIFI_CONNECTED : STATE_WIFI_FAILED);
    });

    if (wm->autoConnect())
    {
        log_i("Connected with: %s", WiFi.SSID());
        log_i("Private IP Address: %s", WiFi.localIP().toString());
        setState(STATE_WIFI_CONNECTED);
    }
}

// void Connect::configPortalCallback(WiFiManager *wm)
// {
// }

// void Connect::saveConfigCallback()
// {
// }
