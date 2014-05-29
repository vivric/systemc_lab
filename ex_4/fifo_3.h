// fifo_3.h

#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/peq_with_get.h"

// to make things easier readable ...
using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

SC_MODULE(fifo_3)
{

	// *******========================================*******
	// *******             Member Variables           *******
	// *******========================================*******
	public:
	simple_target_socket<fifo_3>  fifo2consum_socket;  //  target socket for consumer
	simple_target_socket<fifo_3>  fifo2prod_socket;	   //  target socket for producer


	private:
	unsigned char *fifo_data;     // points to the data stored in the FIFO
	const int fifo_size;          // size FIFO in multiples of unsigned char
	int write_addr, read_addr;    // current write and read address of the FIFO
	int fill_level;               // current fill level of FIFO

	// we use two PEQs, one for read transactions and one for write transactions
	peq_with_get<tlm_generic_payload> r_peq;
	peq_with_get<tlm_generic_payload> w_peq;

	// the processes that actually perform read and write
	void do_read();
	void do_write();


	// nb_transport_fw() - Nonblocking Transport Forward path
	//                    (for requests, to be called from producer or consumer)
	public:
	tlm_sync_enum                            // returns status
	nb_transport_fw
	( tlm_generic_payload  &payload,         // ref to payload
	  tlm_phase          &phase,		 // ref to phase
	  sc_time          &delay_time           // ref to delay time
	);

	private:
	void output_fifo_status();  // function to output current FIFO content in a text line

	// *******=================================================*******
	// *******                    Constructor                  *******
	// *******=================================================*******
	public:
	SC_CTOR(fifo_3):
		fifo2prod_socket("fifo2prod_socket"),      // call cunstructors of sockets
		fifo2consum_socket("fifo2consum_socket"),
		fifo_size(40),				   // initialize FIFO size
		r_peq("read_peq"),
		w_peq("write_peq")
	{

		// register nb_transport_fw function with sockets
		fifo2prod_socket.register_nb_transport_fw(this, &fifo_3::nb_transport_fw);
		fifo2consum_socket.register_nb_transport_fw(this, &fifo_3::nb_transport_fw);


		// register the read and write processes with the simulation kernel
		SC_THREAD(do_read);
		sensitive << r_peq.get_event();
		SC_THREAD(do_write);
		sensitive << w_peq.get_event();

		// initialization of FIFO: allocate memory and reset read/write addresses
		fifo_data = new unsigned char[fifo_size];

		write_addr = 0;
		read_addr  = 0;
		fill_level = 0;
	}


};

