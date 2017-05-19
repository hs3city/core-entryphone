#include "classes.h"

//=================
// Configuration
// ================

// Pins
const int ENTRYPHONE_PIN = 5;

const int PORT = 80;

// WIFI credentials -- to be removed
const char* ssid = "hackerspace";
const char* password = "hackerspace";

//=================
// Main
// ================

indicator Indicator(LED_BUILTIN);
server Server(PORT);

void setup()
{
    Serial.begin(9600); //is this mandatory???

    wifiConnect(ssid, password, []()
    {
        Indicator.blink();
    });

    Server.init();

    // Prints own ip
    Serial.println(WiFi.localIP());
}

door Door(ENTRYPHONE_PIN);

void loop() 
{
    Server.handleRequest([]()
    {
        Door.open();
    });
}
