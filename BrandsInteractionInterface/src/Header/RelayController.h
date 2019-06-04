#ifndef RELAYCONTROLLER_H
#define RELAYCONTROLLER_H

class RelayController {

public:
//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
RelayController                             ();
~RelayController                            ();
void loop                                   ();

//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
void setRelay                               (int relay, 
                                            bool state);

private:
//* ***********************************************
//          PRIVATE ATTRIBUTES
//* ***********************************************
int                                         m_relays[4] = {27, 25, 32, 4};
unsigned long                               m_relaysTimeout[4];
long                                        m_timeoutInterval = 1000 * 10;

};
#endif