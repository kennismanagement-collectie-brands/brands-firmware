#ifndef DIPSWITCHREADER_H
#define DIPSWITCHREADER_H

class DipswitchReader final {

public:
//* ***********************************************
//          PUBLIC METHODS
//* ***********************************************
static int fetchPCBID                           ();

private:
//* ***********************************************
//          CONSTRUCTOR & DESTRUCTOR
//* ***********************************************
DipswitchReader                                 ();
~DipswitchReader                                ();

};
#endif