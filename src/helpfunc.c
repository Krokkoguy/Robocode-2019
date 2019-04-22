// f�lg linje og stopp p� enkoder
// f�lg linje og stopp p� tid
// f�lg linje og stopp p� port
// f�lg linje og stopp p� kryss

#define SENSOR_SIZE 8
#define SENSOR_POSITIVE 0

struct SensorRead{
  unsigned short width;
  float direction;
}

/* Reads the output of a sensor array and calculates a value to use when turning.
 * Reduces the output of the sensors to a usable number.
 * Ignores false positives.
 */
struct SensorRead sensorRead( int sensorArr[SENSOR_SIZE] ){

  struct sensorRead reading;

  int index = 0;
  int width = 0;

  int maxIndex = index;
  int maxWidth = width;

  /* Iterate over sensorArr to find the largest consecutive chunks of positive readings */
  for( int i = 0; i < SENSOR_SIZE; i++ ){

    if( sensorArr[i] == SENSOR_POSITIVE ){

      if( width == 0 ){
        index = i;
      }

      ++width;
    }
    else if ( width > maxWidth ){
      maxIndex = index;
      maxWidth = width;
    }
    else{
      count = 0;
    }
  }

  reading.width = maxWidth;
  reading.direction = maxWidth == 0 ? (maxIndex + (maxWidth/2.0)) - (SENSOR_SIZE/2.0) : 0.0;

  return reading;
}

void DriveOnEncoder(int tics)
{
	Stop();
	ResetEncoder();

	SERVOSet(servoLeft, spd1);
	SERVOSet(servoRight, spd1);

	while (GetEncoder(AVERAGE) < tics)
	{
		OSSleep(1);
	}

	Stop();
	return;
}

void FollowLineOnEncoder(int tics, int lr)
{
	Stop();
	ResetEncoder();

	while (GetEncoder(AVERAGE) < tics)
	{
		FollowLine(lr);
		OSSleep(1);
	}

	Stop();
	return;
}

void DriveOnTime(int time)
{
	int counter = 0;
	Stop();

	SERVOSet(servoLeft, spd1)
	SERVOSet(servoRight, spd1);

	while (counter < time)
	{
		counter++;
		OSSleep(1);
	}

	Stop();
	return;
}

void FollowLineOnTime(int time, int lr)
{
	int counter = 0;
	Stop();
	ResetEncoder(1);

	while (counter < time)
	{
		FollowLine(lr);
		counter++;
		OSSleep(1);
	}

	Stop();
	return;
}
