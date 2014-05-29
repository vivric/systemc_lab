#include "systemc.h"

SC_MODULE(polic){
    sc_in<short unsigned int> size;
    sc_out<bool> discard;

    int r_pol;
    int max;
    int counter;
    sc_time last_arrival_time;
    int dec;

    void policer();

    SC_CTOR(polic){
	SC_METHOD(policer);
	sensitive << size;

	r_pol = 30;
	max = 1500;
	counter = 0;
	last_arrival_time = SC_ZERO_TIME;
    }
};
	    
