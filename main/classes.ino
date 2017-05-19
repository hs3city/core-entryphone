#include "classes.h"

#pragma region indicator

    indicator::indicator(int pin)
    {
        PIN = pin;
        pinMode(PIN, OUTPUT); // Does this need to be in void setup() ????
        digitalWrite(PIN, LOW);
    }
    void indicator::blink()
    {
        digitalWrite(PIN, HIGH);
        delay(250);
        digitalWrite(PIN, LOW);
        delay(250);
    }

#pragma endregion

#pragma region door

    door::door(int pin)
    {
        PIN = pin;
        pinMode(PIN, OUTPUT); // Does this need to be in void setup() ????
        close(); // Set entryphone to off by default
    }
    void door::open()
    {
        digitalWrite(PIN, LOW);
        delay(1000);
        close();
    }
    void door::close()
    {
        digitalWrite(PIN, HIGH);
    }

#pragma endregion

#pragma region wifi

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

#pragma endregion

#pragma region server

    server::server(unsigned short int port)
    {
        _server = new WiFiServer(static_cast<uint16_t>(port));
    }

    server::~server()
    {
        delete _server;
    }

    void server::init()
    {
        _server->begin();
    }

    void server::handleRequest(std::function<void ()> onReqest)
    {
        // Check if a client has connected
        WiFiClient Client = _server->available();
        if (!Client) return;

        // Wait until the client sends some data
        while(!Client.available())
        {
            delay(1);
        }

        // If the request is not a favicon, handle it
        if(!(Client.readStringUntil('\r').indexOf("/favicon") != -1))
        {
            onReqest();
        }

        // Respond 200, OK
        Client.println("HTTP/1.1 200 OK");

        // Get ready for next request
        delay(1);
        Client.flush();
    }

#pragma endregion