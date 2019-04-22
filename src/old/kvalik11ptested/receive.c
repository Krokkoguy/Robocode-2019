/*

	Kode som leser alle tegn som blir sendt til Eyeboten via seriellport 2
	og skriver tegnene ut til Eyebotens LCD-panel
	Av Sizarta Sarshar
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "eyebot.h"

#define BASE_SERIAL SERIAL3

int main() {

	char c;


	OSInitRS232(SER57600, NONE, BASE_SERIAL);

	LCDPrintf("Started.\r\n");


	while(1)
	{
		if(OSRecvRS232(&c, BASE_SERIAL) == 0)
		{
			c = (char)tolower(c);
			LCDPrintf("%c",c);
		}
	}


	return 0;

}


