#include <stdio.h>
#include <time.h>
#include "E101.h"

int samples = 64;
char row[64];
int oldError = 0;
float error = 0;



//Takes a picture and fills an array of values with a spaced 
//row of pixels across that image.
int populate(){
	take_picture();
	//display_picture(5,0);
	for (int i = 0; i < samples; i++){
		row[i] = 50;
    if(i > 20 && i < 26){row[i]=240;}
		
	}
	return 0;
}



//Calculates the Error value for stage 2/3
float calcError(){
	
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
	
	
	float newError = newErrorP + newErrorI + newErrorD;
	
return newError;}

int turn(double pidTurn){
	if (errCalc < 0){	
		set_motor(1, pidTurn);
		set_motor(2, -pidTurn/2);
	}
	else if (errCalc > 0){
		set_motor(1, -pidTurn/2);
		set_motor(2, pidTurn);
		
	}
	else {
		set_motor(1, pidTurn);
		set_motor(2, pidTurn);
	}
}


int main (){
	init();
	
	
	
	int thresh = 50;
	int high = 0;
	int low = 10000;
	
	
	populate();
	
	display_picture(3,0);
	
	for (int i = 0; i < 64; i++){
		if(row[i]>high){high = row[i];}
		if(row[i]<low){low = row[i];}
		
	}
	thresh = (high-low)/2;
	
	for(int j = 0; j < 200; j++){
		populate();
		//for (int i = 0; i < samples; i++){
		//	if(row[i]<thresh){printf("0");}
		//	if(row[i]>thresh){printf("1");}
		//	
		//}
		
		error = calcError();
		//Scale error to fit into motor
		turn(error);
		printf("%f\n", error);
		
		sleep1(0,100);
	}
	
	return 0;}
	
