void taskGylotin()
{
	LCDPrintf("\r\n Gylotin");
	driveFollowLineTicks(200000);	// litt forbi gylotin
	driveFollowLineTicks(100000);	// litt opp rampe
}

void taskVippeport()
{
	LCDPrintf("\r\n Vippeport");
	driveToCross(LEFT, 200000);
	//sving til vippeport og kjør ned
	fram(5000);
	turn(LEFT, 10000);	//4300
	driveFollowLineTicksSlow(103000);
	rygg(2000);
	// kjør i blinde til strek foran trapp
	OSWait(100);
	fram(10000);
	turn(RIGHT, 8800);
	fram(40000);
	OSWait(100);
	driveToLine(15000);
	// ved strek, sving venstre og følg til neste kryss
	fram(1000);
	turn(LEFT, 8000);
	OSWait(100);
	driveFollowLineTicks(20000);
	OSWait(100);
	driveToCross(FRONT, 20000);
	fram(1000);
	OSWait(100);
	turn(RIGHT, 9700);
	OSWait(100);
	
}

void taskOpprampe()
{
	LCDPrintf("\r\n Opp rampe");
	//driveFollowLineTicksFast(100000);	// opp til rampe 
	driveFollowLineTicksSlow(40000);
	//OSWait(100);
	turn(RIGHT, 4000);
	fram(5000);
	driveToLine(10000);
	//fram(1000);
	turn(RIGHT, 4000);
	LCDPrintf("\r\n ned trapp");
	driveFollowLineTicksTrapp(100000);
	//driveToCross(RIGHT, 30000);
	
}
