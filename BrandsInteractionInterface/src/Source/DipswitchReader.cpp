// ========================================================================
// File:    DipswitchReader.cpp
// Date:    21-05-2019
// By:      Mark Meerlo
// ========================================================================

#include <Arduino.h>
#include "../Header/DipswitchReader.h"

//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
DipswitchReader::DipswitchReader () { /* No implementation */ }
DipswitchReader::~DipswitchReader () { /* No implementation */ }

//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
/*
 *  Fetches the ID of the PCB using the dipswitches on the printed circuit board.
 *  A number is generated from the dipswitches using the corresponding binary representations
 */ 
int DipswitchReader::fetchPCBID ()
{
    return 0;

    int m_dipswitches[4]            { 22, 21, 17, 16};
    int m_binarySize[4]             { 1, 2, 4, 8 };

    // Initialize pins
    for (int i =0; i < 4; i++) {
        pinMode(m_dipswitches[i], INPUT_PULLUP); 
    }

    // Calculate ID
    int result = 0;

    for (int i = 0; i < 4; i++) {
        if (digitalRead(m_dipswitches[i]) == LOW) { result += m_binarySize[i]; }
    }

    // De-Inputize pins
    /*for (int i =0; i < 4; i++) {
        pinMode(m_dipswitches[i], INPUT); 
    }*/
    
    return result;
}