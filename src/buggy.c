#include "buggy.h"

void giljotin();
void speed();
void lysport();
void plukkball1();
void tilhull();
void tiltrapp();
void tiltrapp2(); // med n�rmeste kjegle port
void rampe();
void tunnel();
void tunnel2();	// ta tunnel etter lysport
void kjegle();
void speed2();
void drititunnel();


int main()
{
	LCDPrintf("Started\n");


	init();
	
	/* oppgaver */
	
	giljotin();
	speed();
	
	lysport();
											//tunnel2();
	plukkball1();
											//tilhull();
	tiltrapp2();

	rampe();
	//drititunnel();
	tunnel();
	kjegle();
	
	release();

	return 0;
}







void giljotin()
{
	spd1 = 156;
	spd2 = 128;

	LCDPrintf("giljotin\n");
	FollowLineOnPort(1);
	//FollowLineOnEncoder(170000, 1);
}



void speed()
{
	LCDPrintf("speed\n");
	
	spd1 = 166;
	spd2 = 127;
	
	// kj�r forbi sving
	FollowLineOnEncoder(260000, 1);
	
	/*
	// kj�r sakte for korigering
	spd1 = 144;
	spd2 = 138;
	FollowLineOnEncoder(15000, 0);
	
	// maks hastighet til port
	ResetEncoder();
	
	SERVOSet(servoLeft, 206);
	SERVOSet(servoRight, 200);
	
	while (GetEncoder(AVERAGE) < 75000)
	{
			OSSleep(1);
	}
	
	Stop();
	
	*/
	
	
	spd1 = 150;
	spd2 = 127;
	
	LCDPrintf("looking for port\n");
	
	FollowLineOnPort(0);
	Stop();
	
}


void speed2()
{
	LCDPrintf("speed2\n");
	
	spd1 = 166;
	spd2 = 127;
	
	// kj�r forbi sving
	FollowLineOnEncoder(86000, 1);
	
	
	// kj�r sakte for korigering
	spd1 = 144;
	spd2 = 138;
	FollowLineOnEncoder(15000, 0);
	
	// maks hastighet til port
	ResetEncoder();
	
	SERVOSet(servoLeft, 206);
	SERVOSet(servoRight, 200);
	
	while (GetEncoder(AVERAGE) < 75000)
	{
			OSSleep(1);
	}
	
		
	Stop();
	
	
	
	
	spd1 = 150;
	spd2 = 127;
	
	LCDPrintf("looking for port\n");
	
	FollowLineOnPort(0);
	Stop();
	
}



