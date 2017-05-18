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
		if(row[i]<thresh){printf("0");}
		if(row[i]>thresh){printf("1");}
		
	}
	
	return 0;
}

float errCalc(){
	
	float newErrorP = 0;
	oldError = error;
	for(int i = 0; i < samples; i++){
		newErrorP = newErrorP + (i-(samples/2))*row[i];
		
	}
	
	
	float newErrorD = 0;
	
	newErrorD = (newErrorP-oldError)/10;
	//calculate I
	
	float newErrorI = 0;
	
	//calculate I
	
	
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


int main (){
	init();
	
	
	
	
	int high = 0;
	int low = 10000;
	
	
	populate();
	
	display_picture(3,0);
	
	for (int i = 0; i < 64; i++){
		if(row[i]>high){high = row[i];}
		if(row[i]<low){low = row[i];}
		
	}
	thresh = (high-low)/2;
	
	while(true){
		populate();
		
		
		error = (int)errCalc()*0.02;//Check This scale factor
		//Scale error to fit into motor
		if(error>190){error = 190;}
		if(error<-190){error = -190;}
		
		turn(error);
		printf("%f\n", error);
		
		sleep1(0,1000);
	}
	
	return 0;}
	

