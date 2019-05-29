// ========================================================================
// File:    main.cpp
// Date:    21-05-2019
// By:      Mark Meerlo
// ========================================================================

#include <Arduino.h>
#include "Header/Core.h"
#include "Header/DipswitchReader.h"
#include "Header/MqttController.h"

Core* core; 

/*
 *  The default setup method gets executed once, when the ESP32 boots
 */
void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println("Executing setup...");

  delay(100);
  core = new Core();
}

/*
 *  The default loop method gets called after the setup method and loops consecutively
 */
void loop() {
  core->loop();
}

//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
Core::Core () :
m_PCB_ID(DipswitchReader::fetchPCBID())
{
  Serial.println("Initialized Serial monitor!");
  m_mqtt = new MqttController(m_PCB_ID);
}

Core::~Core() { /* Not implemented */ }

//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
void Core::setup () { /* Not implemented */ }

void Core::loop ()
{
  // Loop the MQTT logic which handles internet connection and recieving of messages
  m_mqtt->loop();
}