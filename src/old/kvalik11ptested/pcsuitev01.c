#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "eyebot.h"

#define BASE_SERIAL SERIAL2

char command[10];

image    greyimage, sendimage, differimage;
int      camera;

void performCommand();
void sendImageOverSerial(unsigned char data[], int sizeX, int sizeY);
void getColorTone(unsigned char src[],unsigned char dest[], int sizeX, int sizeY, int tone);
//void copyImage(image* src, image* dest);
void copyImage(unsigned char dest[],unsigned char src[]);
void takeSmallImage();

void error(char *str) {
	LCDPrintf("ERROR: %s\n",str);
	OSWait(200);
	exit(0);
}


int main() {

	char c;
	//char highResImage[176*144*3];
	int index = 0;

	camera = CAMInit(NORMAL);
	if(camera == NOCAM) {
		error("No camera!\n");
	} else if(camera == INITERROR) {
		error("CAMInit!\n");
	}

	OSInitRS232(SER115200, NONE, BASE_SERIAL);

	LCDPrintf(".\r\n");


	while(1)
	{
		if(OSRecvRS232(&c, BASE_SERIAL) == 0)
		{
			c = (char)tolower(c);

			if (c == '.')	// new command
				index = 0;
			else
			{
				command[index] = c;
				index++;
			}

			//LCDPrintf("%c",c);

			if (c == '#')	// command received
			{
				performCommand();
			}

			if (index > 9)
				index = 0;
		}

	}

	return 0;

}

void performCommand()
{
	

	LCDPrintf("\r\n");
	switch(command[0])
	{
		case 'c':	// camera

			if (command[1] == 's')			// small image
			{
				takeSmallImage();

				if (command[4] == 'd')		// differ
				{
					OSWait((int)(command[5]*10));
					//copyImage(&sendimage,&differimage);
					copyImage((unsigned char*)sendimage,(unsigned char*)differimage);
					
					takeSmallImage();
					copyImage((unsigned char*)sendimage,(unsigned char*)greyimage);
					IPDiffer(&greyimage, &differimage, &sendimage);
				}

				// Print to screen
				LCDPutGraphic(&sendimage);
				
				// Send image over serial
				sendImageOverSerial((unsigned char*)sendimage, 82, 62);
				
				
			}
			/*
			else
			{	// large image
				CAMGetFrameRGB(highResImage)
				IPColor2Grey (highResImage, greyimg);
			}
			*/

			break;
	}

}


void sendImageOverSerial(unsigned char data[], int sizeX, int sizeY)
{
	int x, y;
	for(y=0; y<sizeY; y++) {
		for(x=0; x<sizeX; x++) {
			OSSendCharRS232(data[y*sizeX+x], BASE_SERIAL);
			//LCDPrintf("%c",data[y*sizeX+x]);
		}
	}
}

void getColorTone(unsigned char src[], unsigned char dest[], int sizeX, int sizeY, int tone)
{
	int x, y;
	for(y=0; y<sizeY; y++) {
		for(x=0; x<sizeX; x++) {
			dest[y*sizeX+x] = src[y*sizeX*3+x*3+tone];
		}
	}
}

void copyImage(unsigned char dest[], unsigned char src[])
{
	int y;
	for(y=0; y<82*62; y++) {
		dest[y] = src[y];
	}
}

void takeSmallImage()
{
	colimage colimg;
	
	// Select color tone
	if (command[2] == 'r')		// red
	{
		CAMGetColFrame(&colimg,FALSE);
		getColorTone((unsigned char*)colimg,(unsigned char*)greyimage,82, 62, 0);
	}
	else if (command[2] == 'g')	// green
	{
		CAMGetColFrame(&colimg,FALSE);
		getColorTone((unsigned char*)colimg,(unsigned char*)greyimage,82, 62, 1);
	}
	else if (command[2] == 'b')	// blue
	{
		CAMGetColFrame(&colimg,FALSE);
		getColorTone((unsigned char*)colimg,(unsigned char*)greyimage,82, 62, 2);
	}
	else						// grey
	{
		CAMGetFrame(&greyimage);
	}
	
	// Select image processing action
	if (command[3] == 'l') 				// laplace
		IPLaplace(&greyimage, &sendimage);
	else if (command[3] == 's')			// sobel
		IPSobel(&greyimage, &sendimage);
	else if (command[3] == 'd')			// dither
		IPDither(&greyimage, &sendimage);
	else
		copyImage((unsigned char*)sendimage,(unsigned char*)greyimage);
}
