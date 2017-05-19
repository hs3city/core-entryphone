#pragma once

// External WiFi libs
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

#include <functional>

//=================
// Pin operators
// ================

class pinOperator
{
protected:
    int PIN;
    pinOperator(int pin)
    {
        PIN = pin;
        pinMode(PIN, OUTPUT);
    }
};

class indicator: pinOperator
{
public:
    indicator(int);
    void blink();
private:
    void on();
    void off();
};

class door: pinOperator
{
public:
    door(int);
    void open();
private:
    void close();
};

//=================
// Network
// ================

void wifiConnect(const char[],const char[], std::function<void ()>);
void wifiConnect(const char ssid[],const char pass[]);

class server
{
public:
    server(unsigned short int);
    ~server();
    void handleRequest(std::function<void ()>);
    void init();
private:
    WiFiServer* _server;
};
