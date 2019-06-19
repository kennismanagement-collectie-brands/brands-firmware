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

    // Set all timeouts for the relais
    for(unsigned long previous : m_relaysTimeout)
    {
        previous = millis();
    }
}

RelayController::~RelayController () { /* No implementation */ }

//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
/*
 *  Loop method handles automatic timeouts for relais that are turned on but never
 *  turned off again
 */
void RelayController::loop()
{
    for(byte i = 0; i < 4; i++)
    {
        unsigned long currentMillis = millis();
        if(currentMillis - m_relaysTimeout[i] > m_timeoutInterval && digitalRead(m_relays[i]) == HIGH)
        {
            m_relaysTimeout[i] = currentMillis;
            this->setRelay(i, LOW);
        }
    }
}

/*
 *  Set a specific relay to either a ON (HIGH) or OFF (LOW) state.
 */ 
void RelayController::setRelay (int relay, bool state)
{
    // Prevent retrieving garbage values or causing segmentation faults
    if(relay < 0 || relay >= 4) return;
    digitalWrite(m_relays[relay], state);
    if(state == HIGH) m_relaysTimeout[relay] = millis();

    for(int i = 0; i < 4; i++)
    {
        if(i != relay && digitalRead(m_relays[i]) == HIGH)
        {
            digitalWrite(m_relays[i], LOW);
        }
    }
}