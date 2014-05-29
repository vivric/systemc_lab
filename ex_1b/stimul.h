#include "systemc.h"

SC_MODULE(stimul){
  sc_out<bool> clk;
  sc_out<bool> res;
    
  void c_gen();
  void r_gen();
  
  SC_CTOR(stimul){
    SC_THREAD(c_gen);
    SC_THREAD(r_gen);
  }
};
