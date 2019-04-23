#include <stdlib.h>

/* Checks if mask is unchanged if applied to n. */
int testMask( int n, int mask ){
	return ( n & mask) == mask;
}

/* Follows a line. */
int driveFollowLine(int ticks, float speed){

  /* Save encoder data to virtually reset the encoder.
   * (actually resettting the encoder will not change how this function performs.) */
	int enc = getEncoder(AVERAGE);

  /* Init the return code */
  int rCode = 1;

	while( rCode && (abs(enc - getEncoder(AVERAGE)) < ticks) ) {
		rCode = followLineLoop( speed );
	}

  if(rCode) LCDPrintf("Stoppet på ticks - dFL\n\r");
  else      LCDPrintf("Mistet strek - dFL\n\r");

  stop();
  return rCode;
}

/* Drives forward. */
void drive( int ticks, float speed, float direction ){

  /* Pick which encoder to check. */
	int d                 = AVERAGE;
	if( d < 0.0f ) d      = LEFT;
	else if( d > 0.0f ) d = RIGHT;

	int enc = getEncoder( d );

  driveRaw( speed, direction );
	while( abs(enc - getEncoder( d )) < ticks );

	LCDPrintf("Stoppet på ticks - d\n\r");

	stop();
}

/* Follows a line until a crossing. */
int driveToCross(int ticks, float speed, int retning ){

  /* Set the mask to find the cross */
  int mask = 0x7e; //01111110
	if (retning == LEFT)
		mask = 0x78;   //01111000
	else if (retning == RIGHT)
		mask = 0x1e;   //00011110

  int enc = getEncoder(AVERAGE);
  int rCode = 1;

	while( rCode && (abs(enc - getEncoder(AVERAGE)) < ticks) && testMask( ~OSReadInLatch(0), mask ) ) {
		rCode = followLineLoop( speed );
	}

  if(rCode) LCDPrintf("Stoppet på ticks - dTC\n\r");
  else      LCDPrintf("Mistet strek - dTC\n\r");

  stop();
  return rCode;
}

/* Drives forward until a line has been found. */
int driveToLine(int ticks, float speed) {

  int enc = getEncoder(AVERAGE);
  int rCode = 0;

  driveRaw( speed, 0 );
	while ( (!rCode) && (abs(enc - getEncoder(AVERAGE)) < ticks) ){
    rCode = testMask( ~OSReadInLatch(0), 0x18 );
	}

  if( rCode ) LCDPrintf("Line detected - dTL\n\r");
  else        LCDPrintf("Stoppet på ticks - dTL\n\r");

	stop();
  return rCode;
}

void turnToDistance(int sensor, int value)
{
	int last = getDistance(sensor);
	LCDPrintf("\r\n%d", last);
	robotTurn = 0.20f;
	robotSpeed = 0.0f;
	driveRaw(robotSpeed, robotTurn);
	while((last < value) || (last > (value + 100)))
	{
		last = getDistance(sensor);
		LCDPrintf("\r\n%d", last);
	}
	stop();
}

void turn( int ticks, float direction ){
  drive( ticks, 0.0f, direction );
}
