#include "../Header/MqttController.h"
// ========================================================================
// File:    MqttController.cpp
// Date:    21-05-2019
// By:      Mark Meerlo
// ========================================================================
// *** Dependencies  ******************************
#include "Header/RelayController.h"

// External library for MQTT
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
MqttController::MqttController (int PCB_ID) :
m_PCB_ID(PCB_ID),
m_client(new WiFiClient()),
m_mqtt(nullptr)
//m_relayCtrl(nullptr)
{
    m_mqtt = new PubSubClient(getClient()); 
    m_relayCtrl = new RelayController();

    // Configure secure client
    // m_client->setCACert(m_NET_ROOT_CA);
    m_mqtt->setServer(m_MQTT_SERVER, m_MQTT_PORT);
    m_mqtt->setCallback([this] (char* topic, byte* payload, unsigned int length) { this->callback(topic, payload, length); });

    this->connect();
}
MqttController::~MqttController () { /* No implementation */ }

void MqttController::loop()
{
    m_currentMillis = millis();
    if(m_currentMillis - m_startMillis >= m_delay)
    {
        this->connect();
        m_startMillis = m_currentMillis;
    }

    m_mqtt->loop();
}


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
    // *** WiFi Connecting ************************
    // Check if WiFi connection is available
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Attempting WiFi connection...");
        WiFi.begin(m_NET_SSID, m_NET_PASS);

        // Wait for connection to be established
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.print(".");
        }

        Serial.println("\nConnected WiFi\n");
    }


    // *** MQTT Connecting ************************
    // Check if connection is available
    if (m_mqtt->connected())                        {  return true; }
    Serial.println("Attempting MQTT connection...");
    while(!m_mqtt->connected())
    {
        // TODO: Implement PCB_ID here.
        if (m_mqtt->connect("collectieBrandsMuseum")) {
            Serial.println("Connected MQTT");
            m_mqtt->subscribe("somerandomtopictosubscribe");
            return true;
        } else {
            Serial.print("failed, rc=" + (String)m_mqtt->state() + " try again in 5 seconds");
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