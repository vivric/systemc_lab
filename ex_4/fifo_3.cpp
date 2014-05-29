//fifo_3.cpp

#include "fifo_3.h"			// our header file
#include "tlm.h"
#include "systemc.h"


#include <iostream>
#include <iomanip>
             
// to make things easier readable...
using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;


//*******================================================*******
//  nb_transport_fw implementation of fw calls from initiators 
//*******================================================*******
tlm_sync_enum
fifo_3::nb_transport_fw
( tlm_generic_payload  &payload,               // ref to Generic Payload 
  tlm_phase            &phase,                 // ref to phase
  sc_time              &delay_time             // ref to delay time 
)
{ 

	// check whether transaction os correctly initiated
	if(phase != BEGIN_REQ){
		cout << sc_time_stamp()<<" ERROR in FIFO: nb_transport_fw call with phase!=BEGIN_REQ" << endl;
		exit(1);
	}

	// determine operation and how much data is involved
	tlm_command cmd = payload.get_command();  
	int len = payload.get_data_length();

	if(cmd == TLM_WRITE_COMMAND)
	{
		// increase delay time by a value corresponding to transfertime of len bytes 
		// over 32 bit wide interfacewith 50 ns cycle time
		delay_time += sc_time((int)((len+3)/4)*50, SC_NS);

		// put transaction into write payload event queue: the do_write() process
		// will be triggered after delay time
		w_peq.notify(payload, delay_time);
		payload.set_response_status(TLM_OK_RESPONSE);
	}

	else if(cmd == TLM_READ_COMMAND)
	{
		// increase delay time by a value corresponding to transfertime of command 
		// assumed to 1 clock cycle with 50 ns cycle time
		delay_time += sc_time(50, SC_NS);

		// put transaction into read payload event queue: the do_read() process
		// will be triggered after delay time
		r_peq.notify(payload, delay_time);
		payload.set_response_status(TLM_OK_RESPONSE);
	}
	
	// finish the first phase of the transaction
        phase = END_REQ;
	return TLM_UPDATED;

}

void fifo_3::do_read()
{

	unsigned int first_part;
        tlm_sync_enum tlm_resp;
	tlm_response_status status;
	sc_time delay;
	tlm_phase phase;
	tlm_generic_payload *payload;

	unsigned char* ptr;   // pointer where to put data
	unsigned int len;     // amount of data


	while(true)
	{
		// wait for read to be triggered from read payload event queue
		wait();

		// get the transaction out of the read payload event queue
		payload = r_peq.get_next_transaction();


		// functions to get information out of the generic payload
		ptr = payload->get_data_ptr();   // get pointer where to put data
		len = payload->get_data_length();  // how much data
	
		if(fill_level == 0){ // read attempt from empty FIFO
			len = 0;
			status = TLM_BURST_ERROR_RESPONSE;
		}
		else if(fill_level < len){ // not enough data to read
			len = fill_level;  // less data will be read
			status = TLM_BURST_ERROR_RESPONSE;
		}
		else
			status = TLM_OK_RESPONSE;

		if(len > 0)
		{
			if(read_addr+len < fifo_size)  // read in one chunk
				memcpy(ptr, (fifo_data+read_addr), len);
			else{
				first_part = fifo_size-read_addr; // read in two chunks
				memcpy(ptr, (fifo_data+read_addr), first_part);
				memcpy(ptr+first_part, (fifo_data), len-first_part);
			}

			read_addr = (read_addr+len)%fifo_size;
			fill_level = fill_level - len;

			cout << endl << sc_time_stamp() << " fifo: 0x ";
			cout << hex;
			for(int i=0;i<len;i++)
				cout << std::setw(2) << std::setfill('0') << (int)*(ptr+i) << " ";
			cout << dec  << " read. " << endl;
   		}
		output_fifo_status();

		// prepare backward call
		payload->set_data_length(len);
		payload->set_response_status(status);
		phase = BEGIN_RESP;
		delay = SC_ZERO_TIME;

		// call nb_transport_bw
		tlm_resp = fifo2consum_socket->nb_transport_bw(*payload, phase, delay);
		if(tlm_resp != TLM_COMPLETED || phase != END_RESP)
		{
			cout<<endl<<sc_time_stamp()<<" fifo: read response not appropriately completed" << endl;
		}
	}
}

