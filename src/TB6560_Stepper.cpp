#include "Arduino.h"
#include "Stepper.h"

Stepper::Stepper(int number_of_steps, int pin_EN, int pin_CW){
	this->step_number = 0;    // which step the motor is on
	this->direction = 0;      // motor direction
	digitalWrite(pin_CW, direction);
	this->last_step_time = 0; // time stamp in us of the last step taken
	this->number_of_steps = number_of_steps; // total number of steps for this motor

	// Arduino pins for the motor control connection:
	this->pin_EN = pin_EN;
	this->pin_CW = pin_CW;

	// setup the pins on the microcontroller:
	pinMode(this->pin_EN, OUTPUT);
	pinMode(this->pin_CW, OUTPUT);

/*
 * Sets the speed in revs per minute
 */

 void Stepper::setSpeed(long whatSpeed){
 	this->step_delay = 60L * 1000L * 1000L / this->number_of_steps / whatSpeed;
 }

 /*
 * Moves the motor steps_to_move steps.  If the number is negative,
 * the motor moves in the reverse direction.
 */

 void Stepper::step(int steps_to_move){
 	int steps_left = abs(steps_to_move);  // how many steps to take

 	// determine direction based on whether steps_to_mode is + or -:
 	if (steps_to_move > 0) { this->direction = 1; }
 	if (steps_to_move < 0) { this->direction = 0; }
 	digitalWrite(pin_CW, direction);

 	// decrement the number of steps, moving one step each time:
 	while (steps_left > 0){
 		unsigned long now = micros();
 		// move only if the appropriate delay has passed:
 		if (now - this->last_step_time >= this->step_delay){
 			// get the timeStamp of when you stepped:
 			this->last_step_time = now;
 			// increment or decrement the step number,
 			// depending on direction:
 			if (this->direction == 1){
 				this->step_number++;
 				if (this->step_number == this->number_of_steps){
 					this->step_number = 0;
 				}
 			}
 			else{
 				if (this->step_number == 0){
 					this->step_number = this->number_of_steps;
 				}
 				this->step_number--;
 			}
 			// decrement the steps left:
 			steps_left--;
 			// step the motor to step number 0, 1, ..., {3 or 10}
 			digitalWrite(pin_EN, HIGH);
 		}
 		else{
 			digitalWrite(pin_EN, LOW);
 		}	
 	}
 }