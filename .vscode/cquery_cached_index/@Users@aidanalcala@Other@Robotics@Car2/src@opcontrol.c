

#include "main.h"
#include "Control.h"



#include "math.h"

//Mr Wright was here :)
//test Aidan
//test Ayush
//test Diego1
//test Joaquin
void operatorControl() {


	int controlMode = 1;

	int range;

	int motr;
	double turnJ;

	while (1) {




		if (joystickGetDigital(1, 8, JOY_DOWN)){turnHoming();}

		if (joystickGetDigital(1, 7, JOY_UP)){//togle modes
			while(joystickGetDigital(1, 7, JOY_UP)){}
			controlMode*=-1;
			motorStopAll();
		}
		if (controlMode == 1){
			turnJ=joystickGetAnalog(1, 1);
			motr =joystickGetAnalog(1, 3);
			motorControl(turnJ,motr);
		}else{
			range=ultrasonicGet(noiseMaker);
			motorControl(range-128,30);
		}
	}
}
