#include "header.h"

void server::handleRequest(unsigned int timeout, std::function<void ()> onReqest)
{
    // Check if a client has connected
    WiFiClient Client = _server->available();
    // Try again if not
    if (!Client) return;

    int requestTime = 0;

    // Wait for data
    while(!Client.available())
    {
        delay(1);
        requestTime++;
        if(requestTime > timeout)
        {
            Client.flush();
            return;
        }
    }

    // If the request is not a favicon, handle it
    if(!(Client.readStringUntil('\r').indexOf("/favicon") != -1))
    {
        onReqest();
    }

    // Respond 200, OK
    Client.println("HTTP/1.1 200 OK");

    // Get ready for next request
    Client.flush();
}

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
