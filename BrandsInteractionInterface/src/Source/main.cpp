#include <Arduino.h>
#include "Header/Core.h"
// ========================================================================
// File:    main.cpp
// Date:    21-05-2019
// By:      Mark Meerlo
// ========================================================================
// *** Dependencies  ******************************
#include "Header/MqttController.h"
#include "Header/DipswitchReader.h"

Core* core; 

void setup() {
  Serial.begin(BAUD_RATE);      // Re-Enable Serial for global scope usage
  Serial.println("Executing setup...");

  delay(100);                   // Give it some breathing room
  core = new Core();
}

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

  // TODO: Initialization logic goes here!
}

Core::~Core() { /* Not implemented */ }


//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
void Core::setup () 
{
  /* Not implemented */
}

void Core::loop ()
{
  m_mqtt->loop();
}