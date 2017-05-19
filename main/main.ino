#include "header.h"

//=================
// Configuration
// ================

const int ENTRYPHONE_PIN = 5;
const int SERVER_PORT = 80;

// WIFI credentials -- to be removed
const char* ssid = "hackerspace";
const char* password = "hackerspace";

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
    Server.handleRequest([]()
    {
        Door.open();
    });
}
