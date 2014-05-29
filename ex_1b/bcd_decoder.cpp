#include "bcd_decoder.h"

void bcd_decoder::decode(){
  
  unsigned int val_int;
  
  val_int = val.read();
  
  lo.write(val_int%10);
  hi.write((val_int/10)%10);
}
