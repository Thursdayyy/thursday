#pragma once

#include "LineTracker.h"
#include "PortConfig.h"

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

// void ResumeDriveSpeed();
// void Forward( double distance );
// void Reverse( double distance );
// void Creep( double distance );
// void CreepReverse( double distance );
// void KeepScooting(); // drives forward until the forward line sensors no longer see white. Assumes the robot starts on white.