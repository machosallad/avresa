#ifndef APPLICATION_H
#define APPLICATION_H

#include "trafikverket_client.h"
#include "content_manager.h"
#include "web_server.h"
#include "wifi_manager.h"
#include "announcements.h"

class Application
{
public:
    Application();
    ~Application();
    void init();
    void run();

private:
    unsigned long lastRequestTime = 0;           // When the last request was made
    const unsigned long requestInterval = 10000; // Request interval (10 seconds)
};

#endif // APPLICATION_H