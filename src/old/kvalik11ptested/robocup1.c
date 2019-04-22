#include "eyebot.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "robocupCamera.h"
#include "robocupIO.h"
#include "robocupSerial.h"
#include "robocupDrive.h"
#include "robocupServo.h"
#include "robocupTasks2.h"

int main(){


	initCamera();
	
	initSerial();
	
	initMotor();
	
	initServo();
	
	char c;
	
	LCDPrintf("."); // started sign
	
	while(1) 
	{
		if(OSRecvRS232(&c, BASE_SERIAL) == 0) 
		{
			switch(tolower(c)) 
			{
				case 'r':
					turn(RIGHT, 3400);
					break;
			
				case 'e':
					turn(LEFT, 4400);
					break;
			
				case 'f':
					opprampe();
					break;
					
			
				case 'g':
					tilrampeball();
					break;
					
				case 'h':
					ryggSluttKjegle(2600);
					LCDPrintf("\r\nENC: %d", ((evl+evr)/2));
				
					rygg(1300);
					turn(RIGHT, 2500);
					break;
			
				case '8':
					
					taskLysport3();
					
					break;
					
				case '9':
					lysport(150, 1200);
					break;
					
				case '0':
					gylotin();
					break;
					
				case '.':
					opprampe2();
					break;
					
				case ',':
					opptrapp();
					break;
				
				case 'm':
					tospeedgulport();
	
					driveToLine(5000);
					
					fram(500);
					turn(RIGHT, 3400);
					
					kjegler4();
	
					break;
				
				case 'i':
					//gylotin();
					//opprampe();
					nedrampe();
					toBane2();
					taskLysport3();
					
					break;
					
				case 'u':
					driveFollowLineTicksFast(170000);
					LCDPrintf("\r\nENC: %d", ((evl+evr)/2));
					//driveFollowLineTicksFast(200000);
					//LCDPrintf("\r\nENC: %d", ((evl+evr)/2));
					//driveFollowLineTicksFast(110000);
					//LCDPrintf("\r\nENC: %d", ((evl+evr)/2));

					driveToTKryss(0, 50000);
					fram(500);
					turn(RIGHT, 3600);
					driveFollowLineTicksFast(100000);
					LCDPrintf("\r\nENC: %d", ((evl+evr)/2));
					
					// Stopper når bane2 slutter
					
					
					//driveToLine(5000);
					//fram(500);
					//turn(RIGHT, 3600);
				
					break;
					
				
					
				case 'v':
					CAMGetFrame(&camimage1);	// Ta bilde 1
					LCDPutGraphic(&camimage1);
					break;
					
				case 'n':
					lysport(50, 1200);
					break;

				case 'y':
					driveToTKryss(LEFT, 50000);
					break;
				case 't':
					toBane2();
					break;

				case '7':
					driveFollowLineTicks(10000);
					followLineToBallFront(5500);
					break;

				case 'w':
					robotSpeed += 0.1f;
					driveRaw(robotSpeed, robotTurn);
					break;
				case 's':
					robotSpeed -= 0.1f;
					driveRaw(robotSpeed, robotTurn);
					break;
				case 'a':
					robotTurn -= 0.1f;
					driveRaw(robotSpeed, robotTurn);
					break;
				case 'd':
					robotTurn += 0.1f;
					driveRaw(robotSpeed, robotTurn);
					break;
				case 'q':
					stop();
					break;
				
				case 'x':
					LCDClear();
					LCDPrintf("F: %0d", getDistance(FRONT));
					break;
				case 'z':
					LCDClear();
					LCDPrintf("L: %d", getDistance(LEFT));
					break;
				case 'c':
					LCDClear();
					LCDPrintf("R: %d", getDistance(RIGHT));
					break;
				
				
					
				case '1':
					kloOpen();
					break;
				case '2':
					kloClose();
					break;
				case '3':
					armUp();
					break;
				case '4':
					armDown();
					break;
				case '5':
					camUp();
					break;
				case '6':
					camDown();
					break;
					
				case 'p':
					driveFollowLineTicks(30000);
					break;
					
					
				case 'o':
					driveFollowLinePort(15000, RIGHT);
					break;
					
				case 'l':
					driveFollowLinePort(15000, LEFT);
					break;
			}
		}
		OSWait(1);
		readIRLine();
		
		
	}
	
	releaseMotor();
	
	return 0;
}

