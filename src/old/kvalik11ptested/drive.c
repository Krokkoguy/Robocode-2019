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

#define WHEELDIFF (5200.0f/5450.0f)
					
#define TPR_LEFT (40652.0f/40.0f)
#define TPR_RIGHT (43714.0f/40.0f)
#define CM_PER_REV (19.7f)

float robotSpeed, robotTurn;
int evl, evr;
char buf[250];

void driveRaw(float speed, float turn);
void updateEncoderValues();

void writeStringToSerial(char dataString[], int serialPort);
void readStringFromSerial(char dataString[], char startChar, char stopChar, int serialPort);

int main() {

	char c;
	int i;
	
	robotSpeed = 0.0f;
	robotTurn = 0.0f;

	OSInitRS232(SER115200, NONE, BASE_SERIAL);

	servoLeft = SERVOInit(SERVO_LEFT);
	servoRight = SERVOInit(SERVO_RIGHT);
	driveRaw(0.0f, 0.0f);

	encLeft = QUADInit(QUAD_LEFT);
	encRight = QUADInit(QUAD_RIGHT);

	updateEncoderValues();

	while(1) {
		if(OSRecvRS232(&c, BASE_SERIAL) == 0) {
			switch(tolower(c)) {
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
					robotTurn = 0.0f;
					robotSpeed = 0.0f;
					driveRaw(robotSpeed, robotTurn);
					break;
				case 'p':
					for(i=0; i<200; i++) {
						AUTone(65+i*50, 9);
						OSWait(1);
					}
					break;
				case 'r':
					QUADReset(encLeft);
					QUADReset(encRight);
					break;
				case 't':
					QUADReset(encLeft);
					QUADReset(encRight);			
					
					robotTurn = 0.0f;
					robotSpeed = 0.2f;
					driveRaw(robotSpeed, robotTurn);
									
					
					updateEncoderValues();

					
					while ((evl+evr)/2 < 30000)
					{
						
						if ((evr-evl)>100)
						{
							robotTurn = 0.1f;
					
							
						}
						else if ((evl-evr)>100)
						{
							robotTurn = -0.1f;
			
						}
						else
						{
							robotTurn = 0.0f;
							
						}
						
						driveRaw(robotSpeed, robotTurn);
						OSWait(5);
						
						updateEncoderValues();
						//LCDSetPrintf(1,1,"%d",(int)evl);
						//LCDSetPrintf(2,1,"%d",(int)evr);
					}
					
					robotTurn = 0.0f;
					robotSpeed = 0.0f;
					driveRaw(robotSpeed, robotTurn);
					break;
					
				case 'y':
					QUADReset(encLeft);
					QUADReset(encRight);			

					robotTurn = 0.2f;
					robotSpeed = 0.0f;
					driveRaw(robotSpeed, robotTurn);
				
					while ((int)QUADRead(encLeft) < 4600) {;}
					
					robotTurn = 0.0f;
					robotSpeed = 0.0f;
					driveRaw(robotSpeed, robotTurn);
					break;
					
				case 'l':
				
					
					// Rygg
					QUADReset(encLeft);
					QUADReset(encRight);
					robotTurn = 0.0f;
					robotSpeed = -0.2f;
					driveRaw(robotSpeed, robotTurn);							
					while ((evl+evr)/2 > -6000) {updateEncoderValues();}	
					robotTurn = 0.0f;
					robotSpeed = 0.0f;
					driveRaw(robotSpeed, robotTurn);
					OSWait(50);
					
					// sving 90 grader venstre
					QUADReset(encLeft);
					QUADReset(encRight);			
					robotTurn = -0.2f;
					robotSpeed = 0.0f;
					driveRaw(robotSpeed, robotTurn);
					while ((int)QUADRead(encRight) < 4000) {;}
					robotTurn = 0.0f;
					robotSpeed = 0.0f;
					driveRaw(robotSpeed, robotTurn);
					OSWait(50);
					
					// Fremover
					QUADReset(encLeft);
					QUADReset(encRight);
					robotTurn = 0.0f;
					robotSpeed = 0.1f;
					driveRaw(robotSpeed, robotTurn);							
					while ((evl+evr)/2 < 3100) {updateEncoderValues();}	
					robotTurn = 0.0f;
					robotSpeed = 0.0f;
					driveRaw(robotSpeed, robotTurn);
					OSWait(50);
					
					// sving 90 grader høyre
					QUADReset(encLeft);
					QUADReset(encRight);			
					robotTurn = 0.2f;
					robotSpeed = 0.0f;
					driveRaw(robotSpeed, robotTurn);
					while ((int)QUADRead(encLeft) < 4500) {;}
					robotTurn = 0.0f;
					robotSpeed = 0.0f;
					driveRaw(robotSpeed, robotTurn);
					OSWait(50);
					
					// Fremover
					QUADReset(encLeft);
					QUADReset(encRight);
					robotTurn = 0.0f;
					robotSpeed = 0.1f;
					driveRaw(robotSpeed, robotTurn);							
					while ((evl+evr)/2 < 3500) {updateEncoderValues();}	
					robotTurn = 0.0f;
					robotSpeed = 0.0f;
					driveRaw(robotSpeed, robotTurn);
					
					break;
			}

		}
		LCDClear();
		updateEncoderValues();
		LCDSetPrintf(1,1,"%d",(int)evl);
		LCDSetPrintf(2,1,"%d",(int)evr);
	}

	SERVORelease(servoLeft | servoRight);
	QUADRelease(encLeft | encRight);

	return 0;

}



//speed -1 to +1	Backward, Forward
//turn -1 to +1		Left, Right
//Uferdig
void driveRaw(float speed, float turn) {

	float leftSpeed, rightSpeed;

	leftSpeed = speed + turn;
	rightSpeed = speed - turn;

	//Clamp to [-1,+1]
	leftSpeed  = leftSpeed  >  1.0f ?  1.0f : leftSpeed;
	leftSpeed  = leftSpeed  < -1.0f ? -1.0f : leftSpeed;
	rightSpeed = rightSpeed >  1.0f ?  1.0f : rightSpeed;
	rightSpeed = rightSpeed < -1.0f ? -1.0f : rightSpeed;

	SERVOSet(servoLeft, 128+(int)(127.0f*leftSpeed));
	SERVOSet(servoRight, 128+(int)(127.0f*rightSpeed));



//	leftSpeed = speed + (turn+1)/2.0f;
//	rightSpeed = speed + (1-turn)/2.0f;

//	SERVOSet(servoDrive, (int)CENTER_DRIVE-speed*MAX_SPEED);
//	SERVOSet(servoTurn, (int)CENTER_TURN-turn*MAX_TURN);
}



void updateEncoderValues() {
	evr = (int)((float)(QUADRead(encRight)*WHEELDIFF));
	evl = QUADRead(encLeft);
}

void writeStringToSerial(char dataString[], int serialPort) {
	int i=0;

	while(dataString[i]) {
        OSSendRS232(&(dataString[i]), serialPort);
		i++;
	}

}



