#include "Driving.h"

// CONSTANTS
const double VROOM_SPEED = 15;
const double YAW_SPEED = 12;
const double CREEP_SPEED = 8;

//==================================================================================================================
void RevThoseEngines()
{
  while (!bumpy.pressing())
    ;

  while ( bumpy.pressing() ) // wait until the button is released to begin
    ;
  task::sleep(200);
}

//==================================================================================================================
void ResumeDriveSpeed()
{
  dt.setDriveVelocity( VROOM_SPEED, PUNITS);
}

//==================================================================================================================
void Forward( double distance ) // TODO: make it accellerate to max speed instead of immediately starting full speed to prevent jerking
{
  dt.driveFor( directionType::fwd, distance, DUNITS );
}

//==================================================================================================================
void Reverse( double distance ) // TODO: make it accellerate to max speed instead of immediately starting full speed to prevent jerking
{
  dt.driveFor( directionType::rev, distance, DUNITS );
}

//==================================================================================================================
void Sleep( double sleep_time )
{
  vex::task::sleep( sleep_time );
}

//==================================================================================================================
void Creep( double distance )
{
  dt.setDriveVelocity( CREEP_SPEED, PUNITS );
  Forward( distance );
  ResumeDriveSpeed();
}

//==================================================================================================================
void CreepReverse( double distance )
{
  dt.setDriveVelocity( CREEP_SPEED, PUNITS );
  Reverse( distance );
  ResumeDriveSpeed();
}

//==================================================================================================================
void KeepScooting()
{
  // move past the starting square
  while ( line_tracker_left.sees_line() && line_tracker_right.sees_line() )
  {
    dt.drive(fwd);
  }
}

void CorrectForDropOff(){

  Forward(1);
  dt.setTurnVelocity(5, PUNITS);
  dt.turn(turnType::left);

  while (!line_tracker_right.sees_line()) {
    Sleep(50);
    continue;
  }

  dt.turnFor(6, RUNITS);

}