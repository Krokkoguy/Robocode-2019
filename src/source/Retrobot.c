#include "eyebot.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "Retrobot.h"
#include "RetrobotDrive.h"
#include "RetrobotTasks.h"

int main(){
	
	initMotor();
//	initServo();
	LCDPrintf("start"); // started sign
		
	// Tasks
	taskGylotin();
	taskVippeport();
	taskOpprampe();
	//taskTrapptilMal();
	//taskOpptrapp();
	taskOksport();
	
	// Stop and release 
	stop();
	OSWait(100);
	releaseMotor();
//	releaseServo();
	return 0;
}


