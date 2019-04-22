#include "robocupCamera.h"
#include "robocupDrive.h"

#include <stdio.h>
#include <ctype.h>

int      camera;  /* camera version */



//void sendImageOverSerial(unsigned char data[], int sizeX, int sizeY, int bitsPerPixel);





int main(){


//	OSInitRS232(SER115200, NONE, SERIAL2);

	
	initCamera();
	
	lysport(200, 200);
	
	OSWait(200);
	
	return 0;
}



/*
void sendImageOverSerial(unsigned char data[], int sizeX, int sizeY, int bitsPerPixel) 
{
	int x, y;
	for(y=0; y<sizeY; y++) {
		for(x=0; x<sizeX; x++) {
			OSSendCharRS232(data[y*sizeX*3+x*3], SERIAL2);
		}
	}
}*/
