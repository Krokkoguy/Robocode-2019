#define SPEED_FAST 0.3
#define SPEED_NORMAL 0.2
#define SPEED_SLOW 0.15

void taskGylotin()
{
	LCDPrintf("\r\n Gylotin");
	driveFollowLine(190000, SPEED_NORMAL);	// litt forbi gylotin
	driveFollowLine(95000, SPEED_SLOW);	// litt opp rampe
	driveFollowLine(40000, SPEED_NORMAL);
}

void taskVippeport()
{
	LCDPrintf("\r\n Vippeport");

	driveToCross(LEFT, 150000);
	//sving til vippeport og kjør ned
	fram(5000);
	turn(LEFT, 10000);	//4300
	driveFollowLine(125000, SPEED_SLOW);
	//rygg(2000);
	
	driveRaw(-0.15, 0.0f);
	OSWait(70);
	
	// kjør i blinde til strek foran trapp
	//OSWait(100);
	fram(16000);
	turn(RIGHT, 8700);
	fram(40000);
	//OSWait(100);

	
	driveToLine(15000);
	// ved strek, sving venstre og følg til neste kryss
	fram(1000);
	turn(LEFT, 8000);
	
	driveRaw(-0.15, 0.0f);
	OSWait(170);

	//driveFollowLine(15000, SPEED_NORMAL);
	fram(15000);
	//OSWait(100);
	
	driveRaw(0.25f, 0.15f);
	OSWait(210); //215
	stop();
	//OSWait(100);
	fram(4000); //5000
	//OSWait(100);
	driveToLine(15000);
	//fram(1000);
	turn(RIGHT, 1000);
	//OSWait(100);
	
/*	
	driveToCross(FRONT, 20000);
	fram(3000);
	OSWait(100);
	turn(RIGHT, 9700);
	OSWait(100);
	*/
}

void taskOpprampe()
{
	LCDPrintf("\r\n Opp rampe");
	driveFollowLine(117000, SPEED_FAST);	// opp til rampe

	driveFollowLine(40000, SPEED_SLOW);
	//OSWait(100);
	turn(RIGHT, 4000);
	fram(5000);
	driveToLine(10000);
	//rygg(1000);
	turn(RIGHT, 6700);

	LCDPrintf("\r\n ned trapp");
	driveFollowLineTicksTrapp(35000);
	driveRaw(-0.2, 0.0f);
	OSWait(50);
	driveFollowLineTicksTrapp(22000);
	driveRaw(-0.2, 0.0f);
	OSWait(50);
	driveFollowLineTicksTrapp(22000);
	driveRaw(-0.2, 0.0f);
	OSWait(50);
	driveFollowLineTicksTrapp(22000);
	driveRaw(-0.2, 0.0f);
	OSWait(50);
	driveFollowLineTicksTrapp(22000);
	driveRaw(-0.2, 0.0f);
	OSWait(50);
	
	
	
}

void taskTrapptilMal()
{
	
	driveFollowLine(42000, SPEED_SLOW);
	stop();
	OSWait(100);
	//driveToCross(LEFT, 10000);
	//stop();
	//OSWait(100);
	turn(RIGHT, 8000);
	fram(30000);
	OSWait(100);
	turnToDistance(FRONT, 200);
	OSWait(100);
	fram(50000);
	
	
}

/*
void taskOpptrapp()
{
//	armDown();
//	OSWait(100);
	driveRaw(-0.5f, 0.0f);	
	OSWait(100);
	armDown();
	OSWait(100);
}
*/

void taskOksport()
{
	
	driveFollowLine(42000, SPEED_SLOW);
	stop();
	OSWait(100);
	//driveToCross(LEFT, 10000);
	//stop();
	//OSWait(100);
	turn(RIGHT, 8000);
	fram(30000);
	OSWait(100);
	turn(LEFT, 7300);
	//turnToDistanceLeft(FRONT, 350);
	//OSWait(100);
	//turn(LEFT, 3000);
	fram(14000);
	stop();
	OSWait(100);

	//ved oks
	int i = 0;
	while(i < 10)
	{
		if (getDistance(FRONT) > 200) 
			i++;
		else
			i=0;
	}
	
	i=0;
	while(i < 10)
	{
		if (getDistance(FRONT) < 100) 
			i++;
		else
			i=0;
	}
	
		
	framFast(20000);
	
	stop();
	OSWait(300);
	
	ryggFast(35000);
	stop();
	
	
	turn(RIGHT, 10000);
	//fram(30000);
	OSWait(100);
	turnToDistance(FRONT, 200);
	OSWait(100);
	fram(50000);
	
}


