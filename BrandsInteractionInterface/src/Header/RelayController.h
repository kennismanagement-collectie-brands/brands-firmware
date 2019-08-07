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
int                                         m_relays[5] = {27, 25, 32, 22, 21};
unsigned long                               m_relaysTimeout[5];
long                                        m_timeoutInterval = 1000 * 60 * 5; // 5 minutes

};
#endif