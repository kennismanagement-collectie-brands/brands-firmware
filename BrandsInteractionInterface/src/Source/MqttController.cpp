// ========================================================================
// File:    MqttController.cpp
// Date:    21-05-2019
// By:      Mark Meerlo
// ========================================================================

#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "Header/MqttController.h"
#include "Header/RelayController.h"

//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
MqttController::MqttController (int PCB_ID) :
m_PCB_ID(PCB_ID),
m_client(new WiFiClient()),
m_mqtt(nullptr)
{
    m_mqtt = new PubSubClient(getClient()); 
    m_relayCtrl = new RelayController();

    // Configure the MQTT server and set the callback to the "callback" member function of MqttController
    m_mqtt->setServer(m_MQTT_SERVER, m_MQTT_PORT);
    m_mqtt->setCallback([this] (char* topic, byte* payload, unsigned int length) { this->callback(topic, payload, length); });

    this->connect();
}

MqttController::~MqttController () { /* No implementation */ }

/*
 *  Loop method that consecutively executes MQTT and WiFi logic such as (re)connecting to the Internet / MQTT Broker
 *  and calling the internal loop method of the PubSubClient which handles the recieving of the actual messages. 
 */
void MqttController::loop()
{
    m_currentMillis = millis();
    if(m_currentMillis - m_startMillis >= m_delay)
    {
        this->connect();
        m_startMillis = m_currentMillis;
    }

    m_mqtt->loop();
    m_relayCtrl->loop();
}

//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
/*
 *  The callback method handles the recieving of MQTT messages. The message topic, payload and length are made available
 *  to use and interpret in the firmware. The callback also controls the RelayController by translating the recieved MQTT
 *  commands into function calls for the RelayController.
 */ 
void MqttController::callback (char* topic, byte* payload, unsigned int length) 
{
    // Read and parse incoming MQTT messages
    payload[length] = 0;
    const char* formattedPayload = reinterpret_cast<const char*>(payload);
    Serial.println((char*)"INCOMING\n === TOPIC === \n\t" + (String)topic + "\n === PAYLOAD === \n\t" + formattedPayload);

    // Split the topic up into different parts to read the command set
    std::vector<const char*> commands;
    char* tokens = strtok(topic, "/");
    while(tokens != NULL)
    {
        commands.push_back(tokens);
        tokens = strtok(NULL, "/");
    }

    // Compare the command to the available command in the command set
    if(strcmp(commands[CommandSet::COMMAND], "on") == 0)
    {
        m_relayCtrl->setRelay(atoi(formattedPayload), HIGH);
        Serial.printf("Relay %d was switched on!\n", atoi(formattedPayload));
    }
    else if(strcmp(commands[CommandSet::COMMAND], "off") == 0)
    {
        m_relayCtrl->setRelay(atoi(formattedPayload), LOW);
        Serial.printf("Relay %d was switched off!\n", atoi(formattedPayload));
    }
    else if(strcmp(commands[CommandSet::COMMAND], "allon") == 0)
    {
        for(byte i = 0; i < 4; i++) { m_relayCtrl->setRelay(i, HIGH); }
        Serial.println("All relays were switched on!");
    }
    else if(strcmp(commands[CommandSet::COMMAND], "alloff") == 0)
    {
        for(byte i = 0; i < 4; i++) { m_relayCtrl->setRelay(i, LOW); }
        Serial.println("All relays were switched on!");
    }
}

//* ***********************************************
//          PRIVATE METHODS
//* ***********************************************
bool MqttController::connect ()
{
    // Check if WiFi is connected, if not connect to the specified SSID with the specified PASSWORD
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

    // Check if MQTT is connected, if not connect to the earlier specified MQTT Broker.
    if (m_mqtt->connected()) {  return true; }
    Serial.println("Attempting MQTT connection...");
    while(!m_mqtt->connected())
    {
        // TODO: Implement PCB_ID here.
        if (m_mqtt->connect("collectieBrandsMuseum")) {
            Serial.println("Connected MQTT");
            m_mqtt->subscribe("relaymodule/1101/#");
            return true;
        } else {
            // Wait 5 seconds before retrying
            Serial.print("failed, rc=" + (String)m_mqtt->state() + " try again in 5 seconds");
            delay(5000);
        }
    }

    return false;
}

/*
 *  The publish method publishes a specified message on the specified topic
 */ 
bool MqttController::publish (const char* topic, const char* payload)
{
    // Check if WiFi and MQTT are available
    if (!m_mqtt->connected()) { return false; }
    return m_mqtt->publish(topic, payload);
}