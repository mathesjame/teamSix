#include <stdio.h>
#include <time.h>
#include "E101.h"

int samples = 64;
char row[64];
int oldError = 0;
float error = 0;
int thresh = 100;
int arraySum = 0;
int doReverse = 0;
int passedThree = 0;
int seesCross = 0;
int quad4 = 0;

double kP = 0.007;

int turnTime = 500000;
int turnThresh = 55;
int turnSpeed = -100;

double errorScale = 0.02;//Set to 0.02
int baseMotorSpeed = -80;//Set to -80

int leftMotor = 0;
int rightMotor = 0;

char serverNum[15] = {0};

int populate(){
	take_picture();
	//display_picture(5,0);
	for (int i = 0; i < samples; i++){
		row[i] = get_pixel(100, i*(320/samples), 3);

	}

	//Convert To 1s and 0s
	for (int i = 0; i < samples; i++){
		if(row[i]<thresh){row[i]=0;}
		if(row[i]>=thresh){row[i]=1;}
	}
	printf("\n");
	arraySum = 0;
	for (int i = 0; i < samples; i++){
		arraySum = arraySum+row[i];
	}
        printf("%d\n", arraySum);
	if(arraySum<2){
		doReverse = 1;
	}
	if(arraySum>turnThresh){
		if(passedThree == 1){seesCross = 1;}//Will only set seesCross after seeing the entry to Q3.
		passedThree = 1;
		sleep1(0,100000);
	}
	
	double red = 0;
	double blue = 0;
	double green = 0;
	
	for (int i = 0; i < samples/16; i++){
		red = red + get_pixel(100, 159 + (i * 4), 0);
		blue = blue + get_pixel(100, 159 + (i * 4), 1);
		green = green + get_pixel(100, 159 + (i * 4), 2);
		
	}
	
	red = red / 4;
	blue = blue / 4;
	green = green / 4;
	
	if ((red > 50) && (blue < 50) && (green < 50)){
		quad4 = 1;
	}
	
	return 0;
}

float errCalc(){
	float newErrorP = 0;
	oldError = error;

	for(int i = 0; i < samples; i++){
		newErrorP = newErrorP + (i-(samples/2))*row[i]*254*kP;

	}


	float newErrorD = 0;

	newErrorD = (newErrorP-oldError)/10;
	//calculate I

	float newErrorI = 0;

	//calculate I


	float newError = newErrorP;// + newErrorI + newErrorD;

return newError;}

int turn(double pidTurn){
	rightMotor = (int)(-1*(baseMotorSpeed + (pidTurn)*10));
	leftMotor = (int)(1*(baseMotorSpeed - (pidTurn)*10));
	if(leftMotor > 254){leftMotor = 253;}
	if(leftMotor < -254){leftMotor = -253;}
	if(rightMotor > 254){rightMotor = 253;}
	if(rightMotor < -254){rightMotor = -253;}



	set_motor(1, leftMotor);
	//printf("%d\n", leftMotor);
	set_motor(2, rightMotor);

	return 0;
}


int main (){
	init();


	sprintf(serverNum, "130.195.6.196");
	connect_to_server(serverNum, 1024);
	char message[24] = {0};
	sprintf(message, "Please And Thanks");
	send_to_server(message);
	receive_from_server(message);
	send_to_server(message);
	printf("%s", message);
	sleep1(0,50000);
	
	
	//Motor 1 - Negative is forward
	//Motor 2 - Positive is forward
	
	
	int high = 0;
	int low = 10000;
	
	
	populate();
	
	display_picture(2,0);
	
	for (int i = 0; i < 64; i++){
		if(row[i]>high){high = row[i];}
		if(row[i]<low){low = row[i];}
		
	}
//	thresh = (high-low)/2;
	
	while(true){
		populate();
		
                if(doReverse == 1){
		    set_motor(1,100);
		    set_motor(2,-100);
		    sleep1(0,200000);
                    printf("no line\n");
		    doReverse = 0;
		}
		if(seesCross == 1){
		    turn(turnSpeed);
		    sleep1(0,turnTime);
                    printf("turning Left\n");
		    seesCross = 0;
		}
		
		error = (int)errCalc()*errorScale;//Check This scale factor
		if(error)
		//Scale error to fit into motor
		//printf("Uncut Error: %f\n", error);
		
		turn(error);
		//set_motor(1,180);
		//printf("%f\n", error);
		
		sleep1(0,10000);
	}
	
	return 0;}
	

