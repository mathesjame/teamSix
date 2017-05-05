# include <stdio.h>
# include <time.h>
# include "E101.h"

int main (){
  init();
  
  // turn_left and int duration is guide only
  int turn_left(int duration){
    set_motor(1, -127);
    set_motor(2, 127);
    sleep1(0 ,500000);
    sleep1(0,500000);
  }
return 0;
}
