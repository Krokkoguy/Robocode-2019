#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "eyebot.h"

#define BASE_SERIAL SERIAL2

#define SERVO_LEFT SERVO12
#define SERVO_RIGHT SERVO13

ServoHandle servoLeft;
ServoHandle servoRight;
QuadHandle encLeft, encRight;

void error(char *str) {
	LCDPrintf("ERROR: %s\n",str);
	OSWait(200);
	exit(0);
}

void performCommand();
void sendImageOverSerial(unsigned char data[], int sizeX, int sizeY);
void driveRaw(float speed, float turn);

char command[10];
float robotSpeed, robotTurn;

int main() {

	int camera;
	camera = CAMInit(NORMAL);
	if(camera == NOCAM) {
		error("No camera!\n");
	} else if(camera == INITERROR) {
		error("CAMInit!\n");
	}
	CAMMode(AUTOBRIGHTNESS);

	OSInitRS232(SER115200, NONE, BASE_SERIAL);

	servoLeft = SERVOInit(SERVO_LEFT);
	servoRight = SERVOInit(SERVO_RIGHT);
	driveRaw(0.0f, 0.0f);

	encLeft = QUADInit(QUAD_LEFT);
	encRight = QUADInit(QUAD_RIGHT);
	

	LCDPrintf(".\r\n"); // Started

	char c;
	int index = 0;
	
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
			if (c == '#')	// command finnished
			{
				performCommand();
			}
			if (index > 9)
				index = 0;
		}
	}

	CAMRelease();
	SERVORelease(servoLeft | servoRight);
	QUADRelease(encLeft | encRight);
	
	return 0;
}

void performCommand()
{
	switch(command[0])
	{
		case 'c':	// camera

			if (command[1] == 's')			// small image
			{
				int x, y, sizeX, sizeY;
				sizeX=82;
				sizeY=62;
				colimage colorimage;
				image greyimage, ipimage;
								
				if (command[2] == 'w')		// grey tone
					CAMGetFrame (&greyimage);		
			
				if (command[3] == 'l')		// laplace
					IPLaplace(&greyimage, &ipimage);
				else if (command[3] == 's')	// cobel
					IPSobel(&greyimage, &ipimage);
				else if (command[3] == 'd')	// dither
					IPDither(&greyimage, &ipimage);
				
				if (command[3] == 'n')		// no image processing				
				{
					sendImageOverSerial((unsigned char*)greyimage, sizeX, sizeY);
					LCDPutGraphic(&greyimage);
				}
				else
				{
					sendImageOverSerial((unsigned char*)ipimage, sizeX, sizeY);
					LCDPutGraphic(&ipimage);
				}
			}

			break;
		
		case 'd'	// drive
		
			if (command[2] == 'w')
			{
				robotSpeed += 0.1f;
				driveRaw(robotSpeed, robotTurn);
			}
			else if (command[2] == 's')
			{
				robotSpeed -= 0.1f;
				driveRaw(robotSpeed, robotTurn);
			}
			else if (command[2] == 'a')
			{				
				robotTurn -= 0.1f;
				driveRaw(robotSpeed, robotTurn);
			}
			else if (command[2] == 'd')
			{					
				robotTurn += 0.1f;
				driveRaw(robotSpeed, robotTurn);
			}
			else if (command[2] == 'q')
			{					
				robotTurn = 0.0f;
				robotSpeed = 0.0f;
				driveRaw(robotSpeed, robotTurn);
			}
			break;
	}

}

void sendImageOverSerial(unsigned char data[], int sizeX, int sizeY)
{
	int x, y;
	for(y=0; y<sizeY; y++) {
		for(x=0; x<sizeX; x++) {
			OSSendCharRS232(data[y*sizeX+x], BASE_SERIAL);
		}
	}
}
