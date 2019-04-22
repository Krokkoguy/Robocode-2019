//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
#include "eyebot.h"

#define BASE_SERIAL SERIAL2
#define SERVO_ARM SERVO11
#define SERVO_LEFT SERVO12
#define SERVO_RIGHT SERVO13
#define FRONT 1
#define LEFT 2
#define RIGHT 3
#define AVERAGE 4
#define DIST_SENSOR 7

ServoHandle servoLeft, servoRight, servoArm;
QuadHandle encLeft, encRight;

int a2, a3, a4, a5, a6;	// LED variabler
int t2, t3, t4, t5, t6;	// Grensevariabler
int spd1, spd2, spd3;	// Hastighetsvariabler
int ql, qr;				// Enkoder variabler

/*
 dig ut
 0 - lys
 1 - photoresistor midt bak
 2 - ir front
 3 - ir left
 4 - ir right
 
 dig in
 6 - høyre
 7 - venstre
 
 analog in
 2 - photo: venstre frem og høyre bak
 3 - photo: høyre frem og venstre bak
 4 - photo: midt venstre
 5 - photo: midt høyre
 6 - photo: midt
 7 - ir sensorer 
*/

int init();						// Initierer alt. Returnerer 0 hvis OK og 1 hvis feil.
void release();					// Releaser alt.
int irGetDistance(int irID);	// Henter distansen, irID = FRONT/LEFT/RIGHT
int GetEncoder(int encID);		// Henter encoderverdien, encID = LEFT/RIGHT/MIDDLE
void ResetEncoder();			// Resetter enkoderen
void UpdateLEDs();				// Oppdaterer LEDs
void FollowLine(int lr);		// Leser leds og setter hastighet, må kjøres i loop, lr=1 foretrekker venstre, lr=0 foretrekker høyre
void Stop();					// Stopper roboten
int AllWhite();					// Sjekker om alle LEDs er hvite, ja = 1, nei = 0;

void DriveOnEncoder(int tics, int speedL, int speedR);
void FollowLineOnEncoder(int tics, int lr);
void DriveOnTime(int time);
void FollowLineOnTime(int time, int lr);
void FollowLineOnPort(int lr);
void FollowLineOnCross(int lr);

void TurnLeft();
void TurnRight();


int DoesBlink(int c1, int c2, int c3);
int IMGCountBPix(image img);

int init()
{
	servoLeft = SERVOInit(SERVO_LEFT);
  	servoRight = SERVOInit(SERVO_RIGHT);
	servoArm = SERVOInit(SERVO_ARM);

  	encLeft = QUADInit(QUAD_LEFT);
  	encRight = QUADInit(QUAD_RIGHT);

  	OSWriteOutLatch(0, 0xFE, 0x01); // Lights on

	/*
	Venstre ir
		260, 290,370
		260, 220-230
	Høre ir
		218-242, (250)-310-370
		
	forran
		280-
	*/

	// Setter grenseverdier
	t2 = 250;	// 390-400-440-300, 170-190-200
	t3 = 200;	// 300-280-200-190, 140-150
	t4 = 1021;	// 1023-1000-980, 930
	t5 = 710;	// 919-810-760, 650-680 old:720
	t6 = 550;	// 800-600-590-560, 410-420-470-490

	// Setter hastigheter
	spd1 = 166;	// Fremover
	spd2 = 127;	// Stå stille
	spd3 = 100;	// Rygge
	
	if (servoLeft == 0 || servoRight == 0 || servoArm == 0 || encLeft == 0 || encRight == 0)
	{
		LCDPrintf("Feil i servoinit\n");
		
		return 1;
	}
		
	return 0;
}

void release()
{
	Stop();

  	SERVORelease(servoLeft | servoRight | servoArm);
	QUADRelease(encLeft | encRight);
}

int irGetDistance(int irID)
{
	switch(irID)
	{
		case FRONT:
			// slå av ir left og right: 1110 0111
			OSWriteOutLatch(0, 0xE7, 0x00);
			// slå på ir front: 1111 1011
			OSWriteOutLatch(0, 0xFB, 0x04);
			break;
		case LEFT:
			// slå av ir front og right: 1110 1011
			OSWriteOutLatch(0, 0xEB, 0x00);
			//slå på ir left: 1111 0111
			OSWriteOutLatch(0, 0xF7, 0x08);
			break;
		case RIGHT:
			// slå av ir front og left: 1111 0011
			OSWriteOutLatch(0, 0xF3, 0x00);
			//slå på ir right: 1110 1111
			OSWriteOutLatch(0, 0xEF, 0x10);
			break;
	}
	OSSleep(5);
	OSGetAD(DIST_SENSOR);
	OSGetAD(DIST_SENSOR);
	return (int)OSGetAD(DIST_SENSOR);
}

int GetEncoder(int encID)
{
	ql = QUADRead(encLeft);
	qr = QUADRead(encRight);
	
	if (encID == LEFT)
		return ql;
	else if (encID == AVERAGE)
		return ((ql+qr) / 2);
	else
		return qr;
}

void ResetEncoder()
{
	QUADReset(encLeft);
	QUADReset(encRight);
	
	ql = 0;
	qr = 0;
}

void UpdateLEDs()
{
	// Leser sensorer
	a2 = OSGetAD(2);
	a3 = OSGetAD(3);
	a4 = OSGetAD(4);
	a5 = OSGetAD(5);
	a6 = OSGetAD(6);
}

