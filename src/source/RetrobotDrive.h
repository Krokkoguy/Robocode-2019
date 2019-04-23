void driveFollowLineTicks(int tics)
{
	resetEncoders();
	int i;
	tick = 0;
	while (getEncoder(AVERAGE) < tics)
	{
		i = followLineLoop(0.2);
		if (!i)
		{	// Mistet strek
			stop();
			LCDPrintf("Mistet strek - dFLTicks");
			break;
		}
	}
	stop();
}

void driveFollowLineTicksSlow(int tics)
{
	resetEncoders();
	int i;
	tick = 0;
	while (getEncoder(AVERAGE) < tics)
	{
		i = followLineLoop(0.15);
		if (!i)
		{	// Mistet strek
			stop();
			LCDPrintf("Mistet strek - dFLTSlow");
			break;
		}
	}
	stop();
}

void driveFollowLineTicksFast(int tics)
{
	resetEncoders();
	int i;
	tick = 0;
	while (getEncoder(AVERAGE) < tics)
	{
		i = followLineLoop(0.3);
		if (!i)
		{	// Mistet strek
			stop();
			LCDPrintf("Mistet strek - dFLTSlow");
			break;
		}
	}
	stop();
}

void driveFollowLineTicksTrapp(int tics)
{
	resetEncoders();
	int i;
	tick = 0;
	while (getEncoder(AVERAGE) < tics)
	{
		i = followLineLoop(0.15);
		if (!i)
		{	// Mistet strek
			//stop();
			LCDPrintf("Mistet strek - Trapp");
			tick = 0;
			//break;
		}
	}
	stop();
}


void driveToCross(int retning, int tics)
{
	//LCDPrintf("%d", OSReadInLatch(0));
	if (retning == LEFT)
		retning = 135; //248;
	else if (retning == RIGHT)
		retning = 240; //15;
	else
		retning = 128;
		
	resetEncoders();
	int i;
	while (getEncoder(AVERAGE) < tics && OSReadInLatch(0) != retning)
	{
		readIRLine();
		i = followLineLoop(0.2);
		if (!i)
		{	// Mistet strek
			stop();
			LCDPrintf("Mistet strek - dTCross");
			break;
		}
	}
	stop();
	if (getEncoder(AVERAGE) >= tics)
		LCDPrintf("\r\n Stoppet på tics");
	else
		LCDPrintf("\r\n Cross");
}

void driveToLine(int tics)
{
	resetEncoders();
	robotSpeed = 0.2;
	robotTurn = 0;
	driveRaw(robotSpeed, robotTurn);
	while (getEncoder(AVERAGE) < tics)
	{
		readIRLine();
		
		if (!binlys[3] && !binlys[4])
		{
			LCDPrintf("Line");
			stop();
			break;
		}
	}
	stop();
}


void fram(int tics)
{
	resetEncoders();
	robotSpeed = 0.2f;
	robotTurn = 0.0f;
	driveRaw(robotSpeed, robotTurn);		
	while (getEncoder(AVERAGE) < tics) {;}
	stop();
}

void rygg(int tics)
{
	resetEncoders();
	robotSpeed = -0.15f;
	robotTurn = 0.0f;
	driveRaw(robotSpeed, robotTurn);		
	while (getEncoder(AVERAGE) > -tics) {;}
	stop();
}

void turn(int side, int tics)
{
	stop();
	resetEncoders();
	robotSpeed = 0.0;
	if (side == LEFT)
	{
		robotTurn = -0.3f;
		driveRaw(robotSpeed, robotTurn);		
		while (getEncoder(side) > -tics) {;}
	}
	else
	{
		robotTurn = 0.3f;
		driveRaw(robotSpeed, robotTurn);		
		while (getEncoder(side) > -tics) {;}
	}
	stop();
}

/*
void safeLostLine()
{
	// Rygg uten å resette enkoder
	int j = getEncoder(AVERAGE);
	robotSpeed = -0.15f;
	robotTurn = 0.0f;
	driveRaw(robotSpeed, robotTurn);
	while ((getEncoder(AVERAGE) - j) > -3000) 
	{
		; // rygg til strek funnet
	}
	stop();
	// se etter strek
	// hvis strek fortsett
	// hvis ikke selfdestruct
}
*/