void lysport()
{

	LCDPrintf("lysport\n");
	
	/*
	
		int encL = 0, encR = 0, encM = 0;
		
		ResetEncoder();
		
		// sving sakte mot h�yre ben av lysport
		SERVOSet(servoLeft, spd1);
		SERVOSet(servoRight, spd3);
		OSSleep(50);
			
		int dist = 0;
		while(dist < 350 && encL < 50000) //(dist - distold) < 30 && encL < 10000)
		{
			dist = irGetDistance(FRONT);
			encL = GetEncoder(LEFT);
		}
		
		SERVOSet(servoLeft, spd3);
		SERVOSet(servoRight, spd2);
		OSSleep(40);
		
		SERVOSet(servoLeft, spd2);
		SERVOSet(servoRight, spd2);
		OSSleep(50);
	
		
		ResetEncoder();
		encM = 0;
		
		LCDPrintf("%d, %d \n", dist, encL);
		OSSleep(50);
		
		// rygg litt
		SERVOSet(servoLeft, spd3);
		SERVOSet(servoRight, spd3);
		while (encM > -2000)
		{
			// kj�r til lysport
	
			encL = GetEncoder(LEFT);
			encR = GetEncoder(RIGHT);
			encM = (encL + encR) / 2;
		}
		SERVOSet(servoLeft, spd2);
		SERVOSet(servoRight, spd2);
		OSSleep(50);
	
		
		// hev arm
		SERVOSet(servoArm, 95);
		OSSleep(50);
		
		// Bildeanalyse
		image  img1, img2, img3, tempimg;
		int img1c, img2c, img3c;
		
		
		
		CAMGetFrame(&img1);
		OSSleep(30);
		CAMGetFrame(&img2);
		OSSleep(30);
		CAMGetFrame(&img3);
		
		
		LCDPrintf("bilder tatt\n");
		
		IPSobel(&img1, &tempimg);
	
		//LCDPutGraphic(&img1);
		//OSSleep(300);
		
		//LCDPutGraphic(&tempimg);
		//OSSleep(200);
		
		img1c = IMGCountBPix(tempimg);
		
		IPSobel(&img2, &tempimg);
		
		//LCDPutGraphic(&img2);
		//OSSleep(300);
	
		//LCDPutGraphic(&tempimg);
		//OSSleep(200);
		
		img2c = IMGCountBPix(tempimg);
		
		IPSobel(&img3, &tempimg);
		
		//LCDPutGraphic(&img3);
		//OSSleep(300);
	
		//LCDPutGraphic(&tempimg);
		//OSSleep(200);
		
		img3c = IMGCountBPix(tempimg);
		
		LCDPrintf("img1: %d \n",img1c);
		LCDPrintf("img2: %d \n",img2c);
		LCDPrintf("img3: %d \n",img3c);
	
		LCDPrintf("Blink: %d \n", DoesBlink(img1c, img2c, img3c));
		
		if (DoesBlink(img1c, img2c, img3c) == 1) // BLINKER!!
		{
			// rygg litt
			ResetEncoder();
			OSSleep(50);
			LCDPrintf("rygg\n");
			
			SERVOSet(servoLeft, spd3);
			SERVOSet(servoRight, spd3);
			while (encM > -6000)
			{
				encL = GetEncoder(LEFT);
				encR = GetEncoder(RIGHT);
				encM = (encL + encR) / 2;
			}
			SERVOSet(servoLeft, spd2);
			SERVOSet(servoRight, spd2);
			OSSleep(50);
			
			// sving ca 90 grader til venstre
			LCDPrintf("sving til venstre\n");
			ResetEncoder();
			OSSleep(50);
			SERVOSet(servoLeft, spd3-10);
			SERVOSet(servoRight, spd1);
			while (encR < 2500)
			{
				encR = GetEncoder(RIGHT);
			}
	
			// kj�r til overgang
			LCDPrintf("kj�r til overgang\n");
			SERVOSet(servoLeft, spd1+15);
			SERVOSet(servoRight, spd1);
			
			while (OSGetAD(2) > 400) {}
			
			SERVOSet(servoLeft, spd2);
			SERVOSet(servoRight, spd2);
			ResetEncoder();
			OSSleep(100);
			
	
			// sving ca 90 grader til h�yre
			LCDPrintf("sving hoyre\n");
			SERVOSet(servoLeft, spd1);
			SERVOSet(servoRight, spd3);
			while (encL < 7000)
			{
				encL = GetEncoder(LEFT);
			}
			
			// kj�r til strek
			LCDPrintf("kj�r til strek\n");
			SERVOSet(servoLeft, spd1);
			SERVOSet(servoRight, spd1);
			
			while(OSGetAD(2) > 300) {}
			
			// stopp
			SERVOSet(servoLeft, spd2);
			SERVOSet(servoRight, spd2);
			OSSleep(50);
		
			
		}
		else		// BLINKER IKKE!!
		{
			// sving litt til venstre
			SERVOSet(servoLeft, spd3);
			SERVOSet(servoRight, spd1);
			OSSleep(80);
			
			// stopp
			SERVOSet(servoLeft, spd2);
			SERVOSet(servoRight, spd2);
			OSSleep(50);
		
			
			// F�lg linje til overgang 
			while (OSGetAD(2) > 400)
			{
				// Leser sensorer
				a2 = OSGetAD(2); // venstre
				a3 = OSGetAD(3); // h�yre
				a4 = OSGetAD(4); // venstre midt
				a5 = OSGetAD(5); // h�yre midt
				a6 = OSGetAD(6); // midt
	
				// Kj�rer
				if (a4 < t4)
				{	// Sving venstre
					SERVOSet(servoLeft, spd2);
					SERVOSet(servoRight, spd1);
				}
				else if (a5 < t5)
				{	// Sving h�yre
					SERVOSet(servoLeft, spd1);
					SERVOSet(servoRight, spd2);
				}
				else if (a2 < t2)
				{	// Roter venstre
					SERVOSet(servoLeft, spd3);
					SERVOSet(servoRight, spd1);
				}
				else if (a3 < t3)
				{	// Roter h�yre
					SERVOSet(servoLeft, spd1);
					SERVOSet(servoRight, spd3);
				}
				else
				{	
					SERVOSet(servoLeft, spd1);
					SERVOSet(servoRight, spd1);
				}
			}
			// stopp
			SERVOSet(servoLeft, spd2);
			SERVOSet(servoRight, spd2);
			OSSleep(50);
			
			// sving ca 90 grader til venstre
			LCDPrintf("sving til venstre\n");
			ResetEncoder();
			encM = 0;
			OSSleep(50);
			
			SERVOSet(servoLeft, spd3-10);
			SERVOSet(servoRight, spd1);
			while (encR < 2500)
			{
				encR = GetEncoder(RIGHT);
			}
			
			// stopp
			SERVOSet(servoLeft, spd2);
			SERVOSet(servoRight, spd2);
			ResetEncoder();
			encM = 0;
			OSSleep(50);
			
			// kj�r frem
			LCDPrintf("kj�r frem\n");
			SERVOSet(servoLeft, spd1);
			SERVOSet(servoRight, spd1);
			while (encM < 12000)
			{
				encL = GetEncoder(LEFT);
				encR = GetEncoder(RIGHT);
				encM = (encL + encR) / 2;
			}
			SERVOSet(servoLeft, spd2);
			SERVOSet(servoRight, spd2);
			OSSleep(50);
	
			// sving ca 90 grader til h�yre
			LCDPrintf("sving til h�yre\n");
			ResetEncoder();
			encL = 0;
			OSSleep(50);
			SERVOSet(servoLeft, spd1);
			SERVOSet(servoRight, spd3);
			while (encL < 5500)
			{
				encL = GetEncoder(LEFT);
			}
			// stopp
			SERVOSet(servoLeft, spd2);
			SERVOSet(servoRight, spd2);
			ResetEncoder();
			encM = 0;
			OSSleep(50);
			
			// kj�r frem
			LCDPrintf("kj�r frem\n");
			SERVOSet(servoLeft, spd1);
			SERVOSet(servoRight, spd1);
			while (encM < 14000)
			{
				encL = GetEncoder(LEFT);
				encR = GetEncoder(RIGHT);
				encM = (encL + encR) / 2;
			}
			SERVOSet(servoLeft, spd2);
			SERVOSet(servoRight, spd2);
			OSSleep(50);
	
			// sving ca 90 grader til h�yre
			LCDPrintf("sving til h�yre\n");
			ResetEncoder();
			encL = 0;
			OSSleep(50);
			SERVOSet(servoLeft, spd1);
			SERVOSet(servoRight, spd3);
			while (encL < 5000)
			{
				encL = GetEncoder(LEFT);
			}
			// stopp
			SERVOSet(servoLeft, spd2);
			SERVOSet(servoRight, spd2);
			OSSleep(50);
			
			// kj�r til strek
			LCDPrintf("kj�r til strek\n");
			SERVOSet(servoLeft, spd1);
			SERVOSet(servoRight, spd1);
					
			while(OSGetAD(6) > t6) {}
			
			// stopp
			SERVOSet(servoLeft, spd2);
			SERVOSet(servoRight, spd2);
			OSSleep(50);
		}
		
		// stopp
		SERVOSet(servoLeft, spd2);
		SERVOSet(servoRight, spd2);
		OSSleep(50);
		
		


	*/


	

	// avslutt lysport ved � kj�re til kryss rett etter siste port
	spd1 = 156;
	spd2 = 127;
	FollowLineOnEncoder(90000, 1);
	FollowLineOnCross(0);
	
	
}


