// consum_2.h

#include "consum_2.h"

#include <iostream>
#include <iomanip>


void consum_2::consumer()
{
	// fill in here
}


//*******===============================================================*******
//*******                            fetch_trigger                      *******
//*******               generates a pattern of read transtations
//*******===============================================================*******

void consum_2::fetch_trigger(){

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

