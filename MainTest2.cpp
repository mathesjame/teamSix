#include <stdio.h>
#include <time.h>
#include "E101.h"

int samples = 64;
char row[64];
int oldError = 0;
float error = 0;
int thresh = 50;

int populate(){
	take_picture();
	//display_picture(5,0);
	for (int i = 0; i < samples; i++){
		row[i] = get_pixel(100, i*(320/samples), 3);
		
	}
	
	//Convert To 1s and 0s
	for (int i = 0; i < samples; i++){
		//Array values replaced with 0s or 1s based on their relationships to thresh
		if(row[i]<thresh){printf("0"); row[i]=0;}
		if(row[i]>thresh){printf("1"); row[i]=1;}
		
	}
	
	return 0;
}

float errCalc(){
	
	float newErrorP = 0;
	oldError = error;
	for(int i = 0; i < samples; i++){
		//Added 255 Multiplier
		newErrorP = newErrorP + (i-(samples/2))*row[i]*255;
		
	}
	
	
	float newErrorD = 0;
	
	newErrorD = (newErrorP-oldError)/10;
	//calculate I
	
	float newErrorI = 0;
	
	//calculate I
	
	//Check D and I calculation before uncommenting
	float newError = newErrorP;// + newErrorI + newErrorD;
	
return newError;}

int turn(double pidTurn){
	if (errCalc < 0){	
		set_motor(1, (int)-pidTurn/2 -63);
		set_motor(2, -pidTurn +63);
	}
	else if (errCalc > 0){
		set_motor(1, -pidTurn -63);
		set_motor(2, (int)-pidTurn/2 +63);
		
	}
	else {
		set_motor(1, 1);
		set_motor(2, 1);
	}
	return 0;
}

// if no white line? reverse?
// if err(all black = 0?)
//     set motors to go reverse until can see white

// if camera sees all white line(T junction)? turn left?
// if err(all white = 0?)
//    set motors to turn left until 1 white line, then back to normal pid

// if deadend? reverse on angle? turn 180 degrees?
// if err(all black = 0?)
//    if prevous pictures had white line, then set motors to reverse? or set motors to turn 180 degrees?
//    then go forwards as normal

// how to stop it driving the way it's come from?
// if turning corner or at deadends and has turned around, don't turn down same path as it's come from


int main (){
	init();
	
	
	populate();
	
	display_picture(3,0);
	
	//Calculate the threshold value for deciding between white lines and black
	int high = 0;
	int low = 10000;
	for (int i = 0; i < 64; i++){
		if(row[i]>high){high = row[i];}
		if(row[i]<low){low = row[i];}
		
	}
	thresh = (high-low)/2;
	
	while(true){
		//Take image again and recalculate line position
		populate();
		
		//Get new 
		error = (int)errCalc()*0.02;//Check This scale factor
		//Scale error to fit into motor
		if(error>190){error = 190;}
		if(error<-190){error = -190;}
		//Send error signal to turn
		turn(error);
		
		printf("%f\n", error);
		
		sleep1(0,1000);
	}
	
	return 0;}
	

