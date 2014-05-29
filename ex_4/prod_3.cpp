// prod_3.cpp

#include "prod_3.h"
#include "tlm.h"
#include "systemc.h"

#include <iostream>
#include <iomanip>

// to make things easier readable ...
using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;


// *******===============================================================******* //
// *******                             producer                          ******* //
// *******===============================================================******* //

void prod_3::producer()
{
  
	// setup generic payload with an appropriate buffer for the read data to be written
	tlm_generic_payload trans;
	unsigned char data[16];
	trans.set_data_ptr(data);

	tlm_sync_enum tlm_resp;
	tlm_response_status tlm_stat;
	sc_time delay;
	tlm_phase phase;
    
	int data_length;  // number of bytes that should be written [1; 16]
	int data_written;    // number of bytes that actually have been written
	unsigned char* prod_data;

	// needed to wait until a transaction is finished
	bool pending_transaction = false;
    

	while(true){

		if(pending_transaction){
			cout<<sc_time_stamp()<<" producer waiting until transaction is finished"<<endl;
			wait(response_event);

			// now response via nb_transport_bw has arrived
			// evaluate return status of transaction 
			tlm_stat = trans.get_response_status();
			cout<<endl<<sc_time_stamp()<<" producer transaction is finished";

			if(tlm_stat == TLM_OK_RESPONSE)
				cout<<" successfully.";
			else
				cout<<" not or only in part successfully.";
			cout<<endl;
	
			data_written = trans.get_data_length();

			cout<<"     producer wrote "<<data_written<<" of "<<data_length<<" bytes."<<endl;
			pending_transaction = false;
		}

		// now we have to wait until new write request is issued
		wait(send_event);

	
		// setup the generic payload
		// generate random data of random lenght between 1 and 16 bytes
		data_length = 1+rand()%16;
		for(int i=0;i<data_length;i++)
			*(data+i) = rand()%256;
	
		trans.set_command(TLM_WRITE_COMMAND);
		trans.set_data_length(data_length);
		trans.set_response_status(TLM_GENERIC_ERROR_RESPONSE);
	
		// prepare transaction
		delay = SC_ZERO_TIME;
		phase = BEGIN_REQ;
    
		// output message 
		cout<<endl<<sc_time_stamp()<<" producer wants to write "<<data_length<<" bytes: 0x ";
		cout << hex;                     // switch to hexadecimal mode
			for(int i=0;i<data_length;i++)
			cout << std::setw(2) << std::setfill('0') << (int)*(data+i)<<" ";
		cout << dec << endl;             // switch back to decimal mode
	
		// call transaction
		tlm_resp = prod2fifo_socket->nb_transport_fw(trans, phase, delay);

		pending_transaction = true;
		if(tlm_resp != TLM_UPDATED || phase != END_REQ)
		{
			cout<<endl<<sc_time_stamp()<<" producer: write request not appropriately completed" << endl;
		}

	}  // end while true
}  // end producer 

// *******===============================================================******* //
// *******               implementation of nb_transport_bw               ******* //
// *******===============================================================******* //
//*******================================================*******
//  nb_transport_bw implementation of bw calls from targets 
//*******================================================*******
tlm_sync_enum                                        
prod_3::nb_transport_bw
( tlm_generic_payload  &payload,               // ref to Generic Payload 
  tlm_phase            &phase,                 // ref to phase
  sc_time              &delay_time             // ref to delay time 
)
{

	if(phase == BEGIN_RESP)
		cout<<endl<<sc_time_stamp()<<" producer: write confirmation coming" << endl;
	else
		cout<<endl<<sc_time_stamp()<<" producer: write not correctly confirmed" << endl;

	// increase delay time by a value corresponding to transfer time of 
	// confirmation assumed to 1 clock cycle with 50 ns cycle time
	delay_time += sc_time(50, SC_NS);

	// consume process should go on after time needed for the confirmation
	response_event.notify(delay_time);

	// finish the transaction (end of 2nd phase)
	phase = END_RESP;
	return TLM_COMPLETED;


}




// *******===============================================================******* //
// *******                             send_trigger                      ******* //
// *******===============================================================******* //

void prod_3::send_trigger() {

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