// Follow line
// lr = 1 prioritizes left
// lr = 0 prioritizes right
void FollowLine(int lr)
{
	// Leser sensorer
	UpdateLEDs();
	
	if (lr > 0)
	{
		if (a4 < t4)
		{	// Sving venstre
			SERVOSet(servoLeft, spd2);
			SERVOSet(servoRight, spd1);
		}
		else if (a2 < t2)
		{	// Roter venstre
			SERVOSet(servoLeft, spd3);
			SERVOSet(servoRight, spd1);
		}
		else if (a5 < t5)
		{	// Sving høyre
			SERVOSet(servoLeft, spd1);
			SERVOSet(servoRight, spd2);
		}
		else if (a3 < t3)
		{	// Roter høyre
			SERVOSet(servoLeft, spd1);
			SERVOSet(servoRight, spd3);
		}
		/*		else if (a6 < t6)
		{
			SERVOSet(servoLeft, spd1+20);
			SERVOSet(servoRight, spd1+20);
		}*/
		else
		{	// Kjør fremover
			SERVOSet(servoLeft, spd1+3);
			SERVOSet(servoRight, spd1);
		}
	}
	else
	{
		if (a5 < t5)
		{	// Sving høyre
			SERVOSet(servoLeft, spd1);
			SERVOSet(servoRight, spd2);
		}
		else if (a3 < t3)
		{	// Roter høyre
			SERVOSet(servoLeft, spd1);
			SERVOSet(servoRight, spd3);
		}
		else if (a4 < t4)
		{	// Sving venstre
			SERVOSet(servoLeft, spd2);
			SERVOSet(servoRight, spd1);
		}
		else if (a2 < t2)
		{	// Roter venstre
			SERVOSet(servoLeft, spd3);
			SERVOSet(servoRight, spd1);
		}
/*		else if (a6 < t6)
		{
			SERVOSet(servoLeft, spd1+20);
			SERVOSet(servoRight, spd1+20);
		}*/
		else
		{	// Kjør fremover
			SERVOSet(servoLeft, spd1+3);
			SERVOSet(servoRight, spd1);
		}
	}
	
	return;
}

void Stop()
{
	SERVOSet(servoLeft, 127);
	SERVOSet(servoRight, 127);
	
	OSSleep(50);
	
	return;
}

int AllWhite()
{
	UpdateLEDs();
	
	if (a2 < t2)
		return 0;
	if (a3 < t3)
		return 0;
	if (a4 < t4)
		return 0;
	if (a5 < t5)
		return 0;
	if (a6 < t6)
		return 0;
	
	return 1;
}









void DriveOnEncoder(int tics, int speedL, int speedR)
{
	Stop();
	ResetEncoder();
	
	SERVOSet(servoLeft, speedL);
	SERVOSet(servoRight, speedR);
	
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
	
	SERVOSet(servoLeft, spd1);
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

void FollowLineOnPort(int lr)
{
	Stop();
	ResetEncoder();
	
	if (lr > 0)
	{
		while (irGetDistance(LEFT) < 370)
		{
			FollowLine(lr);
			OSSleep(1);
		}
	} 
	else
	{
		while (irGetDistance(RIGHT) < 360)
		{
			FollowLine(lr);
			OSSleep(1);
		}
	}
	
	
	Stop();
	return;
}


void FollowLineOnCross(int lr)
{
	Stop();
		
	UpdateLEDs();
	
	if (lr > 0)
	{
		while (OSGetAD(2) > t2)
		{
			FollowLine(lr);
			
		}
	} 
	else
	{
		while (OSGetAD(3) > t3)
		{
			FollowLine(lr);
			
		}
	}
	
	
	Stop();
	return;
}


void TurnLeft()
{
	// sving ca 90 grader til venstre
	ResetEncoder();
	SERVOSet(servoLeft, 100);
	SERVOSet(servoRight, 156);
	while (GetEncoder(RIGHT) < 4700)
	{}
	Stop();
}


void TurnRight()
{
	
}




int IMGCountBPix(image img)
{
	int i, j;
	int bnumber = 0;
	
	for (i = 1; i < 81; i++)
	{
		for (j = 1; j < 61; j++)
		{
			if (img[i][j] < 127)
			{
				bnumber++;
			}
		}
	}
	
	return bnumber;
}

int DoesBlink(int c1, int c2, int c3) // 1: blink, 0: ikke blink
{
	int t1, t2, t3;
	int max, min, diff;
	
	t1 = c1 - c2;	// 931 - 1084 = -153
	t2 = c1 - c3;	// 931 - 1095 = -164
	t3 = c2 - c3;	// 1084 - 1095 = -11
	
	if (t1 < 0)
		t1 *= -1;	// t1 = 153
	if (t2 < 0)
		t2 *= -1;	// t2 = 164
	if (t3 < 0)
		t3 *= -1;	// t3 = 11
	
	max = t1;		// max = 164
	if (t2 > max)
		max = t2;
	if (t3 > max)
		max = t3;
	
	min = t1;		// min = 11
	if (t2 < min)
		min = t2;
	if (t3 < min)
		min = t3;
	
	diff = max - min;	// 164-11=153
	
	if (diff > 100)
	{
		return 1;
	}
	
	return 0;
}