void plukkball1()
{
	LCDPrintf("plukk ball 1\n");
	
	SERVOSet(servoArm, 90);
	spd1 = 156;						// FEILET HER!!!!!
	spd2 = 127;
	FollowLineOnEncoder(96000, 1);
	spd1 = 144;
	spd2 = 127;
	FollowLineOnEncoder(3200, 1);
	SERVOSet(servoArm, 245);
	
	// kj�r p� encoder litt opp rampe
	spd1 = 160;
	spd2 = 127;
	FollowLineOnEncoder(80000, 1);
}



void tilhull()
{
	LCDPrintf("til hull\n");

	SERVOSet(servoArm, 245);

	// kj�r til port p� rampe
	spd1 = 156;
	spd2 = 127;
	FollowLineOnPort(1);
	
	// kj�r til rampetopp
	spd1 = 156;
	spd2 = 127;
	FollowLineOnEncoder(20000, 0);

	// kj�r til hull (nesten)
	DriveOnEncoder(22200, 147, 144);
	
	// kj�r frem til en av lysensorene detektere hull
	ResetEncoder();
	SERVOSet(servoLeft, 146);
	SERVOSet(servoRight, 144);
	while (AllWhite() || GetEncoder(AVERAGE) < 1000)
	{}
	Stop();
	
	if (!AllWhite())
	{
		if (a6 < t6)
		{
			SERVOSet(servoLeft, 112);
			SERVOSet(servoRight, 112);
			while (a6 < t6)
			{ UpdateLEDs(); }
		} 
		else 
		{
			SERVOSet(servoLeft, 112);
			SERVOSet(servoRight, 127);
			OSSleep(50);
			SERVOSet(servoLeft, 127);
			SERVOSet(servoRight, 112);
			OSSleep(100);
		}
		Stop();
		
		// hev arm
	}
	

}




