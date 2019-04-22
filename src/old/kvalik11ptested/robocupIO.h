#define FRONT 2
#define LEFT 4
#define RIGHT 3

/*
 dig ut
 0 - IR lys
 
 analog in
 2 - IR front
 3 - IR right 
 4 - IR left
 
*/

int activeIR=0;

int getDistance(int irID)
{
	return (int)OSGetAD(irID);
}
