#define SLOW 0.15f
#define REGULAR_SPEED 0.20f
#define FAST 0.30f
#define STILL 0.0f

#define TURN_LEFT -0.30f
#define TURN_RIGHT 0.30f
#define NO_TURN 0.0f

#define MCYCLE 1000


void taskGylotin()
{
  resetEncoders();
	LCDPrintf("\r\n Gylotin");
	driveFollowLine( 200 * MCYCLE, REGULAR_SPEED           );	// litt forbi gylotin
	driveFollowLine( 100 * MCYCLE, REGULAR_SPEED           );	// litt opp rampe
}

void taskVippeport()
{
  resetEncoders();
	LCDPrintf("\r\n Vippeport");
  driveToCross   ( 200 * MCYCLE, REGULAR_SPEED, LEFT     );
	// //sving til vippeport og kjør ned
	drive          ( 5   * MCYCLE, REGULAR_SPEED, NO_TURN  );
	turn           ( 10  * MCYCLE, TURN_LEFT               );
	driveFollowLine( 103 * MCYCLE, SLOW                    );
	drive          ( 2   * MCYCLE, -SLOW,         NO_TURN  );
	// // kjør i blinde til strek foran trapp
	OSWait(100);
	drive          ( 10  * MCYCLE, REGULAR_SPEED, NO_TURN  );
	turn           ( 8.8 * MCYCLE, TURN_RIGHT              );
	drive          ( 40  * MCYCLE, REGULAR_SPEED, NO_TURN  );
	OSWait(100);

  driveToLine    ( 15  * MCYCLE, REGULAR_SPEED           );
	// // ved strek, sving venstre og følg til neste kryss
	drive          ( 1   * MCYCLE, REGULAR_SPEED, NO_TURN  );
	turn           ( 8   * MCYCLE, TURN_LEFT               );
  driveRaw(-0.15, 0.0f);
  OSWait(170);

  drive          ( 15  * MCYCLE, REGULAR_SPEED, NO_TURN  );
  driveRaw(0.25f, 0.15f);
  //drive( 22 * MCYCLE, 0.25f, 0.15f );
  OSWait(220);
  stop();

  drive          ( 3   * MCYCLE, REGULAR_SPEED, NO_TURN  );
  turn           ( 1   * MCYCLE, TURN_RIGHT              );
}

void taskOpprampe()
{
  resetEncoders();
	LCDPrintf("\r\n Opp rampe");
  driveFollowLine( 110 * MCYCLE, FAST                    );
	driveFollowLine( 40  * MCYCLE, SLOW                    );
	turn           ( 4   * MCYCLE, TURN_RIGHT              );
	drive          ( 5   * MCYCLE, REGULAR_SPEED, NO_TURN  );
	driveToLine    ( 10  * MCYCLE, REGULAR_SPEED           );
	turn           ( 6.7 * MCYCLE, TURN_RIGHT              );

	LCDPrintf("\r\n ned trapp");
	driveFollowLine( 35 * MCYCLE,  SLOW                    );
	driveRaw(-0.2, 0.0f);
	OSWait(50);

  int i;
  for( i = 0; i < 4; i++ ){
    driveFollowLine( 22 * MCYCLE, SLOW                   );
    driveRaw( -0.2, 0.0f );
  	OSWait(50);
  }
  driveFollowLine( 40 * MCYCLE, SLOW                     );
}

void taskTrapptilMal()
{
	driveFollowLine( 42 * MCYCLE, SLOW                     );
	OSWait(100);

  turn           ( 8   * MCYCLE, TURN_RIGHT              );
	drive          ( 30  * MCYCLE, REGULAR_SPEED, NO_TURN  );
	OSWait(100);

	turnToDistance(FRONT, 200);
	OSWait(100);

	drive          ( 50 * MCYCLE, REGULAR_SPEED,  NO_TURN  );


}
