#include "systemc.h"

SC_MODULE(counter){
  sc_in<bool> clk;
  sc_in<bool> res;
  sc_out<unsigned short int> cnt;
  
  private:
  // variable to store counter value
  unsigned short int cnt_int;

  // counter process
  void count();
  
  public:
  SC_CTOR(counter){
    SC_THREAD(count);
    sensitive << clk.pos();
  }
};

