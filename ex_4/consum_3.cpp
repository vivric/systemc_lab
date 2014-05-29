// consum_3.cpp

#include "consum_3.h"

#include "systemc.h"
#include "tlm.h"

#include <iostream>
#include <iomanip>

// to make things easier readable ...
using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;


//*******===============================================================*******
//*******                             consumer                          *******
//*******===============================================================*******

// fill in here


// *******===============================================================******* //
// *******               implementation of nb_transport_bw               ******* //
// *******===============================================================******* //
//*******================================================*******
//  nb_transport_bw implementation of bw calls from targets
//*******================================================*******

// fill in here

//*******===============================================================*******
//*******                            fetch_trigger                      *******
//*******               generates a pattern of read transtations
//*******===============================================================*******

void consum_3::fetch_trigger(){

  while(true){
    wait(1200, SC_NS);
    fetch_event.notify(0, SC_NS);
    wait(800, SC_NS);
    fetch_event.notify(0, SC_NS);
    wait(1000, SC_NS);
    fetch_event.notify(0, SC_NS);
    wait(800, SC_NS);
    fetch_event.notify(0, SC_NS);
    wait(600, SC_NS);
    fetch_event.notify(0, SC_NS);
    wait(1200, SC_NS);
    fetch_event.notify(0, SC_NS);
  }
}

