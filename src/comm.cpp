//This file manage 
// 1.the wifi communication for remote control by providing a websocket access
// 2. Trigger callback when receiving it from websocket connection
//----------------------------------------------------------------
#include "comm.h"
#include <Arduino.h>
#include <WiFi.h>
#include <string.h>

//Source : https://m1cr0lab-esp32.github.io/remote-control-with-websocket/wifi-setup/

namespace comm {
// --- Setup -----------------
// First, it tries to connect twice during 3 seconds to the existing SSID from settings
// Then, if it doesn't find it, it creates an access point
void init_comm() {
    if(!init_connect_wifi()) { //Connect twice and if not successful
        init_access_pt();
    }
    //Generate access point
}

bool init_connect_wifi() { 
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.printf("Trying to connect [%s] ", WiFi.macAddress().c_str());
    int tried = 0;
    while (WiFi.status() != WL_CONNECTED && tried <= 4) {
        Serial.print(".");
        delay(250);
        tried++;
    }
    if (WiFi.status() != WL_CONNECTED) { 
        return false;
    }
    Serial.printf(" %s\n", WiFi.localIP().toString().c_str());
    return true;
}

void init_access_pt() { 

}

void initWebSocket() {
    ws.onEvent(onEvent);
    server.addHandler(&ws);
    
}

void onEvent(AsyncWebSocket       *server,  //
             AsyncWebSocketClient *client,  //
             AwsEventType          type,    // the signature of this function is defined
             void                 *arg,     // by the `AwsEventHandler` interface
             uint8_t              *data,    //
             size_t                len) {   //

        switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
            break;
        case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;
        case WS_EVT_DATA:
            handleWebSocketMessage(arg, data, len);
        case WS_EVT_PONG:
        case WS_EVT_ERROR:
            break;
        }
    }

    void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
        if (strcmp((char*)data, "forward"))
        {
            movement_handler(Movement::FORWARD);
            
        }
        if (strcmp((char*)data, "stop"))
        {
            movement_handler(Movement::STOP);
        }
        movement_handler(Movement::UNKNOWN);
    }
}