#include "data_gen.h"
#include "polic.h"

int sc_main(int argc, char *argv[]){

    sc_signal<short unsigned int> data_amount;
    sc_signal<bool> disc_packet;

    sc_set_time_resolution(1, SC_US);

    data_gen dg1("m1");
    dg1.dat(data_amount);

    polic p1("m2");
    p1.size(data_amount);
    p1.discard(disc_packet);


  
    sc_trace_file *tf = sc_create_vcd_trace_file("traces");  
    sc_trace(tf, data_amount, "data_amount");
    sc_trace(tf, disc_packet, "disc_packet");
    sc_trace(tf, p1.counter, "counter");

    int n_cycles;
    if(argc != 2){
        cout << "default n_cycles = 200\n";
        n_cycles = 200;
    }
    else
        n_cycles = atoi(argv[1]);
 
    sc_start(n_cycles, SC_US);

    sc_close_vcd_trace_file(tf);
 
    return(0);
}
