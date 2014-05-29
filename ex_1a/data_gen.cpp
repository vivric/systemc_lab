#include "data_gen.h"

void data_gen::generate(){

    unsigned short int iat;
    short unsigned int bytes;

    iat = rand()%10;

    dat.write(0);
    while(true){
	wait(iat, SC_US);
	bytes = (64 + rand()%1436);
	iat = (bytes + rand()%(6045-bytes))/155;

	dat.write(bytes);
	cout << sc_time_stamp() << ": #data_gen# number of bytes " << bytes << "\n";
    }
}
