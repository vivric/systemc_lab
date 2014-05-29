// fifo_2.cpp

#include "fifo_2.h"

#include <iostream>
#include <iomanip>

bool fifo_2::write_fifo(unsigned char *data, unsigned int &count)
{
	bool result = false;

	unsigned int first_part;
	unsigned int len;  // number of actually written data
 	sc_time delay;
		
	unsigned char *ptr;
	ptr = data;

	if(fill_level == fifo_size)          // no free space
		len = 0;
	else if(fill_level+count > fifo_size)  // not enough space for all data
		len = fifo_size-fill_level;  // less data will be written
	else{
		len = count;
		result = true;
	}			

	if(len > 0)
	{
		// set delay according to transfertime of len bytes over 32 bit wide interface
		// with 50 ns cycle time
		delay = sc_time((int)((len+3)/4)*50, SC_NS);

		wait(delay);

		if(write_addr+len < fifo_size)  // write in one chunk
			memcpy((fifo_data+write_addr), ptr, len);
		else{
			first_part = fifo_size-write_addr; // write in two chunks
			memcpy((fifo_data+write_addr), ptr, first_part);
			memcpy((fifo_data), ptr+first_part, len-first_part);
		}

		write_addr = (write_addr+len)%fifo_size;
	
		fill_level = fill_level + len;
	
		cout << endl << sc_time_stamp() << " " << name() <<": 0x ";
		cout << hex;
		for(int i=0;i<len;i++)
			cout << std::setw(2) << std::setfill('0') << (int)*(ptr+i) << " ";
		cout << dec  << " written. "<< endl;	
	}
	else
		cout << endl << sc_time_stamp() << " " << name() <<": full - no data have been written"<<endl;
	

	output_fifo_status();
	count = len;		
	return result;
}


bool fifo_2::read_fifo(unsigned char *data, unsigned int &count)
{
	bool result = false;

	unsigned int first_part;
	sc_time delay;

	unsigned char *ptr;
	ptr = data;

	unsigned int len;     // amount of data

	if(fill_level == 0) // read attempt from empty FIFO
		len = 0;
	else if(fill_level < count) // not enough data to read
		len = fill_level;  // less data will be read
	else{
		len = count;
		result = true;;
	}

	if(len > 0)
	{
		// set delay according to transfertime of len bytes over 32 bit wide interface
		// with 50 ns cycle time
		delay = sc_time((int)((len+3)/4)*50, SC_NS);

		wait(delay);

		if(read_addr+len < fifo_size)  // read in one chunk
			memcpy(ptr, (fifo_data+read_addr), len);
		else{
			first_part = fifo_size-read_addr; // read in two chunks
			memcpy(ptr, (fifo_data+read_addr), first_part);
			memcpy(ptr+first_part, (fifo_data), len-first_part);
		}

		read_addr = (read_addr+len)%fifo_size;
		fill_level = fill_level - len;

		cout << endl << sc_time_stamp() << " " << name() << ": 0x ";
		cout << hex;
		for(int i=0;i<len;i++)
			cout << std::setw(2) << std::setfill('0') << (int)*(ptr+i) << " ";
		cout << dec  << " read. " << endl;

	}
	else
		cout << endl << sc_time_stamp() << " "<< name()<< ": empty - no data have been read"<<endl;

	output_fifo_status();
	count = len;		
	return result;
}

// helper function to output content of FIFO
void fifo_2::output_fifo_status()
{
	cout<<"     ";
	cout << "Current "<<name()<<" status: write address: "<<write_addr<<", read address: "\
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

