/*
void taskLysport()
{
	driveFollowLinePort(15000, RIGHT);
	rygg(6000);
	turn(LEFT, 4400);
	camUp();
	fram(3000);
	//driveToPort(RIGHT, 3500);
	
	turn(RIGHT, 1500);
	turnFrontObject(RIGHT, 3500, 500);
	turn(LEFT, 15);
	fram(500);
	
	int i = 0;
	int vent = 50;
	int terskel = 1200;
	i = lysport(vent, terskel);
	i = i + lysport(vent, terskel);
	i = i + lysport(vent, terskel);

	if (i < 2) 			// port lyser ikke (se litt til venstre)
	{
		turn(LEFT, 15);
		i = lysport(vent, terskel);
		i = i + lysport(vent, terskel);
		i = i + lysport(vent, terskel);
		turn(RIGHT, 15);
	}

	
	if (i < 2) 			// port lyser ikke (se litt til høyre)
	{
		turn(RIGHT, 15);
		i = lysport(vent, terskel);
		i = i + lysport(vent, terskel);
		i = i + lysport(vent, terskel);
		turn(LEFT, 15);
	}
	

	if (i < 2)			// 1.port lyser ikke
		{
			driveFollowLineTicks(15000);
			driveFollowLinePort(10000, RIGHT);
			
			rygg(5000);
			turn(LEFT, 4200);
			fram(9000);
			turn(RIGHT, 3100);
			fram(12000);
			turn(RIGHT, 3100);
	
			driveToLine(13000);
			fram(300);
			turn(LEFT, 4300);
		}
		else
		{					// 1.port lyser
			rygg(5000);
			turn(LEFT, 4200);
			fram(9000);
			turn(RIGHT, 3100);
			fram(12000);
			turn(RIGHT, 3100);
			
			driveToLine(13000);
			fram(300);
			turn(LEFT, 4300);
		
			driveFollowLinePort(15000, RIGHT);
			driveFollowLineTicks(3000);
	
		}

}
*/

void taskLysport3()
{
	driveToTKryss(RIGHT, 10000);
	rygg(3000);
	turn(RIGHT, 3600);

	camUp();
	
	
	int i = 0;
	int vent = 70;
	int terskel = 1150;
	i = lysport(vent, terskel);
	i = i + lysport(vent, terskel);
	i = i + lysport(vent, terskel);

	if (i < 2) 			// port lyser ikke (se litt til venstre)
	{
		turn(LEFT, 15);
		i = lysport(vent, terskel);
		i = i + lysport(vent, terskel);
		i = i + lysport(vent, terskel);
		turn(RIGHT, 15);
	}


	if (i < 2) 			// port lyser ikke (se litt til høyre)
	{
		turn(RIGHT, 15);
		i = lysport(vent, terskel);
		i = i + lysport(vent, terskel);
		i = i + lysport(vent, terskel);
		turn(LEFT, 15);
	}

	turn(LEFT, 4400);
	//rygg(3000);
	
	driveToTKryss(RIGHT, 3000);
	fram(400);
	turn(RIGHT, 3400);
	
	driveFollowLinePort(15000, RIGHT);
	
	if (i < 2)			// 1.port lyser ikke
		{
			driveFollowLineTicks(6000);
			driveFollowLinePort(16000, RIGHT);
			
			rygg(5000);
			turn(LEFT, 4200);
			fram(9000);
			turn(RIGHT, 3100);
			fram(12000);
			turn(RIGHT, 3100);
	
			driveToLine(11000);
			fram(300);
			turn(LEFT, 4300);
		}
		else
		{		
			// 1.port lyser
			rygg(5000);
			turn(LEFT, 4200);
			fram(9000);
			turn(RIGHT, 3100);
			fram(12000);
			turn(RIGHT, 3100);
			
			driveToLine(11000);
			fram(300);
			turn(LEFT, 4300);
			driveFollowLineTicks(16000);
	
		}

	
}

void rampeToBall()
{
	//driveToBallLeft(5000);
	
		
	
	turn(LEFT, 3500);	// erstatt denne med en som svinger til ball ses midt i bilde eller på front ir
	
	//turnFrontObject(LEFT, 4500, 450);
	LCDPrintf("\r\nENC: %d", ((evl+evr)/2));
	
	//driveToBallFront(4000);
	LCDPrintf("\r\nENC: %d", ((evl+evr)/2));
	
	//fram(2500);			// bruk ir info til å bestemme avstand og antall ticks
	camUp();
	OSWait(100);
	CAMGetFrame(&camimage1);	// Ta bilde 1
	LCDPutGraphic(&camimage1);
	
	//armDown();
	//OSWait(100);
	//kloClose();
	//OSWait(50);
	//armUp();
	
	
}


void gylotin()
{
	driveFollowLineTicks(110000);
	driveFollowLineTicks(25000);
	//driveFollowLinePort(30000, RIGHT);
}

void opprampe()
{
	driveToTKryss(LEFT, 85000);
	LCDPrintf("\r\nENC: %d", ((evl+evr)/2));
	fram(2000);
	driveToVeiskilleLeft(18000);
	LCDPrintf("\r\nENC: %d", ((evl+evr)/2));
}

