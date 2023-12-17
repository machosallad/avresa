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
};

#endif // APPLICATION_H