void tiltrapp()
{
	LCDPrintf("til trapp\n");

	// kj�r til port p� rampe
	spd1 = 156;
	spd2 = 127;
	FollowLineOnPort(1);
	
	int encL = 0, encR = 0, encM = 0;
	
	ResetEncoder();
		encM = 0;
		
		SERVOSet(servoArm,0);
		
		LCDPrintf("til midten \n");
		while (encM < 36500)
		{
			encL = GetEncoder(LEFT);
			encR = GetEncoder(RIGHT);
			encM = (encL + encR) / 2;
			
			// Leser sensorer
			a2 = OSGetAD(2); // venstre
			a3 = OSGetAD(3); // h�yre
			a4 = OSGetAD(4); // venstre midt
			a5 = OSGetAD(5); // h�yre midt
			a6 = OSGetAD(6); // midt
	
			// Kj�rer
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
			{	// Sving h�yre
				SERVOSet(servoLeft, spd1);
				SERVOSet(servoRight, spd2);
			}
			else
			{	
				SERVOSet(servoLeft, spd1);
				SERVOSet(servoRight, spd1);
			}
	
		}
		SERVOSet(servoLeft, spd2);
		SERVOSet(servoRight, spd2);
		OSSleep(50);
		LCDPrintf("pa midten\n");
		
		
		ResetEncoder();
		encM = 0;
	
		// Kj�r ned trapp
		SERVOSet(servoLeft, 152);
		SERVOSet(servoRight, 152);
		while (encM < 60000)
		{
			encL = GetEncoder(LEFT);
			encR = GetEncoder(RIGHT);
			encM = (encL + encR) / 2;
		}
		SERVOSet(servoLeft, spd2);
		SERVOSet(servoRight, spd2);
		OSSleep(50);
		
		
		
		
		// Sving til h�yre
		SERVOSet(servoArm, 100);
		SERVOSet(servoLeft, 166);
		SERVOSet(servoRight, 127);
		OSSleep(250);
		
		
		spd1 = 166;
		spd2 = 127;
		// Kj�r opp rampa igjen
		ResetEncoder();
		encM = 0;
		while (encM < 95000)
		{
			encL = GetEncoder(LEFT);
			encR = GetEncoder(RIGHT);
			encM = (encL + encR) / 2;
	
			// Leser sensorer
			a2 = OSGetAD(2); // venstre
			a3 = OSGetAD(3); // h�yre
			a4 = OSGetAD(4); // venstre midt
			a5 = OSGetAD(5); // h�yre midt
			a6 = OSGetAD(6); // midt
	
			// Kj�rer
			if (a5 < t5)
			{	// Sving h�yre
				SERVOSet(servoLeft, spd1);
				SERVOSet(servoRight, spd2);
			}
			else if (a4 < t4)
			{	// Sving venstre
				SERVOSet(servoLeft, spd2);
				SERVOSet(servoRight, spd1);
			}
			else if (a3 < t3)
			{	// Roter h�yre
				SERVOSet(servoLeft, spd1);
				SERVOSet(servoRight, spd3);
			}
			else if (a2 < t2)
			{	// Roter venstre
				SERVOSet(servoLeft, spd3);
				SERVOSet(servoRight, spd1);
			}
			else
			{	
				SERVOSet(servoLeft, spd1);
				SERVOSet(servoRight, spd1);
			}
	
		}
		SERVOSet(servoLeft, spd2);
		SERVOSet(servoRight, spd2);
		OSSleep(50);
	
	
		

}


