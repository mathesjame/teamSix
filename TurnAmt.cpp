#include <stdio.h>
#include <time.h>
#include "E101.h"

int samples = 64;
char row[64];



//Takes a picture and fills an array of values with a spaced 
//row of pixels across that image.
int populate(){
	take_picture();
	//display_picture(5,0);
	for (int i = 0; i < samples; i++){
		row[i] = get_pixel(100, i*(320/samples), 3);
		
	}
	return 0;
}



//Calculates the Error value for stage 2/3
float calcError(){
	
	float newError = 0;
	
	for(int i = 0; i < samples; i++){
		newError = newError + (i-(samples/2))*row[i];
		
	}
	
	
	
return newError;}



int main (){
	init();
	
	
	
	int thresh = 50;
	int high = 0;
	int low = 10000;
	float error = 0;
	
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
		
		printf("%f\n", error);
		
		sleep1(1,0);
	}
	
	return 0;}
	
