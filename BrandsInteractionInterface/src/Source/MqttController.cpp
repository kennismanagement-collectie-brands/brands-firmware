#include "../Header/MqttController.h"
// ========================================================================
// File:    MqttController.cpp
// Date:    21-05-2019
// By:      Mark Meerlo
// ========================================================================
// *** Dependencies  ******************************
#include "Header/RelayController.h"

// External library for MQTT 
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <PubSubClient.h>



//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
MqttController::MqttController (int& PCB_ID) :
m_PCB_ID(PCB_ID),
m_client(new WiFiClientSecure()),
m_mqtt(nullptr),
m_relayCtrl(nullptr)
{
    m_mqtt      = new PubSubClient(getClient()); 

    // Configure secure client
    m_client->setCACert(m_NET_ROOT_CA);
    m_mqtt->setCallback([this] (char* topic, byte* payload, unsigned int length) { this->callback(topic, payload, length); });

}
MqttController::~MqttController () { /* No implementation */ }



//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
void MqttController::callback (char* topic, byte* payload, unsigned int length) 
{
    // *** Read incoming data *********************
    String formattedPayload;
    for (int i = 0; i < length; i++) {
        formattedPayload += (char)payload[i];
    }
    String t = topic;
    Serial.println((char*)"INCOMING\n === TOPIC === \n\t" + t + "\n === PAYLOAD === \n\t" + formattedPayload.c_str());

    // *** Act upon transmission ******************
    // TODO: Implement event handlers.
}


//* ***********************************************
//          PRIVATE METHODS
//* ***********************************************
bool MqttController::connect ()
{
    // Connect with WiFi

    // Connect with MQTT if not connected
    return false;
}

bool MqttController::publish (const char* topic, const char* payload)
{
    // Check if WiFi and MQTT are available
    if (!m_mqtt->connected())                       { return false; }

    return m_mqtt->publish(topic, payload);
}