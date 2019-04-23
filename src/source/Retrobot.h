#define SERVO_LEFT SERVO11
#define SERVO_RIGHT SERVO12
#define AVERAGE 5
#define LEFT 4
#define RIGHT 3
#define FRONT 2
ServoHandle servoLeft;
ServoHandle servoRight;

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

void dig2bin( int dig ) {
	int i;
  for ( i = 0; (dig > 0) && (i < 8); i++ ){
    binlys[i] = dig & 0x01;
    dig >>= 1;
  }
}

void readIRLine() {
	dig2bin( OSReadInLatch(0) );
}

int followLineLoop( float defspeed ){
	readIRLine();
	robotSpeed = defspeed;
	robotTurn = 0.0f;

	struct Chunk chunk = detectLargestChunk(binlys, 8, 0);
  robotTurn = -chunk.direction;

	if ( chunk.width > 0 ) tick = 0;
	else if ( tick < 5 ) {
			OSWait(30);
			tick++;
	}
	else return 0;

	driveRaw(robotSpeed, robotTurn);
	return 1;
}
