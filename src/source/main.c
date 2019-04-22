#include "../headers/main.h"
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
  reading.direction = (maxIndex + (maxWidth/2.0)) - (SENSOR_SIZE/2.0);

  return reading;
}
