#define SERVO_LEFT SERVO11
#define SERVO_RIGHT SERVO12

#define AVERAGE 5
#define LEFT 4
#define RIGHT 3
#define FRONT 2



ServoHandle servoLeft;
ServoHandle servoRight;

QuadHandle encLeft, encRight;

// Encoder differanse, de teller ulikt...
#define WHEELDIFF (5200.0f/5450.0f)

float robotSpeed, robotTurn;
int evl, evr;


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
	
	resetEncoders();
}

void releaseMotor()
{
	SERVORelease(servoLeft | servoRight);
	QUADRelease(encLeft | encRight);
}

int getEncoder(int encID)
{
	evr = (int)((float)(QUADRead(encRight)*WHEELDIFF));
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
	
	OSSleep(50);
	
	return;
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

/*
void stopVedPort(int side, int maxEncTics)
{
	getDistance(side);
	resetEncoders();
	
	while (getEncoder(AVERAGE) < maxEncTics && getEncoder(AVERAGE) > -maxEncTics)
	{
		if (getDistance(side) > 350)
		{
			stop();
			AUTone(1200, 100);
			OSWait(11);
			AUTone(1100, 100);
			OSWait(11);
			break;
		}
	}

	stop();
}

void rygg(int tics)
{
	resetEncoders();

	robotSpeed = -0.2f;
	robotTurn = 0.0f;
	driveRaw(robotSpeed, robotTurn);		
	
	while (getEncoder(AVERAGE) > -tics) {;}
	
	stop();
}

void fram(int tics)
{
	resetEncoders();

	robotSpeed = 0.2f;
	robotTurn = 0.0f;
	driveRaw(robotSpeed, robotTurn);		
	
	while (getEncoder(AVERAGE) < tics) {;}
	
	stop();
}

void framsakte(int tics)
{
	resetEncoders();

	robotSpeed = 0.15f;
	robotTurn = 0.0f;
	driveRaw(robotSpeed, robotTurn);		
	
	while (getEncoder(AVERAGE) < tics) {;}
	
	stop();
}

void framSluttKjegle(int tics)
{
	resetEncoders();

	robotSpeed = 0.15f;
	robotTurn = 0.0f;
	driveRaw(robotSpeed, robotTurn);		
	
	while (getEncoder(AVERAGE) < tics && getDistance(LEFT) > 150) {;}
	
	stop();
}

void ryggSluttKjegle(int tics)
{
	resetEncoders();

	robotSpeed = -0.15f;
	robotTurn = 0.0f;
	driveRaw(robotSpeed, robotTurn);		
	
	while (getEncoder(AVERAGE) > -tics && getDistance(RIGHT) > 150) {;}
	
	stop();
}

// Antall tics vil være avhengig av underlag! 
// og antall grader det skal svinges
void turn(int side, int tics)
{
	stop();
	resetEncoders();
	robotSpeed = 0.0;
	if (side == LEFT)
	{
		robotTurn = -0.3f;
		driveRaw(robotSpeed, robotTurn);		
		while (getEncoder(side) > -tics) {;}
	}
	else
	{
		robotTurn = 0.3f;
		driveRaw(robotSpeed, robotTurn);		
		while (getEncoder(side) > -tics) {;}
	}

	
	
	stop();
}

void turnFrontObject(int side, int tics, int objektavstand)
{
	stop();
	robotSpeed = 0.0f;
	resetEncoders();
	char buff[10];
	
	if (side == LEFT)
	{
		robotTurn = -0.2f;
		driveRaw(robotSpeed, robotTurn);		
		while (getEncoder(side) > -tics && getDistance(FRONT) < objektavstand) {;}
		sprintf(buff, "%d\r\n", getDistance(FRONT));
		writeStringToSerial(buff);
	}
	else
	{
		robotTurn = 0.2f;
		driveRaw(robotSpeed, robotTurn);		
		while (getEncoder(side) > -tics && getDistance(FRONT) < objektavstand) {;}
		sprintf(buff, "%d\r\n", getDistance(FRONT));
		writeStringToSerial(buff);
	}
	
	
	
	stop();
}
*/

int binlys[8];
char buf[50];

void dig2bin(int dig)
{
	int i, rest;
	int dele = dig;
	for (i=0;i<8;i++)
		binlys[i] = 0;
	
	i=0;
	while (dele > 0 && i<8)
	{
		rest = dele % 2;
		binlys[i] = rest;
		i++;
		dele = dele / 2;
	}
}


void readIRLine()
{
	BYTE digin;
	digin = OSReadInLatch(0);
	//LCDPrintf("\r\n %d", digin);
	dig2bin(digin);

	//OSWait(10);
	//int i;
	//for (i=7;i>=0;i--)
	//	LCDPrintf("%d", binlys[i]);	
		
	sprintf(buf, "%d%d%d%d%d%d%d%d\r\n", binlys[7], binlys[6], binlys[5], binlys[4], binlys[3], binlys[2], binlys[1], binlys[0]);
	//writeStringToSerial(buf);
}

int followLineLoop(float defspeed)
{
	readIRLine();
	robotSpeed = defspeed;
	robotTurn = 0;
	binlys[0] = 1; // grunnet feil på sensor
	binlys[7] = 1; // grunnet feil på sensor

	if (binlys[0] && binlys[1])
	{
		robotTurn = 0.15; //0.1
		robotSpeed = 0.2; //0.15
	}
	else if (binlys[7] && binlys[6])
	{
		robotTurn = -0.15;
		robotSpeed = 0.2;
	}
	else if (binlys[1] && binlys[2])
		robotTurn = 0.1; //0.06
	else if (binlys[6] && binlys[5])
		robotTurn = -0.1;

	else if (binlys[2] && binlys[3])
		robotTurn = 0.07; //0.04

	else if (binlys[4] && binlys[5])
		robotTurn = -0.07;

	else if (binlys[3] && binlys[4])
		robotTurn = 0.0;

	else if (binlys[3])
		robotTurn = 0.0;
		
	else if (binlys[4])
		robotTurn = 0.0;
		
	else if (binlys[2])
		robotTurn = 0.05;
	
	else if (binlys[5])
		robotTurn = -0.05;
		
	else if (binlys[1] || binlys[0])
	{
		robotTurn = 0.15; //0.1
		robotSpeed = 0.2; //0.15
	}
	else if (binlys[6] || binlys[7])
	{
		robotTurn = -0.15;
		robotSpeed = 0.2;
	}
		

	else 
		return 0;
		
	driveRaw(robotSpeed, robotTurn);
	return 1;
}



void driveFollowLineTicks(int tics)
{
	resetEncoders();
	int i;
	while (getEncoder(AVERAGE) < tics)
	{
		i = followLineLoop(0.2);
		if (!i)
		{
			stop();
			AUTone(1200, 100);
			OSWait(11);
			AUTone(1100, 100);
			OSWait(11);
			break;
		}
	}
	stop();
}



/*
void driveFollowLineTicksFast(int tics)
{
	resetEncoders();
	int i;
	while (getEncoder(AVERAGE) < tics)
	{
		i = followLineLoop(0.3);
		if (!i)
		{
			stop();
			AUTone(1200, 100);
			OSWait(11);
			AUTone(1100, 100);
			OSWait(11);
			break;
		}
	}
	stop();
}

void driveFollowLinePort(int tics, int irID)
{
	resetEncoders();
	int i;
	while (getEncoder(AVERAGE) < tics && getDistance(irID) < 690)
	{
		i = followLineLoop(0.2);
		if (!i)
		{
			stop();
			AUTone(1200, 100);
			OSWait(11);
			AUTone(1100, 100);
			OSWait(11);
			break;
		}
	}
	stop();
}


void driveToLine(int tics)
{
	resetEncoders();
	robotSpeed = 0.2;
	robotTurn = 0;
	driveRaw(robotSpeed, robotTurn);
	
	while (getEncoder(AVERAGE) < tics)
	{
		readIRLine();
		
		if (binlys[3] && binlys[4])
		{
			stop();
			AUTone(1200, 100);
			OSWait(11);
			AUTone(1100, 100);
			OSWait(11);
			break;
		}
	}
	stop();
}

void driveToTKryss(int retning, int tics)
{
	if (retning == LEFT)
		retning = 248;
	else if (retning == RIGHT)
		retning = 15;
	else
		retning = 255;
		
	resetEncoders();
	int i;
	while (getEncoder(AVERAGE) < tics && OSReadInLatch(0) != retning)
	{
		readIRLine();
		i = followLineLoop(0.2);
		if (!i)
		{
			stop();
			AUTone(1200, 100);
			OSWait(11);
			AUTone(1100, 100);
			OSWait(11);
			break;
		}
	}
	stop();
}

void driveFollowLineToTrapp(int tics)
{
	resetEncoders();
	int i;
	while (getEncoder(AVERAGE) < tics && OSReadInLatch(0) != 255)
	{
		readIRLine();
		i = followLineLoop(0.2);
		if (!i)
		{
			stop();
			AUTone(1200, 100);
			OSWait(11);
			AUTone(1100, 100);
			OSWait(11);
			break;
		}
	}
	stop();
}

void driveToVeiskilleLeft(int tics)
{
	resetEncoders();
	int i = 1;
	while (getEncoder(AVERAGE) < tics)
	{
		readIRLine();
		if (!i || ((binlys[0] && binlys[1] && binlys[4]) && !(binlys[3] && binlys[4])))
		{
			stop();
			AUTone(1200, 100);
			OSWait(11);
			AUTone(1100, 100);
			OSWait(11);
			break;
		}
		i = followLineLoop(0.2);
	}
	stop();
}

void driveToomvendtVeiskillerampe(int tics)
{
resetEncoders();
	int i = 1;
	while (getEncoder(AVERAGE) < tics)
	{
		readIRLine();
		if (!i || ((binlys[2] && binlys[3] && binlys[4]) && binlys[5]))
		{
			stop();
			AUTone(1200, 100);
			OSWait(11);
			AUTone(1100, 100);
			OSWait(11);
			break;
		}
		i = followLineLoop(0.2);
	}
	stop();
}

void driveToBallLeft(int tics)
{
	resetEncoders();
	robotSpeed = 0.1;
	robotTurn = 0;
	driveRaw(robotSpeed, robotTurn);
	
	while (getEncoder(AVERAGE) < tics && !(getDistance(LEFT) < 430 && getDistance(LEFT) > 350)) {;}
	stop();

}

void driveToBallFront(int tics)
{
	resetEncoders();
	robotSpeed = 0.15;
	robotTurn = 0;
	driveRaw(robotSpeed, robotTurn);
	int last, i1;
	i1 = getDistance(FRONT);
	last = getDistance(FRONT);
	if (last > i1)
		last = i1;
	while (getEncoder(AVERAGE) < tics && last < 500) 
	{
		i1 = getDistance(FRONT);
		last = getDistance(FRONT);
		if (last > i1)
			last = i1;
		sprintf(buf, "Ball: %d\r\n", last);
		writeStringToSerial(buf);
	}
	stop();
}

void followLineToBallFront(int tics)
{
	resetEncoders();
	driveRaw(robotSpeed, robotTurn);
	int i, last, i1, i2, i3;
	i1 = getDistance(FRONT);
	i2 = getDistance(FRONT);
	i3 = getDistance(FRONT);
	last = (i1+i2+i3)/3;
	i1 = getDistance(FRONT);
	i2 = getDistance(FRONT);
	i3 = getDistance(FRONT);
	if (last > (i1+i2+i3)/3)
		last = (i1+i2+i3)/3;
	while (getEncoder(AVERAGE) < tics && last < 620) 
	{
		i1 = getDistance(FRONT);
		i2 = getDistance(FRONT);
		i3 = getDistance(FRONT);
		last = (i1+i2+i3)/3;
		i1 = getDistance(FRONT);
		i2 = getDistance(FRONT);
		i3 = getDistance(FRONT);
		if (last > (i1+i2+i3)/3)
			last = (i1+i2+i3)/3;
		sprintf(buf, "Ball: %d\r\n", last);
		writeStringToSerial(buf);
		i = followLineLoop(0.1);
		if (!i)
		{
			stop();
			AUTone(1200, 100);
			OSWait(11);
			AUTone(1100, 100);
			OSWait(11);
			break;
		}
	}
	stop();
}
*/