void rampe()
{
	LCDPrintf("rampe\n");
	
	int count = 0;


	spd1=144;
	FollowLineOnCross(0); // h�yre
	
	SERVOSet(servoLeft, spd3);
	SERVOSet(servoRight, spd3);
	OSSleep(20);
	
	Stop();
	
	// Roter
	ResetEncoder();
	SERVOSet(servoLeft, 166);
	SERVOSet(servoRight, 100);
	while (GetEncoder(LEFT) < 6200)	{}
	Stop();
	
	// Hvis den kun ser hvitt
	if (AllWhite())
	{
		SERVOSet(servoLeft, 157);
		SERVOSet(servoRight, 110);
		
		while (AllWhite() || count < 50) { count++; OSSleep(1); }
	}

	spd1 = 152;
	SERVOSet(servoLeft, spd1);
	SERVOSet(servoRight, spd1);
	OSSleep(180);	// 150


	FollowLineOnEncoder(25000, 0); //25000
	spd1 = 144;
	FollowLineOnEncoder(9500, 0);
	
	//spd1 = 144;
	//FollowLineOnPort(0);
		
	Stop();
}


void tunnel()
{
	LCDPrintf("tunnel\n");

	DriveOnEncoder(12500, 144, 175);
	DriveOnEncoder(12500, 175, 144);
	DriveOnEncoder(5000, 200, 200);

	// Sving 180g buet til venstre
	ResetEncoder();
	SERVOSet(servoLeft, 130);
	SERVOSet(servoRight, 190);
	while (GetEncoder(RIGHT) < 14500)
	{}
	Stop();
	

	// Kj�r igjennom tunnel
	DriveOnEncoder(20000, 177, 166);

	
	// Sving til h�yre
	ResetEncoder();
	SERVOSet(servoLeft, 200);
	SERVOSet(servoRight, 150);
	while (GetEncoder(LEFT) < 1000)
	{}
	Stop();
	
	
	// Kj�r til strek er funnet
	SERVOSet(servoLeft, 166);
	SERVOSet(servoRight, 166);	
	while (AllWhite()) { OSSleep(1); }
	
	Stop();

}


void drititunnel()
{
	DriveOnEncoder(80000, 170, 166);

	LCDPrintf("notunnel\n");
	
	spd1 = 156;
	spd2 = 127;
	spd3 = 100;
	

	ResetEncoder();

	SERVOSet(servoLeft, spd1);
	SERVOSet(servoRight, spd3);
	while (GetEncoder(LEFT) < 4000)
	{
	}
	Stop();
		
		
		
		
		
	// Kj�r til strek er funnet
	SERVOSet(servoLeft, 172);
	SERVOSet(servoRight, 166);

	while(AllWhite()) { OSSleep(1); }

	Stop();
	
	//DriveOnEncoder(1000, 144,144);
	
	

	
	// sving til h�yre
	LCDPrintf("kjegle\n");

	ResetEncoder();

	SERVOSet(servoLeft, spd1);
	SERVOSet(servoRight, spd3);
	while (GetEncoder(LEFT) < 4000)
	{
	}
	Stop();

	// Kj�r til kross h�yre
	FollowLineOnCross(0);
	DriveOnEncoder(1000, 144,144);
	
	
	// sving ca 90 grader til h�yre
	LCDPrintf("kjegle\n");

	ResetEncoder();

	SERVOSet(servoLeft, spd1);
	SERVOSet(servoRight, spd3);
	while (GetEncoder(LEFT) < 4000)
	{
	}
	Stop();
	
	
	
				// Kj�r ut mot kjegler
				ResetEncoder();
				SERVOSet(servoLeft, spd1);
				SERVOSet(servoRight, spd1);
				while (GetEncoder(AVERAGE) < 12000)
				{					
				}
					Stop();
				
				
				
				// Rygg
				ResetEncoder();
				int encL = 0, encR = 0, encM = 0;
				SERVOSet(servoLeft, spd3);
				SERVOSet(servoRight, spd3);
				while (encM < 14000)
				{
					encL = GetEncoder(LEFT);
					encR = GetEncoder(RIGHT);
					
					if (encL < 0)
						encL *= -1;
					if (encR < 0)
						encR *= -1;
					
					encM = (encL + encR) / 2;
					
				}
					Stop();

	// sving ca 90 grader til h�yre
	LCDPrintf("kjegle\n");

	ResetEncoder();

	SERVOSet(servoLeft, spd1);
	SERVOSet(servoRight, spd3);
	while (GetEncoder(LEFT) < 5000)
	{
	}
	Stop();
	
	while (KEYRead() != KEY4)
	{
		FollowLine(0);
	}
}



