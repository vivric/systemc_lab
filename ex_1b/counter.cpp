#include "counter.h"

void counter::count(){
  while(true){
    if(res.read()==0)
{
      cnt_int = 0;

} 
   else
{
      cnt_int = (cnt_int+1)%100;

}     
    cnt.write(cnt_int);
    //cout << sc_time_stamp() << ": #counter# count_value " << cnt_int << "\n";
    
    wait();
  }
}
