#pragma once

// External WiFi libs
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

#include <functional>

class indicator
{
private:
    int PIN;
public:
    indicator(int);
    void blink();
};

class door
{
private:
    int PIN;
public:
    door(int);
    void open();
    void close();
};

void wifiConnect(const char[],const char[], std::function<void ()>);

class server
{
private:
    WiFiServer* _server;
public:
    server(unsigned short int);
    ~server();
    void handleRequest(std::function<void ()>);
    void init();
};
