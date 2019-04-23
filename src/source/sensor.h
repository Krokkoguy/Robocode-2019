#include "eyebot.h"
#include <stdlib.h>
#include <stdio.h>

struct Chunk{
  /* The width of a chunk */
  unsigned short width;

  /* The midpoint of the chunk in relation to the array it was found in. */
  float direction;
};

/* Reads the output of a sensor array and calculates a value to use when turning.
 * Reduces the output of the sensors to a usable number.
 * Ignores false positives.
 */
struct Chunk detectLargestChunk( int arr[], const int SIZE, const int CONDITION ){

  int index = 0;
  int width = 0;

  int maxIndex = 0;
  int maxWidth = 0;

  /* Iterate over sensorArr to find the largest consecutive chunks of positive readings */
  for( int i = 0; i < SIZE; i++ ){

    if( arr[i] == CONDITION  ){
      /* If the width is 0, start a new chunk */
      if( width == 0 ){
        index = i;
      }

      ++width;

      if ( width > maxWidth ){
        maxIndex = index;
        maxWidth = width;
      }
    }
    else{
      width = 0;
    }
  }

  float direction = maxWidth == 0 ? 0.0 : (maxIndex + (maxWidth/2.0) - (SIZE/2.0)) / (float)SIZE;

  return (struct Chunk){maxWidth, direction};
}

/* Calculates the position of the largest chunks relative to the center of an image. */
/*float calcTurnFromImage( image img, const int CONDITION ){
	int count = 0;
  float sum = 0;
	for (int i = 0; i < 3; i++)
	{
    sum += detectLargestChunk( img[i], 60, CONDITION ).direction;
	}
  return sum / 3;
}*/
