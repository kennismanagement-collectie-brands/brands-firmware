// ========================================================================
// File:    RelayController.cpp
// Date:    24-05-2019
// By:      Arjan Kuiper
// ========================================================================

#include <Arduino.h>
#include "../Header/RelayController.h"

//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
RelayController::RelayController  () 
{
    // Set all the relay pins to OUTPUT pins
    for(int relay : m_relays)
    {
        pinMode(relay, OUTPUT);
    }
}

RelayController::~RelayController () { /* No implementation */ }

//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
/*
 *  Set a specific relay to either a ON (HIGH) or OFF (LOW) state.
 */ 
void RelayController::setRelay (int relay, bool state)
{
    // Prevent retrieving garbage values or causing segmentation faults
    if(relay < 0 || relay >= 4) return;
    digitalWrite(m_relays[relay], state);
}