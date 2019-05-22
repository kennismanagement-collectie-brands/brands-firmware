#include "../Header/MqttController.h"
// ========================================================================
// File:    MqttController.cpp
// Date:    21-05-2019
// By:      Mark Meerlo
// ========================================================================
// *** Dependencies  ******************************
#include "Header/RelayController.h"

// External library for MQTT 
#include <PubSubClient.h>



//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
MqttController::MqttController (int& PCB_ID) :
m_PCB_ID(PCB_ID),
m_mqtt(nullptr),
m_relayCtrl(nullptr)
{ /* No implementation */ }
MqttController::~MqttController () { /* No implementation */ }



//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
void MqttController::callback (char* topic, char* payload, unsigned int length) 
{

}


//* ***********************************************
//          PRIVATE METHODS
//* ***********************************************
bool MqttController::connect ()
{
    return false;
}

bool MqttController::publish (const char* topic, const char* payload)
{
    return false;
}