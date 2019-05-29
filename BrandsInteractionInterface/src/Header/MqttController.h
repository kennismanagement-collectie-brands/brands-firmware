#ifndef MQTTCONTROLLER_H
#define MQTTCONRTOLLER_H

// *** Forward Declarations ***********************
class WiFiClient;
class PubSubClient;
class RelayController;

// *** Dependencies *******************************
#include <Arduino.h>

class MqttController {

public:
//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
MqttController                                  (int PCB_ID);
~MqttController                                 ();

//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
void callback                                   (char* topic, 
                                                 byte* payload, 
                                                 unsigned int length);
void loop                                       ();

private:
//* ***********************************************
//          PRIVATE METHODS
//* ***********************************************
bool connect                                    ();
bool publish                                    (const char* topic, 
                                                 const char* payload);
WiFiClient& getClient()                         { return *m_client; }

//* ***********************************************
//          PRIVATE ATTRIBUTES
//* ***********************************************
// Connection variables
const char*                             m_NET_SSID      = "SSID";
const char*                             m_NET_PASS      = "PASSWORD";
const char*                             m_NET_ROOT_CA;
const char*                             m_MQTT_SERVER   = "broker.hivemq.com";
const int                               m_MQTT_PORT     = 1883;
const char*                             m_MQTT_USER;
const char*                             m_MQTT_PASS;

// Variables to keep track of elapsed time without blocking the core
unsigned long                           m_startMillis = millis();
unsigned long                           m_currentMillis;
const unsigned long                     m_delay = 5000;

// Print identifier
int                                     m_PCB_ID;

// Objects
WiFiClient*                             m_client;
PubSubClient*                           m_mqtt;
RelayController*                        m_relayCtrl;

};
#endif