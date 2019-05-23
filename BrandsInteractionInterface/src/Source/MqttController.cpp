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
MqttController::MqttController (int PCB_ID) :
m_PCB_ID(PCB_ID),
m_client(new WiFiClientSecure()),
m_mqtt(nullptr),
m_relayCtrl(nullptr)
{
    m_mqtt = new PubSubClient(getClient()); 

    // Configure secure client
    // m_client->setCACert(m_NET_ROOT_CA);
    m_mqtt->setCallback([this] (char* topic, byte* payload, unsigned int length) { this->callback(topic, payload, length); });

    this->connect();
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
    WiFi.begin(m_NET_SSID, m_NET_PASS);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected");

    // Connect with MQTT if connected to WiFi
    //WiFiClientSecure espClient;
    //PubSubClient client(espClient);
    m_mqtt->setServer(m_MQTT_SERVER, m_MQTT_PORT);
    Serial.println("Connecting to MQTT..");
    while(!m_mqtt->connected())
    {
        if(m_mqtt->connect("espClient"))
        {
            Serial.println("Connected to MQTT!");
            return true;
        }else{
            Serial.print("failed, rc=");
            Serial.print(m_mqtt->state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }

    return false;
}

bool MqttController::publish (const char* topic, const char* payload)
{
    // Check if WiFi and MQTT are available
    if (!m_mqtt->connected())                       { return false; }

    return m_mqtt->publish(topic, payload);
}