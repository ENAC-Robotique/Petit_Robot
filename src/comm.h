#pragma once

#include "SPIFFS.h" //!! Keep it included !! workaround or else ESPwebsocket compilation throw an error and can't find FS.h
#include "ESPAsyncWebServer.h" 

#define HTTP_PORT 80
namespace comm { 
    enum Movement {
        FORWARD = 0, 
        BACKWARD = 1, 
        LEFT = 2, 
        RIGHT = 3, 
        STOP = 4, 
        UNKNOWN = 5,
    };

    // ----- Settings ---------------------
    //Existing SSID
    const char* ssid = "robot";
    const char* password = "robotcities";
    //Generate access point
    const char* access_pt = "potit_robot";
    const char* password_access_pt = "ageofbots";

    void (*movement_handler)(Movement); //A affecter autre part
    // --- Setup -----------------
    //wifi
    void init_comm();
    bool init_connect_wifi();
    void init_access_pt();

    //Async websocket Connection
    AsyncWebServer server(HTTP_PORT);
    AsyncWebSocket ws("/ws");
    void initWebSocket();
    void onEvent(AsyncWebSocket       *server,  //
             AsyncWebSocketClient *client,  //
             AwsEventType          type,    // the signature of this function is defined
             void                 *arg,     // by the `AwsEventHandler` interface
             uint8_t              *data,    //
             size_t                len);
    void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);


}