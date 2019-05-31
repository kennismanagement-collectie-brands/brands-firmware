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
MqttController*                                 m_mqtt;

};
#endif