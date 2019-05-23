#ifndef MQTTCONTROLLER_H
#define MQTTCONRTOLLER_H

// *** Forward Declarations ***********************
class WiFiClientSecure;
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

private:
//* ***********************************************
//          PRIVATE METHODS
//* ***********************************************
bool connect                                    ();
bool publish                                    (const char* topic, 
                                                 const char* payload);
// Getter
WiFiClientSecure& getClient()                   { return *m_client; }


//* ***********************************************
//          PRIVATE ATTRIBUTES
//* ***********************************************
// Connection variables
const char*                             m_NET_SSID;
const char*                             m_NET_PASS;
const char*                             m_NET_ROOT_CA;
const char*                             m_MQTT_SERVER;
const char*                             m_MQTT_USER;
const char*                             m_MQTT_PASS;

// Print identifier
int                                     m_PCB_ID;


// Objects
WiFiClientSecure*                       m_client;
PubSubClient*                           m_mqtt;
RelayController*                        m_relayCtrl;


};
#endif