void opprampe2()
{
	//driveToTKryss(LEFT, 85000);
	
	//LCDPrintf("\r\nENC: %d", ((evl+evr)/2));
	
	//OSWait(100);
	//fram(4000);
	OSWait(100);
	turn(LEFT, 4000);	//4300
	OSWait(100);
	driveFollowLineTicks(3300);
	OSWait(100);
	fram(3500);
	
	OSWait(100);

	driveFollowLineTicks(40000);
	
	fram(10000);
	
	turn(RIGHT, 3100);
	
	fram(17000);

	driveToLine(10000);
	
	fram(500);
	
	turn(LEFT, 4400);
	
	
	
	//driveToVeiskilleLeft(35000);
	//LCDPrintf("\r\nENC: %d", ((evl+evr)/2));
}

void opptrapp()
{
	
	driveToTKryss(0, 60000);
	
	fram(500);
	
	turn(RIGHT, 3100);
	
	driveFollowLineTicks(20000);
	
	driveFollowLineTicksFast(48000);
	
	driveToomvendtVeiskillerampe(27000);
	
	//fram(500);
	
	//rygg(5000);
	
	turn(RIGHT, 3900);
	
	driveFollowLineTicks(12500);
	
	framsakte(48000);
	
	driveToTKryss(0, 60000);
	
	fram(3000);
}

void nedtrapp()
{
	turn(LEFT, 1000);
	driveFollowLineToTrapp(6000);
}

void nedrampe()
{
	turn(RIGHT, 500);
	//fram(1000);
	driveFollowLineTicks(70000);
	driveToTKryss(LEFT, 18000);
}

void tilrampeball()
{
	turn(LEFT, 2200);
	fram(3000);
	kloOpen();
	armDown();
	OSWait(100);
	kloClose();
	OSWait(100);
	armUp();
	
}

void toBane2()
{
	fram(400);
	turn(RIGHT, 3400);
	//fram(2000);
	driveToLine(2000);
	
	
}


void tospeedgulport()
{
	driveFollowLineTicks(20000);
	driveToTKryss(0, 30000);
	LCDPrintf("\r\nKryss: %d", ((evl+evr)/2));
	fram(500);
	turn(LEFT,4400);
	
	driveToTKryss(0, 150000);
	LCDPrintf("\r\nKryss: %d", ((evl+evr)/2));
	fram(500);
	turn(RIGHT,3000);
	
	driveFollowLineTicks(100000);
	
}

/*
void kjegler()
{
	driveToTKryss(LEFT, 35000);
	fram(400);
	turn(RIGHT, 3500);
	fram(30000);
	turn(RIGHT, 3400);
	fram(6000);
	turn(LEFT, 4400);
	fram(17000);
	turn(LEFT, 4400);
	fram(35000);
	turn(LEFT, 4400);
	fram(15000);
	turn(LEFT,4400);
	fram(8000);
	turn(RIGHT, 3500);
	driveToLine(30000);
}

void kjegler2()
{
	driveFollowLineTicks(5000);
	driveToTKryss(LEFT, 30000);
	fram(400);
	turn(RIGHT, 3550);
	//rygg(5000);
	//driveToTKryss(LEFT, 5000);
	fram(20000);
	LCDPrintf("\r\nENC: %d", ((evl+evr)/2));
	framSluttKjegle(2600);
	LCDPrintf("\r\nENC: %d", ((evl+evr)/2));

	fram(500);
	turn(LEFT, 4400);
	
	fram(6000);
	framSluttKjegle(5000);
	
	

}

void kjegler3()
{
	driveFollowLineTicks(5000);
	driveToTKryss(LEFT, 30000);
	fram(400);
	turn(LEFT, 4400);
	
	driveFollowLineTicks(5000);
	
	//rygg(5000);
	//driveToTKryss(LEFT, 5000);
	rygg(30000);
	LCDPrintf("\r\nENC: %d", ((evl+evr)/2));
	ryggSluttKjegle(2600);
	LCDPrintf("\r\nENC: %d", ((evl+evr)/2));

	rygg(1300);
	turn(RIGHT, 2500);
	
	//fram(6000);
	//framSluttKjegle(5000);
	
	

}
*/

void kjegler4()
{
	driveFollowLineTicks(5000);
	driveToTKryss(LEFT, 30000);
	fram(500);
	turn(LEFT, 4300);
	
	driveFollowLineTicks(5000);
	
	rygg(4000);
	
	driveFollowLineTicks(5000);
	
	rygg(4000);
		
	driveFollowLineTicks(5000);
	
	//driveToTKryss(LEFT, 5000);
	rygg(18000);
	LCDPrintf("\r\nENC: %d", ((evl+evr)/2));
	driveToLine(18000);
	fram(500);
	turn(RIGHT,3000);
	
	driveFollowLineTicks(14000);
	driveToTKryss(LEFT, 4000);
	fram(500);
	turn(LEFT, 4300);

	driveFollowLineTicks(5000);

	rygg(3000);
		
	driveFollowLineTicks(5000);

	//rygg(5000);
	//driveToTKryss(LEFT, 5000);
	rygg(18000);
	LCDPrintf("\r\nENC: %d", ((evl+evr)/2));
	driveToLine(18000);
	fram(500);
	turn(RIGHT,3000);
	
	
	driveFollowLineTicks(80000);
}
