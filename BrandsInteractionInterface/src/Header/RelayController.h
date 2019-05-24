#ifndef RELAYCONTROLLER_H
#define RELAYCONTROLLER_H



class RelayController {

public:
//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
RelayController                                 ();
~RelayController                                ();


//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
void setRelay                                   (int relay, 
                                                 bool state);


private:
//* ***********************************************
//          PRIVATE ATTRIBUTES
//* ***********************************************
int                                             m_relays[4] = {27, 25, 32, 4};


};
#endif