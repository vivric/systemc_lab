// prod_2.cpp

#include "prod_2.h"

#include <iostream>
#include <iomanip>


void prod_2::producer()
{

	unsigned int data_length;  // number of bytes that should be written [1; 16]
	unsigned char prod_data[16];

	bool success;

	while(true)
	{
		// fill in the appropriate statement for synchonization with
		// the send_trigger process

		// generate random data of random lenght between 1 and 16 bytes
		data_length = 1+rand()%16;
		for(int i=0;i<data_length;i++)
			*(prod_data+i) = rand()%256;

		cout<<endl<<sc_time_stamp()<<" "<<name()<<" wants to write "<<data_length<<" bytes: 0x ";
		cout << hex;                     // switch to hexadecimal mode
			for(int i=0;i<data_length;i++)
			cout << std::setw(2) << std::setfill('0') << (int)*(prod_data+i)<<" ";
		cout << dec << endl;             // switch back to decimal mode

		// call transaction
		success = prod2fifo_port->write_fifo(prod_data, data_length);

		cout<<endl<<sc_time_stamp()<<" "<<name()<<" transaction is finished";

		if(success)
			cout<<" successfully.";
		else
			cout<<" not or only in part successfully.";
		cout<<endl;

		cout<<"     "<<name()<<" wrote "<<data_length<<" bytes."<<endl;
	}

}


// *******===============================================================******* //
// *******                             send_trigger                      ******* //
// *******===============================================================******* //

void prod_2::send_trigger() {

  while(true){
    wait(300, SC_NS);
    send_event.notify(0, SC_NS);
    wait(800, SC_NS);
    send_event.notify(0, SC_NS);
    wait(200, SC_NS);
    send_event.notify(0, SC_NS);
    wait(200, SC_NS);
    send_event.notify(0, SC_NS);
    wait(200, SC_NS);
    send_event.notify(0, SC_NS);
    wait(400, SC_NS);
    send_event.notify(0, SC_NS);
    wait(1000, SC_NS);
    send_event.notify(0, SC_NS);
    wait(1000, SC_NS);
    send_event.notify(0, SC_NS);
    wait(400, SC_NS);
    send_event.notify(0, SC_NS);
  }
}