void fifo_3::do_write()
{

	unsigned int first_part;
        tlm_sync_enum tlm_resp;
	tlm_response_status status;
	sc_time delay;
	tlm_phase phase;
	tlm_generic_payload *payload;

	unsigned char* ptr;   // pointer where to put data
	unsigned int len;     // amount of data


	while(true)
	{
		// wait for write to be triggered from write payload event queue
		wait();

		// get the transaction out of the write payload event queue
		payload = w_peq.get_next_transaction();
		
		// functions to get information out of the generic payload
		ptr = payload->get_data_ptr();   // get pointer to data
		len = payload->get_data_length();  // how much data
	
		if(fill_level == fifo_size){ // no free space
			len = 0;
			status = TLM_BURST_ERROR_RESPONSE;
		}
		else if(fill_level+len > fifo_size){ // not enough space for all data
			len = fifo_size-fill_level;  // less data will be written
			status = TLM_BURST_ERROR_RESPONSE;
		}
		else
			status = TLM_OK_RESPONSE;			
	
		if(len > 0)
		{
			if(write_addr+len < fifo_size)  // write in one chunk
				memcpy((fifo_data+write_addr), ptr, len);
			else{
				first_part = fifo_size-write_addr; // write in two chunks
				memcpy((fifo_data+write_addr), ptr, first_part);
				memcpy((fifo_data), ptr+first_part, len-first_part);
			}
	
			write_addr = (write_addr+len)%fifo_size;
	
			fill_level = fill_level + len;
	
			cout << endl << sc_time_stamp() << " fifo: 0x ";
			cout << hex;
			for(int i=0;i<len;i++)
				cout << std::setw(2) << std::setfill('0') << (int)*(ptr+i) << " ";
			cout << dec  << " written. "<< endl;
   		}
		output_fifo_status();
		
		// prepare backward call
		payload->set_data_length(len);
		payload->set_response_status(status);
		phase = BEGIN_RESP;
		delay = SC_ZERO_TIME;

		// call nb_transport_bw
		tlm_resp = fifo2prod_socket->nb_transport_bw(*payload, phase, delay);
		if(tlm_resp != TLM_COMPLETED || phase != END_RESP)
		{
			cout<<endl<<sc_time_stamp()<<" fifo: write response not appropriately completed" << endl;
		}

	}
}


// helper function to output content of FIFO
void fifo_3::output_fifo_status()
{
	cout<<"     ";
	cout << "Current fifo status: write address: "<<write_addr<<", read address: "\
	     << read_addr<<", fill level: "<< fill_level<<endl;   
	cout<<"     ";
	cout << hex;    // switch to hexadecimal mode;
	if(fill_level==0)
		for(int i=0;i<fifo_size;i++)
			cout<<"-- ";
	else if(fill_level==fifo_size)
		for(int i=0;i<fifo_size;i++)
			cout<<std::setw(2)<<std::setfill('0')<<(int)*(fifo_data+i)<<" ";
	else if(write_addr>read_addr)
		for(int i=0;i<fifo_size;i++)
			if((i>=read_addr)&&(i<write_addr))
				cout<<std::setw(2)<<std::setfill('0')<<(int)*(fifo_data+i)<<" ";
			else
				cout<<"-- ";
	else if(write_addr<read_addr)
		for(int i=0;i<fifo_size;i++)
			if((i>=read_addr)||(i<write_addr))
				cout<<std::setw(2)<<std::setfill('0')<<(int)*(fifo_data+i)<<" ";
			else
				cout<<"-- ";
	cout << dec<<endl;
}

