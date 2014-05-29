// consum_1.cpp

#include "consum_1.h"

void consum_1::consumer() {

while (true)
{
	wait();
	if(fetch.read()==true && fifo_empty.read()==false)
	{
		get_data.write(true);
		wait();
		if(fifo_empty.read()==false)
		{
			data_valid.write(true);
			consumed_data=data_write.read();
			cout << sc_time_stamp() << ": consumer " <<name()<<" : "<< consumed_data << " fetched data" << endl;
		}
		else
		{
			data_valid.write(false);
		}
	}
	else
	if(fetch.read()==true && fifo_empty.read()==true)
		data_valid.write(false);
	get_data.write(false);
}

}
// generate a pattern of read actions
void consum_1::fetch_trigger() {

	fetch.write(false);
	wait(50, SC_NS);
	while(true) {
		wait(400, SC_NS);
		fetch.write(true);
		wait(100, SC_NS);
		fetch.write(false);
		wait(500, SC_NS);
		fetch.write(true);
		wait(100, SC_NS);
		fetch.write(false);
		wait(400, SC_NS);
		fetch.write(true);
		wait(100, SC_NS);
		fetch.write(false);
		wait(300, SC_NS);
		fetch.write(true);
		wait(1200, SC_NS);
		fetch.write(false);
		wait(200, SC_NS);
		fetch.write(true);
		wait(100, SC_NS);
		fetch.write(false);
	}
}
