int camera;  /* camera version */

image camimage1, camimage2; 
image diffimage;


/** print error message and exit */
void error(char *str) {
	LCDPrintf("ERROR: %s\n",str);
	OSWait(200);
	exit(0);
}

// Teller ant pixels i et bilde
int pixelCount(image img, int terskel)
{
	int i, j;
	int count = 0;
	for (i = 2; i < 80; i++)
	{
		for (j = 2; j < 60; j++)
		{
			if (img[i][j] < terskel)
			{
				count++;
			}
		}
	}
	return count;
}

// initialiserer camera, avslutter ved feil!
void initCamera()
{
	camera = CAMInit(NORMAL);
	if(camera == NOCAM) {
		error("No camera!\n");
	} else if(camera == INITERROR) {
		error("CAMInit!\n");
	}
	
	CAMGetFrame(&camimage1);	// Ta testbilde
	LCDPutGraphic(&camimage1);
}

// sjekker om port blinker, 
// return 1 hvis ja, 0 hvis nei
int lysport(int vent, int antpx)
{
	LCDClear();
	LCDPrintf("Bilde 1\r\n");
	//OSWait(vent);
	CAMGetFrame(&camimage1);	// Ta bilde 1
	LCDPutGraphic(&camimage1);
	
	LCDPrintf("Bilde 2\r\n");
	OSWait(vent);				// Vent 
	CAMGetFrame(&camimage2);	// Ta bilde 2
	LCDPutGraphic(&camimage2);
	
	//OSWait(vent);
	IPDiffer(&camimage1, &camimage2, &diffimage);
	LCDPutGraphic(&diffimage);
	
	int px;
	px = pixelCount(diffimage, 230);
	LCDPrintf("Diff px: %d", px);
	
	if (px > antpx)	// lyser
	{
		AUTone(1200, 100);
		OSWait(11);
		AUTone(1100, 100);
		OSWait(11);
		return 1;
	} else			// lyser ikke
	{
		AUTone(1000, 100);
		OSWait(11);
		return 0;
	}
}




