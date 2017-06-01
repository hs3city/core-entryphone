#include "header.h"

//=================
// Configuration
// ================

const int ENTRYPHONE_PIN = 5;
const int SERVER_PORT = 80;
const int REQUEST_TIEMOUT = 1000;

// WIFI credentials -- to be removed
const char* ssid = "hackerspace";
const char* password = "hackerspace";

// IP consts -- to be removed
// Sets static IP for the device
const IPAddress ip(192, 168, 0, 10);
const IPAddress gateway(192, 168, 0, 1);
const IPAddress subnet(255, 255, 255, 0);

//=================
// Main
// ================

indicator Indicator(LED_BUILTIN);
server Server(SERVER_PORT);
door Door(ENTRYPHONE_PIN);

void setup()
{
    wifiConnect(ssid, password, []()
    {
        Indicator.blink();
    });

    Server.init();

    // Prints own ip
    Serial.begin(9600);
    Serial.println(WiFi.localIP());
}

void loop() 
{
    Server.handleRequest(REQUEST_TIEMOUT ,[]()
    {
        Door.open();
    });
}
