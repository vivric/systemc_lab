// fifo_1.cpp

#include "fifo_1.h"

void fifo_1::do_write() {

    // write only if requested and not full
	if (wr.read() == true && full.read() == false) {

		// write data & update write count
		int write_data = data_in.read();
		fifo_data[write_count.read() % fifo_size] = write_data;
		write_count.write(write_count.read() + 1);

		cout << sc_time_stamp() << ": fifo: " << write_data
			<< " written to address " << write_count.read() % fifo_size << endl;
	}
}

void fifo_1::do_read() {

	// read only if requested and not empty
	if (rd.read() == true && empty.read() == false) {

		// read data & update read count
		int read_data = fifo_data[read_count.read() % fifo_size];
		read_count.write(read_count.read() + 1);
		data_out.write(read_data);

		cout << sc_time_stamp() << ": fifo: " << read_data
			<< " read from address " << read_count.read() % fifo_size << endl;
	}
}

void fifo_1::set_flags() {

	// set flags according to fill level
	fill_level = write_count.read() - read_count.read();
	empty.write(fill_level == 0);
	full.write(fill_level == fifo_size);
}

