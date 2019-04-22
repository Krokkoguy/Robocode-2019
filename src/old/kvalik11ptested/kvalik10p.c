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
	
		
	LCDPrintf("."); // started sign
	
	gylotin();
	opprampe();	
	nedrampe();
	toBane2();
	
	tospeedgulport();
	
	// Stopper når bane2 slutter
	driveToLine(5000);
	fram(500);
	turn(RIGHT, 3600);

	kjegler4();
	
	releaseMotor();
	releaseServo();
	
	return 0;
}

