#include "../Header/RelayController.h"
#include <Arduino.h>

// ========================================================================
// File:    RelayController.cpp
// Date:    24-05-2019
// By:      Arjan Kuiper
// ========================================================================


//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
RelayController::RelayController  () 
{ 
    for(int relay : m_relays)
    {
        pinMode(relay, OUTPUT);
    }

    this->setRelay(3, HIGH);
}
RelayController::~RelayController () { /* No implementation */ }



//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
void RelayController::setRelay (int relay, bool state)
{
    if(relay >= 4) return;      // Prevent retrieving garbage values or causing segmentation faults
    digitalWrite(m_relays[relay], state);
}