void kjegle()
{
	
	// sving ca 90 grader til h�yre
	LCDPrintf("kjegle\n");
	
	spd1 = 156;
	spd2 = 127;
	
	ResetEncoder();

	SERVOSet(servoLeft, spd1);
	SERVOSet(servoRight, spd3);
	while (GetEncoder(LEFT) < 2500)
	{
	}
	Stop();
	
	LCDPrintf("followline\n");
	FollowLineOnEncoder(110000, 0);
	LCDPrintf("followoncross\n");
	FollowLineOnCross(0);

			
	
	// sving ca 90 grader til h�yre
	LCDPrintf("kjegle\n");

	ResetEncoder();

	SERVOSet(servoLeft, spd1);
	SERVOSet(servoRight, spd3);
	while (GetEncoder(LEFT) < 3700)
	{
	}
	Stop();
	
	
	DriveOnEncoder(25000, 154,152);
	
	
	
	// sving litt til venstre
	LCDPrintf("sving til venstre\n");
	ResetEncoder();
	SERVOSet(servoLeft, spd3);
	SERVOSet(servoRight, spd1);
	while (GetEncoder(RIGHT) < 2600)
	{

	}
	Stop();			
			
			
			
	DriveOnEncoder(30000, 155,152);
		
	
	
	// sving ca 90 grader til h�yre
	LCDPrintf("kjegle\n");

	ResetEncoder();

	SERVOSet(servoLeft, spd1);
	SERVOSet(servoRight, spd3);
	while (GetEncoder(LEFT) < 4200)
	{
	}
	Stop();
		
		
		
		
		
	// Kj�r til strek er funnet
	SERVOSet(servoLeft, 168);
	SERVOSet(servoRight, 166);

	while(AllWhite()) { OSSleep(1); }

	Stop();
	
	DriveOnEncoder(1000, 144,144);
	
	

	
	// sving til h�yre
	LCDPrintf("kjegle\n");

	ResetEncoder();

	SERVOSet(servoLeft, spd1);
	SERVOSet(servoRight, spd3);
	while (GetEncoder(LEFT) < 4000)
	{
	}
	Stop();

	// Kj�r til kross h�yre
	FollowLineOnCross(0);
	DriveOnEncoder(1000, 144,144);
	
	
	// sving ca 90 grader til h�yre
	LCDPrintf("kjegle\n");

	ResetEncoder();

	SERVOSet(servoLeft, spd1);
	SERVOSet(servoRight, spd3);
	while (GetEncoder(LEFT) < 4000)
	{
	}
	Stop();
	
	
	
				// Kj�r ut mot kjegler
				ResetEncoder();
				SERVOSet(servoLeft, spd1);
				SERVOSet(servoRight, spd1);
				while (GetEncoder(AVERAGE) < 12000)
				{					
				}
					Stop();
				
				
				
				// Rygg
				ResetEncoder();
				int encL = 0, encR = 0, encM = 0;
				SERVOSet(servoLeft, spd3);
				SERVOSet(servoRight, spd3);
				while (encM < 11500)
				{
					encL = GetEncoder(LEFT);
					encR = GetEncoder(RIGHT);
					
					if (encL < 0)
						encL *= -1;
					if (encR < 0)
						encR *= -1;
					
					encM = (encL + encR) / 2;
					
				}
					Stop();

	// sving ca 90 grader til h�yre
	LCDPrintf("kjegle\n");

	ResetEncoder();

	SERVOSet(servoLeft, spd1);
	SERVOSet(servoRight, spd3);
	while (GetEncoder(LEFT) < 4000)
	{
	}
	Stop();
	
	while (KEYRead() != KEY4)
	{
		FollowLine(0);
	}
	
}


















