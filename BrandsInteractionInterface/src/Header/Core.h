#ifndef CORE_H
#define CORE_H

// *** Forward Declarations ***********************
class MqttController;

// *** Definitions ********************************
const int BAUD_RATE = 115200;



class Core {

public:
//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
Core                                            ();
~Core                                           ();


//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
void setup                                      ();
void loop                                       ();


private:
//* ***********************************************
//          PRIVATE ATTRIBUTES
//* ***********************************************
// Variables to keep track of elapsed time without blocking the core
unsigned long                                   m_startMillis = millis();
unsigned long                                   m_currentMillis;
const unsigned long                             m_delay = 5000;

int                                             m_PCB_ID;
MqttController*                                 m_mqtt;


};
#endif