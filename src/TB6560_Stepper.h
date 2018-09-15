#ifndef TB6560_Stepper
#define TB6560_Stepper

// library interface description
class Stepper{
public:
	Stepper(int number_of_steps, int pin_EN, int pin_CW);

	// speed setter method:
	void setSpeed(long whatSpeed);

	// mover method:
	void step(int steps_to_move);
};

#endif
