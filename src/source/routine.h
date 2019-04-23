#define TICK_ERROR_MARGIN 100
enum State {
  START,
  SEESAW_DOWN,
  SEESAW_UP,
  AXE,
  END
}

State state    = START;
long long tick = 0;
int tickError  = 0;
int robotSpeed = 0;

void m(){

  /* Main loop  */
  while( true ){
    switch (state) {
      case START:{
        runRoutinesBasic(&startRoutine, &startUpdateStatus);
        break;
      }
    }
  }
}

void runRoutinesAdvanced( int (*perfRoutine)(), void (*updStat)(), int (*errCon)(), void (*fallback)() ){
  if( errCon() != 0 ) ++tickError;
  else tickError = 0;

  if( tickError > TICK_ERROR_MARGIN ){
    fallback();
  }
  else {
    int returnCode = perfRoutine();
    if( returnCode != 0 ){
      fallback();
    }
  }

  updStat();
  ++tick;
}

void runRoutinesBasic( int (*perfRoutine)(), void (*updStat)() ){
  perfRoutine();
  updStat();
  ++tick;
}

int noError(){
  return 0;
}

void noFallback(){}
