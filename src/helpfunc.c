// f�lg linje og stopp p� enkoder
// f�lg linje og stopp p� tid
// f�lg linje og stopp p� port
// f�lg linje og stopp p� kryss

void DriveOnEncoder(int tics)
{
	Stop();
	ResetEncoder();

	SERVOSet(servoLeft, spd1);
	SERVOSet(servoRight, spd1);

	while (GetEncoder(AVERAGE) < tics)
	{
		OSSleep(1);
	}

	Stop();
	return;
}

void FollowLineOnEncoder(int tics, int lr)
{
	Stop();
	ResetEncoder();

	while (GetEncoder(AVERAGE) < tics)
	{
		FollowLine(lr);
		OSSleep(1);
	}

	Stop();
	return;
}

void DriveOnTime(int time)
{
	int counter = 0;
	Stop();

	SERVOSet(servoLeft, spd1)
	SERVOSet(servoRight, spd1);

	while (counter < time)
	{
		counter++;
		OSSleep(1);
	}

	Stop();
	return;
}

void FollowLineOnTime(int time, int lr)
{
	int counter = 0;
	Stop();
	ResetEncoder(1);

	while (counter < time)
	{
		FollowLine(lr);
		counter++;
		OSSleep(1);
	}

	Stop();
	return;
}
