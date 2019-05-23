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

Core core;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}


//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
Core::Core () :
m_PCB_ID(DipswitchReader::fetchPCBID()),
m_mqtt(nullptr)
{
  /* Not implemented */

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