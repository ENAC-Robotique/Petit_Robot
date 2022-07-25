#pragma once

#include "SPIFFS.h" //!! Keep it included !! workaround or else ESPwebsocket compilation throw an error and can't find FS.h
#include "ESPAsyncWebServer.h" 

//To use this file, implement movement_handler somewhere and use "init_comm()" on the setup(), and modify ssid, password, access_pt,... if needed
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
    extern const char* ssid;
    extern const char* password;
    //Generate access point
    extern const char* access_pt;
    extern const char* password_access_pt;

    void movement_handler(Movement mvt); //Fonction à affecter autre part //Return type different from void only to avoid errors
    // --- Setup -----------------
    void init_comm(); //USE IT ON THE MAIN to start network functionalities

    //wifi
    bool init_connect_wifi();
    void init_access_pt();

    //Async websocket Connection
    extern AsyncWebServer server;
    extern AsyncWebSocket ws;
    void initWebSocket();
    void onEvent(AsyncWebSocket       *server,  //
             AsyncWebSocketClient *client,  //
             AwsEventType          type,    // the signature of this function is defined
             void                 *arg,     // by the `AwsEventHandler` interface
             uint8_t              *data,    //
             size_t                len);
    void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);


}