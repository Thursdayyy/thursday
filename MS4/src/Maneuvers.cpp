#include "Maneuvers.h"

const double creep_offsets[8] = { 2.4, 2.3, 2.2, 2.3, 1.9, 1.9, 2.2, 1.7 };
const double turn_angles[8] = { 56, 57, 57, 58, 58, 58, 60, 58 };

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
void TurnIntoBin( double creepin, double left_turn_angle )
{
  dt.setDriveVelocity(CREEP_SPEED, PUNITS);
  dt.drive(fwd);
  while ( !line_tracker_back_right.sees_line() && !line_tracker_back_left.sees_line() )
    Sleep(40);

  Creep(creepin);

  dt.stop();

  OpenDoor();

  dt.setTurnVelocity(CREEP_SPEED, PUNITS);
  dt.turnFor(-left_turn_angle, vex::rotationUnits::deg); // negative because it's a left turn
  dt.setTurnVelocity(YAW_SPEED, PUNITS);

  return;

}

//==================================================================================================================
void ApproachWall()
{
  dt.setDriveVelocity(10, PUNITS);
  
  int old_dist = 0;
  int repeats = 0;
  while (ultra.distance(DUNITS) > 1.4) {

    int new_dist = ultra.distance(DUNITS);

    if (new_dist <= old_dist + .3 && new_dist >= old_dist - .3) {
      repeats++;
    }
    else {
      repeats = 0;
    }

    if (repeats == 30) {
      return;
    }

    dt.drive(fwd);
    Sleep(50);

    old_dist = new_dist;
  }


  dt.stop();

  ResumeDriveSpeed();
}

//==================================================================================================================
void ReturnToLine()
{
  while ( !line_tracker_back_right.sees_line()) {
    dt.drive( directionType::rev );
    vex::task::sleep(10);
  }

  dt.stop();

  Creep(0.1);

  dt.setTurnVelocity(CREEP_SPEED, PUNITS);

  dt.turn(turnType::right);
  while (!line_tracker_left.sees_line()) {
    vex::task::sleep(50);
  }

  dt.turnFor(-5, rotationUnits::deg);

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

  dt.turnFor(100, rotationUnits::deg);

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

  CreepReverse(7);
  dt.stop();
}

//==================================================================================================================
void ButtonDrop()
{
  dt.setDriveVelocity(20, PUNITS);
  // drop off the button assembly
  dt.drive(directionType::rev);
  Sleep(3000);
  dt.stop();
  Sleep(5000);

  dt.setDriveVelocity(5, PUNITS);

  // RightMotor.spinFor(0.5, timeUnits::sec);

  KeepScooting();

  ResumeDriveSpeed();
  return;
}