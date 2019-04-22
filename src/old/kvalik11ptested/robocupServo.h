#define SERVO_KLO SERVO9	// 130 -åpen, 80 - lukket
#define SERVO_ARM SERVO10	// 0 - opp, 255 -nede
#define SERVO_CAM SERVO11	// 0 - opp, 255 -nede

ServoHandle servoKlo;
ServoHandle servoArm;
ServoHandle servoCam;

void kloOpen();
void kloClose();
void armUp();
void armDown();
void camUp();
void camDown();

int armUP;

void initServo()
{
	servoKlo = SERVOInit(SERVO_KLO);
	servoArm = SERVOInit(SERVO_ARM);
	servoCam = SERVOInit(SERVO_CAM);
	
	kloOpen();
	camUp();
}

void releaseServo()
{
	SERVORelease(servoKlo | servoArm | servoCam);
}

void kloOpen()
{
	SERVOSet(servoKlo, 130);
}

void kloClose()
{
	SERVOSet(servoKlo, 70);
}

void armDown()
{
	if (!armUP)
		return;
		
	armUP = 0;
	camDown();
	int i;
	for (i=10; i<255;i++) 
	{
		SERVOSet(servoArm, i);
		OSWait(1);
	}

}

void armUp()
{
	if (armUP)
		return;
	
	armUP = 1;
	int i;
	for (i=255; i>10;i--) 
	{
		SERVOSet(servoArm, i);
		OSWait(1);
	}
}

void camDown()
{
	SERVOSet(servoCam, 255);
}

void camUp()
{
	armUp();
	SERVOSet(servoCam, 0);
}
