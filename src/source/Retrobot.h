#define SERVO_LEFT SERVO11
#define SERVO_RIGHT SERVO12
#define SERVO_ARM SERVO7
#define SERVO_KLO SERVO8
#define AVERAGE 5
#define LEFT 4
#define RIGHT 3
#define FRONT 2
ServoHandle servoLeft;
ServoHandle servoRight;
ServoHandle servoKlo;
ServoHandle servoArm;
int armUP;
QuadHandle encLeft, encRight;
float robotSpeed, robotTurn;
int evl, evr;
int tick;
int activeIR=0;
int binlys[8];

int getDistance(int irID)
{
	return (int)OSGetAD(irID);
}

void resetEncoders()
{
	QUADReset(encLeft);
	QUADReset(encRight);
	evl = 0;
	evr = 0;
}

void initMotor()
{
	servoLeft = SERVOInit(SERVO_LEFT);
	servoRight = SERVOInit(SERVO_RIGHT);
	SERVOSet(servoLeft, 128);
	SERVOSet(servoRight, 128);
	robotSpeed = 0.0f;
	robotTurn = 0.0f;
	encLeft = QUADInit(QUAD_LEFT);
	encRight = QUADInit(QUAD_RIGHT);
	tick = 0;
	resetEncoders();
}

void releaseMotor()
{
	SERVORelease(servoLeft | servoRight);
	QUADRelease(encLeft | encRight);
}

int getEncoder(int encID)
{
	evr = QUADRead(encRight);
	evl = QUADRead(encLeft);

	if (encID == LEFT)
		return evl;
	else if (encID == AVERAGE)
		return ((evl+evr) / 2);
	else
		return evr;
}

void stop()
{
	SERVOSet(servoLeft, 127);
	SERVOSet(servoRight, 127);
	robotSpeed = 0.0f;
	robotTurn = 0.0f;
}

void driveRaw(float speed, float turn)
{
	float leftSpeed, rightSpeed;
	leftSpeed = speed + turn;
	rightSpeed = speed - turn;
	//Clamp to [-1,+1]
	leftSpeed  = leftSpeed  >  1.0f ?  1.0f : leftSpeed;
	leftSpeed  = leftSpeed  < -1.0f ? -1.0f : leftSpeed;
	rightSpeed = rightSpeed >  1.0f ?  1.0f : rightSpeed;
	rightSpeed = rightSpeed < -1.0f ? -1.0f : rightSpeed;
	SERVOSet(servoLeft, 128+(int)(127.0f*leftSpeed));
	SERVOSet(servoRight, 128+(int)(127.0f*rightSpeed));
}

void dig2bin(int dig)
{
	for( int i = 0; i < 8; i++ ){
		binlys[i] = (dig >> i) & 0x01;
	}
}

void readIRLine()
{
	BYTE digin;
	digin = OSReadInLatch(0);
	dig2bin(digin);
}

int followLineLoop(float defspeed)
{
	readIRLine();
	robotSpeed = defspeed;
	robotTurn = 0;
	if (!binlys[1] && !binlys[2])
		robotTurn = 0.1; //0.06
	else if (!binlys[6] && !binlys[5])
		robotTurn = -0.1;
	else if (!binlys[2] && !binlys[3])
		robotTurn = 0.05; //0.04
	else if (!binlys[4] && !binlys[5])
		robotTurn = -0.05;
	else if (!binlys[3] && !binlys[4])
		robotTurn = 0.0;
	else if (!binlys[3])
		robotTurn = 0.0;
	else if (!binlys[4])
		robotTurn = 0.0;
	else if (!binlys[2])
		robotTurn = 0.05;
	else if (!binlys[5])
		robotTurn = -0.05;
	else if (!binlys[1])
		robotTurn = 0.15; //0.1
	else if (!binlys[6])
		robotTurn = -0.15;
	else
	{
		if (tick < 5)
		{
			robotTurn = 0.0; //0.1
			OSWait(35);
			tick++;
		}
		else
			return 0;
	}

	driveRaw(robotSpeed, robotTurn);
	return 1;
}


void kloOpen();
void kloClose();
void armUp();
void armDown();

void initServo()
{
	//servoKlo = SERVOInit(SERVO_KLO);
	servoArm = SERVOInit(SERVO_ARM);
	armUP = 1;
	//kloOpen();
}

void releaseServo()
{
	SERVORelease(servoArm);
}

void kloOpen()
{
	SERVOSet(servoKlo, 200);
}

void kloClose()
{
	SERVOSet(servoKlo, 70);
}

void armUp()
{
	if (armUP)
		return;

	armUP = 1;
	int i;
	for (i=0; i<255;i++)
	{
		SERVOSet(servoArm, i);
		OSWait(1);
	}

}

void armDown()
{
	if (!armUP)
		return;

	armUP = 0;
	int i;
	for (i=255; i>0;i--)
	{
		SERVOSet(servoArm, i);
		OSWait(1);
	}
}
