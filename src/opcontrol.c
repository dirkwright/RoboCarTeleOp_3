

#include "main.h"
#include "math.h"
//Mr Wright was here :)
//test Aidan
//test Ayush
//test Diego1
//test Joaquin
void operatorControl() {


//clc variables
	int l;
	int r;
	int lt;
	int rt;
//homing variables
	int lL;
	int rL;
	int lR;
	int rR;

	//numbers from calibration go here
	int lS=1830;
	int rS=1777;
	float sl=1025.2761;
	float sr=1046.284;

	double Length=32;//front/back wheel distance cm
	double hWidth=12;//half the distance between front wheels cm
	//(should work the same if both are same unit)
	double turnJ;

	int motr;
	while (1) {
//homing function instructions:
//press 8 down then
//manualy turn both front wheels LEFT, then press 8 LEFT
//do the same but right then pres 8 RIGHT
//then point both wheels forward press 8 up

		if (joystickGetDigital(1, 8, JOY_DOWN)){
			motorStopAll();
			while(!joystickGetDigital(1, 8, JOY_LEFT)){}
			lL=analogRead(1);
			rL=analogRead(2);
			while(!joystickGetDigital(1, 8, JOY_RIGHT)){}
			lR=analogRead(1);
			rR=analogRead(2);
			while(!joystickGetDigital(1, 8, JOY_UP)){}
			lS=analogRead(1);
			rS=analogRead(2);
			printf("LEFT Calibrate:%d , ", lL);
			printf("%d\n", rL);
			printf("RIGHT Calibrate:%d , ", lR);
			printf("%d\n", rR);
			printf("Front Calibrate(lS,rS):%d , ", lS);
			printf("%d\n", rS);
			sl=(((lL-lS)+(lS-lR))/2.0)/(M_PI/2);
			sr=(((rL-rS)+(rS-rR))/2.0)/(M_PI/2);
			printf("scale Calibrate(sl,sr):%f , ", sl);
			printf("%f\n", sr);
			delay(2000);
		}
		motr =joystickGetAnalog(1,3);
//my attempt to get slow moving to work
//better, applies when the joystick is < 30
		if((motr*motr)<900){
			if (millis()%2==0){motr=motr*.3;}
			else{motr=motr*2;}
		}
//sets motor speed
		motorSet(2,-1*motr);
		motorSet(9,-1*motr);
//akerman steering
		turnJ= -1*joystickGetAnalog(1, 1);
		if (turnJ==0){turnJ=.1;}
		turnJ=Length/tan(turnJ/150.0);
		lt = sl*atan(Length/(turnJ-hWidth))+lS;
		rt = sr*atan(Length/(turnJ+hWidth))+rS;
//clc section
		l = analogRead(1);
		r = analogRead(2);
			if (abs(l-lt) > 500){
				motorSet(1, -.1*(l-lt));
			}
			else if (abs(l-lt) < 50){
				motorSet(1, -.1*(l-lt));
			}
			else{
			motorSet(1, -.05*(l-lt));
			}
			if (abs(r-rt) > 500){
				motorSet(10, -.1*(r-rt));
			}
			else if (abs(r-rt) < 50){
				motorSet(10, -.1*(r-rt));
			}
			else{
			motorSet(10, -.05*(r-rt));
		}
	}
}
