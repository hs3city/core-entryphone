#include "header.h"

void wifiConnect(const char ssid[],const char pass[], std::function<void ()> onNotConnected)
{
    wifiConnect(ssid, pass);

    // while unable to connect
    while (WiFi.status() != WL_CONNECTED) 
    {
        onNotConnected();
    }
}

void wifiConnect(const char ssid[],const char pass[])
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
}
