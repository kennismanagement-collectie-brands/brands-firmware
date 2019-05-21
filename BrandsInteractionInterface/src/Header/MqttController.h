#ifndef MQTTCONTROLLER_H
#define MQTTCONRTOLLER_H

// *** Forward Declarations ***********************
class PubSubClient;
class RelayController;



class MqttController {

public:
//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
MqttController                                  (int& PCB_ID);
~MqttController                                 ();


//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
void callback                                   (char* topic, 
                                                 char* payload, 
                                                 unsigned int length);

private:
//* ***********************************************
//          PRIVATE METHODS
//* ***********************************************
bool connect                                    ();
bool publish                                    (const char* topic, 
                                                 const char* payload);


//* ***********************************************
//          PRIVATE ATTRIBUTES
//* ***********************************************
// Connection variables
const char*                             m_NET_SSID;
const char*                             m_NET_PASS;
const char*                             m_MQTT_SERVER;
const char*                             m_MQTT_USER;
const char*                             m_MQTT_PASS;

// Print identifier
int&                                    m_PCB_ID;


// Objects
PubSubClient*                           m_mqtt;
RelayController*                        m_relayCtrl;


};
#endif