#include <Arduino.h>
#include "Header/Core.h"
// ========================================================================
// File:    main.cpp
// Date:    21-05-2019
// By:      Mark Meerlo
// ========================================================================
// *** Dependencies  ******************************
#include "Header/MqttController.h"

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
Core::Core ()
{
  Serial.println("Initialized Serial monitor!");
  m_PCB_ID = 0;
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
  m_currentMillis = millis();
  if(m_currentMillis - m_startMillis >= m_delay)
  {
    m_mqtt->loop();
    Serial.printf("Core Looped in %dms\n", millis() - m_currentMillis);
    m_startMillis = m_currentMillis;
  }
}