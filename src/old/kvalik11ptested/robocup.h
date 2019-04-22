#include "eyebot.h"
#include <stdlib.h>

int camera;  /* camera version */

image camimage1, camimage2; 
image diffimage;



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

void initCamera()
{
	camera = CAMInit(NORMAL);
	if(camera == NOCAM) {
		error("No camera!\n");
	} else if(camera == INITERROR) {
		error("CAMInit!\n");
	}
}

int lysport(int vent, int antpx)
{
	OSWait(vent);
	CAMGetFrame(&camimage1);	// Ta bilde 1
	LCDPutGraphic(&camimage1);
	
	OSWait(vent);				// Vent 
	CAMGetFrame(&camimage2);	// Ta bilde 2
	LCDPutGraphic(&camimage2);
	
	OSWait(vent);
	IPDiffer(&camimage1, &camimage2, &diffimage);
	LCDPutGraphic(&diffimage);
	
	int px;
	px = pixelCount((unsigned char*) diffimage, 100);
	LCDPrintf("Px: %d", px);
	
	if (px > antpx)	// lyser
	{
		AUTone(1200, 100);
		OSWait(11);
		AUTone(1100, 100);
		OSWait(11);
		return 1;
	} else			// lyser ikke
	{
		AUTone(1000, 100);
		OSWait(11);
		return 0;
	}
}
