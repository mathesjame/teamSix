#include <stdio.h>
#include <time.h>
#include "E101.h"

int main(){
  init();
  int inputFront;
  int inputSide;
  int adc_readingFront;
  int adc_readingSide;
  int threshold;
  threshold = 100 // ??- Will have to find this through testing as well
  inputFront = 0;
  inputSide = 0;
  while(true){
    adc_readingFront =read_analog(0); //Not to sure what pins the sensors are will have to check
    adc_readingSide = read_analog(1);
    if(adc_readingFront > threshold){
      set_motor(1, 100);
      set_motor(2, 100);
    }else if((adc_readingSide > threshold) && (adc_readingFront < threshold)){
      set_motor(1, 100);
      set_motor(2, -100);
    }else if((adc_readingSide < threshold) && (adc_readingFront < threshold)){
      set_motor(1, -100);
      set_motor(1, 100);
    }else if((camera reading) && (adc_readingFront < threshold)){ //Will have to either get the camera reading to get here, or create a variable to put in here that holds the camrea reading
			set_motor(1, 0);
			set_motor(2, 0);
			sleep1(0,60000); //Not to sure if this is 6 seconds, will change once known
			set_motor(1, 100);
			set_motor(2, 100);
		}else{
			set_motor(1, 100);
			set_motor(2, 100);
		}
  }
