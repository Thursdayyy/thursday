#include "PortConfig.h"
#include "Blocks.h"

void SearchForCrossMark();
void TurnIntoBin();
void ApproachWall();
void ReturnToLine();
void Park( const int cross_marks );
void ChaChaRealSmooth();
void ThatsAWrapFolks();
void ButtonDrop();

//==================================================================================================================
void SearchForCrossMark() // TODO: maybe add a flag to decide to continue or stop at a cross mark
{
  const int vel = VROOM_SPEED;
  const double vel_offset = .2;
  const int delay = 70;
  double i = 0;

  dt.setDriveVelocity(vel, pct);
  dt.drive(fwd);

  // go down center line and search for bins
  while ( true )
  {
      if ( line_tracker_left.sees_line() && line_tracker_right.sees_line() ) // 1 1
      {
        return;
      }

      if ( line_tracker_left.sees_line() && !line_tracker_right.sees_line() ) // 1 0
      {
        i += vel_offset;
        RightMotor.setVelocity( vel + i, PUNITS );
      }
      else if ( !line_tracker_left.sees_line() && line_tracker_right.sees_line() ) // 0 1
      {
        i += vel_offset;
        LeftMotor.setVelocity( vel + i, PUNITS );
      }
      else if ( !line_tracker_left.sees_line() && !line_tracker_right.sees_line() ) { // 0 0
        i = 0;
        LeftMotor.setVelocity( vel, PUNITS );
        RightMotor.setVelocity( vel, PUNITS );
      }

    vex::task::sleep( delay );
  }
}

//==================================================================================================================
void TurnIntoBin()
{
    while ( !line_tracker_back_right.sees_line() )
    {
      dt.drive(fwd);
      vex::task::sleep(40);
    }

    Creep(2.5);
    dt.stop();

    OpenDoor();

    // IDEA: record the movements made to perform the turn into the bin and reverse that movement to exit the bin
    dt.turnFor(-58, vex::rotationUnits::deg); // TODO: change this absolute value into something more consistent
    return;

    // dt.setTurnVelocity(8, PUNITS);
    // while( !line_tracker_back.sees_line() )
    // {
    //   dt.turn(turnType::left);
    //   vex::task::sleep(20);
    // }
    // dt.turnFor(-4, RUNITS);
    // while( line_tracker_back.sees_line() )
    // {
    //   dt.turn(turnType::left);
    //   vex::task::sleep(20);
    // }
    // dt.turnFor(-15, RUNITS);
    // dt.stop();
    // dt.setTurnVelocity(YAW_SPEED, PUNITS);
    
    //vex::task::sleep(5000);
}

//==================================================================================================================
void ApproachWall()
{
  dt.setDriveVelocity(10, PUNITS);
  dt.drive(fwd);

  Forward(16);

  dt.stop();

  ResumeDriveSpeed();
}

//==================================================================================================================
void ReturnToLine()
{
  while ( !line_tracker_back_right.sees_line()) {
    dt.drive( directionType::rev );
    vex::task::sleep(100);
  }

  dt.stop();

  Creep(.5);

  dt.setTurnVelocity(5, PUNITS);

  while (!line_tracker_left.sees_line()) {
    dt.turn(turnType::right);
    vex::task::sleep(50);
  }

  dt.turnFor(-4, rotationUnits::deg);

  dt.setTurnVelocity( YAW_SPEED, PUNITS );
}

//==================================================================================================================
void Park( const int cross_marks )
{

  int seen = 0;
  while (seen < cross_marks) {
    SearchForCrossMark();
    Forward(2.5);
    seen++;
  }

  while (true) { // TODO: replace this code with SearchForCrossMark()
    dt.drive(fwd);

    if (line_tracker_left.sees_line() && line_tracker_right.sees_line()){
       break;
     }

  }

  dt.stop();
  Forward(7);
}

//=================================================================================================================
void ChaChaRealSmooth()
{

  dt.setTurnVelocity(YAW_SPEED, PUNITS);

  dt.turnFor(100, rotationUnits::deg); // TODO: use line sensor to determine if turn is complete instead of absolute

  while( !line_tracker_left.sees_line() )
     dt.turn(turnType::right);

  dt.turnFor(-4, rotationUnits::deg);
}

//==================================================================================================================
void ThatsAWrapFolks()
{
  dt.setDriveVelocity(VROOM_SPEED/2, PUNITS);
 
  while(line_tracker_back_left.sees_line() && line_tracker_back_right.sees_line()) // Need to back up further to touch the wall
  {
    dt.drive(directionType::rev);
  }

  CreepReverse(5);
  dt.stop();
}

//==================================================================================================================
void ButtonDrop()
{
  dt.setDriveVelocity(5, PUNITS);
  // drop off the button assembly
  while(line_tracker_back_left.sees_line() && line_tracker_back_right.sees_line()) // Need to back up further to touch the wall
  {
    dt.drive(directionType::rev);
  }

  CreepReverse(1);
  ResumeDriveSpeed();

  dt.stop();
  vex::task::sleep(3000);

  KeepScooting();
}