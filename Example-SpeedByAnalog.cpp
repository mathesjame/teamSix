# include <stdio.h>
# include <time.h>
# include "E101.h"

int main (){
	init();
	int irSensor = 1;
	
	while (irSensor > 0){
		irSensor = read_analog(0);
		int speed = irSensor * 0.4;
		
		set_motor(1, speed);
	    sleep1(0 ,100000);
    }
    
return 0;
}
