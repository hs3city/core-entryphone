#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

const int ENTRYPHONE_PIN = 5;
const char* ssid = "hackerspace";
const char* password = "hackerspace";
WiFiServer server(80);

void setup()
{
    Serial.begin(9600);

    // Setting pins
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(ENTRYPHONE_PIN, OUTPUT);
    digitalWrite(ENTRYPHONE_PIN, HIGH);

    // Init wifi
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    // Blinks LED if unable to connect
    while (WiFi.status() != WL_CONNECTED) 
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(250);
        digitalWrite(LED_BUILTIN, LOW);
        delay(250);
    }

    // Init server
     server.begin();

    // Prints own ip
    Serial.println(WiFi.localIP());
}

void loop() 
{

    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)return;

    // Wait until the client sends some data
    while(!client.available())delay(1);

    // Open door if the request is not favicon
    if(client.readStringUntil('\r').indexOf("/favicon") == -1)
    {
        digitalWrite(ENTRYPHONE_PIN, LOW);
        delay(1000);
        digitalWrite(ENTRYPHONE_PIN, HIGH);
    }

    // Get ready for next request
    client.flush();

    // Return the response
    client.println("HTTP/1.1 200 OK");
    delay(1);
}