void tunnel2()
{
	int irleft = 0;
	//int encR = 0, encL = 0, encM = 0;
	
	// Kj�r rett frem til tunnel er til venstre
	SERVOSet(servoLeft, 158);
	SERVOSet(servoRight, 156);
	while (irleft < 330)
	{
		irleft = irGetDistance(LEFT);
		LCDPrintf("IR: %d\n", irleft);
	}
	Stop();

	
	// Kj�r frem til tunnel er borte
	SERVOSet(servoLeft, 158);
	SERVOSet(servoRight, 156);
	while (irleft >= 330)
	{
		irleft = irGetDistance(LEFT);
		LCDPrintf("IR: %d\n", irleft);
	}
	Stop();
	
	
	// Kj�r litt ekstra frem
	DriveOnEncoder(2500, 157, 157);
	
	
	// sving ca 90 grader til venstre
	LCDPrintf("sving til venstre\n");
	spd1 = 156;
	ResetEncoder();
	SERVOSet(servoLeft, spd3);
	SERVOSet(servoRight, spd1);
	while (GetEncoder(RIGHT) < 3700) { OSSleep(1); }
	Stop();
	
	
	// Kj�r rett frem til tunnel er til venstre
	SERVOSet(servoLeft, 158);
	SERVOSet(servoRight, 156);
	while (irleft < 330)
	{
		irleft = irGetDistance(LEFT);
		LCDPrintf("IR: %d\n", irleft);
	}
	Stop();

	
	// Kj�r frem til tunnel er borte
	SERVOSet(servoLeft, 158);
	SERVOSet(servoRight, 156);
	while (irleft >= 330)
	{
		irleft = irGetDistance(LEFT);
		LCDPrintf("IR: %d\n", irleft);
	}
	Stop();
	
	
	// Kj�r litt ekstra frem
	DriveOnEncoder(2500, 157, 157);


	// Kj�r rett frem til tunnel er til venstre
	SERVOSet(servoLeft, 158);
	SERVOSet(servoRight, 156);
	while (irleft < 330)
	{
		irleft = irGetDistance(LEFT);
		LCDPrintf("IR: %d\n", irleft);
	}
	Stop();

	
	// Kj�r frem til tunnel er borte
	SERVOSet(servoLeft, 158);
	SERVOSet(servoRight, 156);
	while (irleft >= 330)
	{
		irleft = irGetDistance(LEFT);
		LCDPrintf("IR: %d\n", irleft);
	}
	Stop();

}




























