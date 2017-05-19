#include "header.h"

void wifiConnect(const char ssid[],const char pass[], std::function<void ()> onNotConnected)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    // while unable to connect
    while (WiFi.status() != WL_CONNECTED) 
    {
        onNotConnected();
    }
}
