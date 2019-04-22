#include "eyebot.h"
#include <stdlib.h>

/** print error message and exit */
void error(char *str) {
	LCDPrintf("ERROR: %s\n",str);
	OSWait(200);
	exit(0);
}

int pixelCount(unsigned char bilde[], int terskel)
{
	int i, count;
	count=0;
	for (i=0; i<82*62; i++)
	{
		if (bilde[i] < terskel)
			count++;
	}
	return count;
}