void tiltrapp2()
{
	LCDPrintf("til trapp\n");

	int encL = 0, encR = 0, encM = 0;

	// kj�r til port p� rampe
	spd1 = 144;
	spd2 = 127;
	
	//FollowLineOnPort(1);
	ResetEncoder();
	while (irGetDistance(LEFT) < 350)
	{
		FollowLine(1);
	}


	spd1 = 156;
	spd2 = 127;
	
	
	ResetEncoder();
		encM = 0;
		
		SERVOSet(servoArm,0);
		
		LCDPrintf("til midten \n");
		while (encM < 37500)
		{
			encL = GetEncoder(LEFT);
			encR = GetEncoder(RIGHT);
			encM = (encL + encR) / 2;
			
			// Leser sensorer
			a2 = OSGetAD(2); // venstre
			a3 = OSGetAD(3); // h�yre
			a4 = OSGetAD(4); // venstre midt
			a5 = OSGetAD(5); // h�yre midt
			a6 = OSGetAD(6); // midt
	
			// Kj�rer
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
			{	// Sving h�yre
				SERVOSet(servoLeft, spd1);
				SERVOSet(servoRight, spd2);
			}
			else
			{	
				SERVOSet(servoLeft, spd1);
				SERVOSet(servoRight, spd1);
			}
	
		}
		Stop();
		LCDPrintf("pa midten\n");
		
		
		ResetEncoder();
		encM = 0;
	
		// Kj�r ned trapp
		SERVOSet(servoLeft, 152);
		SERVOSet(servoRight, 152);
		while (encM < 50000)
		{
			encL = GetEncoder(LEFT);
			encR = GetEncoder(RIGHT);
			encM = (encL + encR) / 2;
		}
			Stop();
		
		
		
		
		//kj�r til kjegle port
		
		FollowLineOnEncoder(10000, 1);
		
		t2 = 315;
		FollowLineOnCross(1);
		t2 = 250;
		
		
			DriveOnEncoder(1000, 144,144);
		
		
			// sving ca 90 grader til venstre
			LCDPrintf("sving til venstre\n");
			ResetEncoder();
			encR = 0;
			SERVOSet(servoLeft, spd3);
			SERVOSet(servoRight, spd1);
			while (encR < 3700)
			{
				encR = GetEncoder(RIGHT);
			}
			SERVOSet(servoLeft, spd2);
			SERVOSet(servoRight, spd2);
			OSSleep(50);
			
			
			
			// Kj�r ut mot kjegler
			ResetEncoder();
			encM = 0;
			SERVOSet(servoLeft, spd1);
			SERVOSet(servoRight, spd1);
			while (encM < 12000)
			{
				encL = GetEncoder(LEFT);
				encR = GetEncoder(RIGHT);
				encM = (encL + encR) / 2;
				
			}
				Stop();
			
			
			
			// Rygg
			ResetEncoder();
			encM = 0;
			SERVOSet(servoLeft, spd3);
			SERVOSet(servoRight, spd3);
			while (encM < 11650)
			{
				encL = GetEncoder(LEFT);
				encR = GetEncoder(RIGHT);
				
				if (encL < 0)
					encL *= -1;
				if (encR < 0)
					encR *= -1;
				
				encM = (encL + encR) / 2;
				
			}
				Stop();
		
		
			// sving ca 90 grader til venstre
			LCDPrintf("sving til venstre\n");
			ResetEncoder();
			encR = 0;
			SERVOSet(servoLeft, spd3);
			SERVOSet(servoRight, spd1);
			while (encR < 3700)
			{
				encR = GetEncoder(RIGHT);
			}
				Stop();
		
		/*
		// Sving til h�yre
		SERVOSet(servoLeft, 166);
		SERVOSet(servoRight, 127);
		OSSleep(250);
		*/
		
		spd1 = 160;
		spd2 = 127;
		// Kj�r opp rampa igjen
		ResetEncoder();
		encM = 0;
		while (encM < 120000)
		{
			encL = GetEncoder(LEFT);
			encR = GetEncoder(RIGHT);
			encM = (encL + encR) / 2;
	
			// Leser sensorer
			a2 = OSGetAD(2); // venstre
			a3 = OSGetAD(3); // h�yre
			a4 = OSGetAD(4); // venstre midt
			a5 = OSGetAD(5); // h�yre midt
			a6 = OSGetAD(6); // midt
	
			// Kj�rer
			if (a4 < t4)
			{	// Sving venstre
				SERVOSet(servoLeft, spd2);
				SERVOSet(servoRight, spd1);
			}else if (a5 < t5)
			{	// Sving h�yre
				SERVOSet(servoLeft, spd1);
				SERVOSet(servoRight, spd2);
			}
			
			else if (a2 < t2)
			{	// Roter venstre
				SERVOSet(servoLeft, spd3);
				SERVOSet(servoRight, spd1);
			}else if (a3 < t3)
			{	// Roter h�yre
				SERVOSet(servoLeft, spd1);
				SERVOSet(servoRight, spd3);
			}
			
			else
			{	
				SERVOSet(servoLeft, spd1);
				SERVOSet(servoRight, spd1);
			}
	
		}
			Stop();
	
		

}
