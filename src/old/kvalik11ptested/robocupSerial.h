#define BASE_SERIAL SERIAL2

void initSerial()
{
	OSInitRS232(SER115200, NONE, BASE_SERIAL);
}

void writeStringToSerial(char dataString[]) 
{
	int i=0;
	while(dataString[i]) {
        OSSendRS232(&(dataString[i]), BASE_SERIAL);
		i++;
	}
}

void sendImageOverSerial(unsigned char data[], int sizeX, int sizeY)
{
	int x, y;
	for(y=0; y<sizeY; y++) {
		for(x=0; x<sizeX; x++) {
			OSSendCharRS232(data[y*sizeX+x], BASE_SERIAL);
		}
	}
}
