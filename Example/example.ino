#include <TB6560_Stepper.h>

#define EN 3   //pin Enable
#define CW 4   //pin CW
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution

Stepper myStep(stepsPerRevolution,EN,CW);

int stepCount = 0;         // number of steps the motor has taken

void setup(){
	myStep.setSpeed(50);
	Serial.begin(9600);
}

void loop(){
	// step one step:
	myStepper.step(1);
	Serial.print("steps:");
	Serial.println(stepCount);
	stepCount++;
	delay(500);
}