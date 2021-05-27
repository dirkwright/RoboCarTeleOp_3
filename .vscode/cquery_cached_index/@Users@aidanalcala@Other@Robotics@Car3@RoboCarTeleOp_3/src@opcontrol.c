

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
	int preRange;
	int range2;
	int preRange2;


	int motr;
	double turnJ;

	while (1) {

		range2=ultrasonicGet(oiseMaker2);

		digitalWrite(1, true);
		digitalWrite(2, range2>10);
		digitalWrite(3, false);


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
			if (range < 0){range=preRange;}
			if (range>20){motr=((range+80)/5);}else{motr=20;}
			if (range < 100){turnJ= 1.1*(range-128);}
			else{turnJ=0;}
			motorControl(turnJ,motr);
			preRange=range;
		}
	}
}
