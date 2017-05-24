#include <stdio.h>
#include <time.h>
#include "E101.h"

// Stops motor, when sensor is reading small error signal.
int main(){
    init();
    int input;
    input = 0;
    int adc_reading;
    while (input <= 600){
        adc_reading = read_analog(0);
        input = adc_reading;
        set_motor(1, 254);
    }
    set_motor(1,0);
}

// Reads error signal, and avg 5 times to get sexc value.
int main (){ 
init (); 
  int adc_reading;
  int i = 0;
  int total = 0;
  
  while(i<5){
      
      adc_reading = read_analog(0);
      total+= adc_reading;
      i+ = 1;
}

return 0;
} 
\

// Code for AVC to navigate trough maze.
// FRONT sensor reading
int main(){
init ();
    int adc_reading = read_analog(0);
    

}

// RIGHT sensor reading
int main(){
init ();
    int adc_reading = read_analog(0);
} 


  


