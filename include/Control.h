#include "main.h"
#include "math.h"


//clc variables
	int l;
	int r;
	int lt;
	int rt;
	int lError;
	int rError;
	int lo;
	int ro;

	double lp;
	double li;
	double ld;

	double rp;
	double ri;
	double rd;

	int time=0;
	int prevTime;
	int dt;

	int plError;
	int prError;

	double pk = .1;
	double ik = 0.00001;
	double dk = 0.03;
//numbers from calibration go here
	int lS=1830;
	int rS=1777;
	float sl=1025.2761;
	float sr=1046.284;

  double Length=32;//front/back wheel distance cm
	double hWidth=12;//half the distance between front wheels cm

  //homing variables
  	int lL;
  	int rL;
  	int lR;
  	int rR;


void turnHoming(){
  //homing function instructions:
  //press 8 down then
  //manualy turn both front wheels LEFT, then press 8 LEFT
  //do the same but right then pres 8 RIGHT
  //then point both wheels forward press 8 up
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


void motorControl(double turnJ, int motr){

//my attempt to get slow moving to work
//better, applies when the joystick is < 30
  if((motr*motr)<900){
    if (millis()%2==0){}
    else{motr=motr*2.5;}
  }
//sets motor speed
  motorSet(2,-1*motr);
  motorSet(9,-1*motr);
//akerman steering
  turnJ*=-1;
	if (turnJ< -127){turnJ= 127;}
	if (turnJ> 127){turnJ= 127;}
  if (turnJ==0){turnJ=.1;}
  turnJ=Length/tan(turnJ/150.0);
  lt = sl*atan(Length/(turnJ-hWidth))+lS;
  rt = sr*atan(Length/(turnJ+hWidth))+rS;
//clc section
  l = analogRead(1);
  r = analogRead(2);
	lError = lt-l;
	rError = rt-r;
	prevTime=time;
	time=millis();
	dt=time-prevTime;

//Proportional
	lp=lError*pk;
	rp=rError*pk;
//Integral
	li=li+(ik*lError*dt);
	ri=ri+(ik*rError*dt);
//Derivitive
	ld=dk*((lError-plError)/dt);
	rd=dk*((rError-prError)/dt);


	lo=lp+li+ld;
	ro=rp+ri+rd;
	motorSet(1, lo);
	motorSet(10,ro);

	plError=lError;
	prError=rError;
}
