#include <Arduino.h>
#include "Header/Core.h"
// ========================================================================
// File:    main.cpp
// Date:    21-05-2019
// By:      Mark Meerlo
// ========================================================================
// *** Dependencies  ******************************
#include "Header/MqttController.h"

Core core;

void setup() {
  Serial.begin(BAUD_RATE);      // Re-Enable Serial for global scope usage
  Serial.println("Executing setup...");
}

void loop() {
  // put your main code here, to run repeatedly:
}


//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
Core::Core () :
m_PCB_ID(nullptr),
m_mqtt(nullptr)
{
  Serial.begin(BAUD_RATE);      // Initialize Serial for constructor scope time
  Serial.println("Initialized Serial monitor!");

  // TODO: Initialization logic goes here!

  Serial.flush();               // Make sure the Serial buffer is empty before closing
  Serial.end();                 // Clear Serial for constructor scope
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
  /* Not implemented */
}