#include "../Header/DipswitchReader.h"
#include <Arduino.h>
// ========================================================================
// File:    DipswitchReader.cpp
// Date:    21-05-2019
// By:      Mark Meerlo
// ========================================================================


//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
DipswitchReader::DipswitchReader () { /* No implementation */ }
DipswitchReader::~DipswitchReader () { /* No implementation */ }



//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
int DipswitchReader::fetchPCBID ()
{
    int m_dipswitches[4]            { 5, 4, 3, 2 };
    int m_binarySize[4]             { 1, 2, 4, 8 };

    // Initialize pins
    for (int i =0; i < 4; i++) {
        pinMode(m_dipswitches[i], INPUT_PULLUP); 
    }

    // Calculate ID
    int result = 0;

    for (int i = 0; i < 4; i++) {
        if (digitalRead(m_dipswitches[i]) == 1) { result += m_binarySize[i]; }
    }

    // De-Inputize pins
    for (int i =0; i < 4; i++) {
        pinMode(m_dipswitches[i], INPUT); 
    }
    
    return result;
}