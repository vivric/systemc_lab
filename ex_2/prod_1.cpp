// prod_1.cpp

#include "prod_1.h"

void prod_1::producer(){
	while (true) {
		wait();
		if (send.read() == true && f_full.read() == false) {
			put.write(true);
			dat1.write(prod_data);
			cout << sc_time_stamp() << ": producer " <<name()<<" : "<< prod_data << " output" << endl;
			prod_data++;
		} else {
			if (put.read() == true && f_full.read() == true) {
				prod_data--; // previous write failed due to full fifo
			}
			put.write(false);
		}
	}
}

// generate a pattern of write actions
void prod_1::send_trigger(){

	send.write(false);
	wait(50, SC_NS);
	while(true){
		wait(200, SC_NS);
		send.write(true);
		wait(100, SC_NS);
		send.write(false);
		wait(200, SC_NS);
		send.write(true);
		wait(100, SC_NS);
		send.write(false);
		wait(100, SC_NS);
		send.write(true);
		wait(100, SC_NS);
		send.write(false);
		wait(200, SC_NS);
		send.write(true);
		wait(100, SC_NS);
		send.write(false);
		wait(200, SC_NS);
		send.write(true);
		wait(1000, SC_NS);
		send.write(false);
		wait(100, SC_NS);
		send.write(true);
		wait(100, SC_NS);
		send.write(false);
		wait(1800, SC_NS);
		send.write(false);
	}
}
