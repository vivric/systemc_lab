#include "polic.h"

void polic::policer(){

    unsigned short int d_amount;
    int dec;
    
    sc_time t;
    t = sc_time_stamp() - last_arrival_time;

    dec = t.value()*r_pol;

    last_arrival_time = sc_time_stamp();

    counter = ((counter-dec)<0) ? 0 : counter-dec;

    cout << last_arrival_time << ": #polic# updated counter: " << counter;

    d_amount = size.read();
    if(counter+d_amount > max){
	discard.write(true);
	cout << ", new counter: " << counter << " discard:" << true << endl;
    }
    else{
	counter += d_amount;
	discard.write(false);
	cout << ", new counter: " << counter << " discard:" << false << endl;
    }
}
