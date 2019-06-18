// ========================================================================
// File:    MqttController.cpp
// Date:    21-05-2019
// By:      Mark Meerlo & Arjan Kuiper
// ========================================================================

#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "Header/MqttController.h"
#include "Header/DipswitchReader.h"
#include "Header/RelayController.h"
#include "Header/OTAController.h"

//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
MqttController::MqttController () :
m_client(new WiFiClientSecure()),
m_mqtt(nullptr)
{
    // *** Create ClientID ************************
    char PCB_ID[10];
    int received = DipswitchReader::fetchPCBID();
    snprintf(PCB_ID, sizeof(PCB_ID), "MCB-%d", received);
    m_PCB_ID = PCB_ID;

    Serial.print("PCB Identifier: ");
    Serial.println(m_PCB_ID);

    // *** Initialize MQTT Client *****************
    Serial.println("Setting CA Cert: ");
    Serial.println(m_CA_CERT);
    m_client->setCACert(m_CA_CERT);

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

    // *** OTA Check 
    // Check if the given topic was meant as to update with OTA
    if (strcmp(commands[CommandSet::IDENTIFIER], "ota_update") == 0) 
    {
        OTAController::updateOTA(formattedPayload);
        return;
    }

    // *** Command check
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
        Serial.println("All relays were switched off!");
    }
}

//* ***********************************************
//          PRIVATE METHODS
//* ***********************************************
bool MqttController::connect ()
{
    // Check if WiFi is connected, if not connect to the specified SSID with the specified PASSWORD
    if (WiFi.status() != WL_CONNECTED) {
        // Turn the LED_BUILTIN off to show that connection was lost
        digitalWrite(LED_BUILTIN, LOW);

        Serial.println("Attempting WiFi connection...");

        int visibleNetworks = WiFi.scanNetworks();
        Serial.printf("Found a total of %d accespoints, trying to connect...\n", visibleNetworks);
        if(visibleNetworks > 0)
        {
            for(int i = 0; i < visibleNetworks; i++)
            {
                for(int j = 0; i < m_NET_SSID.size(); j++)
                {
                    Serial.printf("Comparing %s with %s\n", m_NET_SSID.at(j), WiFi.SSID(i).c_str());
                    if(strcmp(m_NET_SSID.at(j), WiFi.SSID(i).c_str()) == 0)
                    {
                        Serial.printf("Trying: %s with %s\n", m_NET_SSID.at(j), m_NET_PASS.at(j));
                        WiFi.begin(m_NET_SSID.at(j), m_NET_PASS.at(j));

                        // Wait for connection to be established
                        while (WiFi.status() != WL_CONNECTED) {
                            delay(1000);
                            Serial.print(".");
                        }

                        WiFi.onEvent(std::bind(&MqttController::wifiEvent, this, std::placeholders::_1));
                        Serial.println("\nConnected WiFi\n"); 
                        return true;
                    }
                }
            }
        }
        else
        {
            Serial.println("Could not find any WiFi accespoints!");
            return false;
        }
    }

    // Check if MQTT is connected, if not connect to the earlier specified MQTT Broker.
    if (m_mqtt->connected()) {  return true; }
    Serial.println("Attempting MQTT connection...");
    while(!m_mqtt->connected())
    {
        // Turn the LED_BUILTIN off to show that connection was lost
        digitalWrite(LED_BUILTIN, LOW);

        if (m_mqtt->connect(m_PCB_ID, m_MQTT_USER, m_MQTT_PASS)) {
            Serial.println("Connected MQTT");

            // Format the topic to subscribe to using the PCB ID
            char topicBuffer[30];
            snprintf(topicBuffer, sizeof(topicBuffer), "relaymodule/%s/#", m_PCB_ID);

            m_mqtt->subscribe(topicBuffer);
            m_mqtt->subscribe("relaymodule/ota_update");

            // Turn the LED_BUILTIN on to show that we are connected to the internet
            digitalWrite(LED_BUILTIN, HIGH);

            return true;
        } else {
            Serial.print("MQTT failed, rc=" + (String)m_mqtt->state() + " - Restarting system in 2 seconds\n");
            delay(2000);
            ESP.restart();
        }
    }

    return false;
}

void MqttController::wifiEvent(WiFiEvent_t event)
{
    switch (event) {
        case SYSTEM_EVENT_STA_DISCONNECTED:
            Serial.println("Disconnected from WiFi access point");
            m_mqtt->disconnect();
            break;
        default:
            // We don't intend on handling other enumeration values
            break;
    }
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

