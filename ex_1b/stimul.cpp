#include "stimul.h"

void stimul::c_gen(){

  bool takt=false;
  
  while(true){
    takt = !takt;
    clk.write(takt);
    wait(5, SC_NS);
  }
}

void stimul::r_gen(){

  bool rset = true;
  res.write(rset);
  wait(17, SC_NS);
  rset = false;
  res.write(rset);
  wait(10, SC_NS);
  rset = true;
  res.write(rset);
}  
  
