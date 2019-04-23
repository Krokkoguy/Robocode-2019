#include "eyebot.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "Retrobot.h"
#include "RetrobotDrive.h"
#include "RetrobotTasks.h"

int main(){
	
	initMotor();
	LCDPrintf("start"); // started sign
	
	// Tasks
	//taskGylotin();
	//taskVippeport();
	taskOpprampe();
	
	// Stop and release 
	stop();
	OSWait(100);
	releaseMotor();
	return 0;
}


