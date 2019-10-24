/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Mon Mar 25 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

#include "LineTracker.h"
#include "PortConfig.h"

using namespace vex;

//FUNCTIONS

// Prints a formatted std::string to the VEX Brain screen
//=================================================================================================================
void println( const char* c_str )
{
  Brain.Screen.print( c_str );
  Brain.Screen.newLine();
}

// Stamps down and raises the blocks
//==================================================================================================================
void RaiseBlocks()
{
    vex::task::sleep( 1000 );
    // Shut the door
    CamMotor.spinTo(0, vex::rotationUnits::deg,true);
    // Stamp down the blocks
    BlockMotor.setVelocity(100, velocityUnits::pct);
    BlockMotor.spin(directionType::rev);

    wait(1.5, vex::timeUnits::sec);
    
    BlockMotor.stop();
    
    // Pick up new blocks
    BlockMotor.spin(directionType::fwd);
    wait(2, vex::timeUnits::sec);
    
    BlockMotor.stop();
    DoorOpen = false;
    return;
}

//==================================================================================================================
void RevThoseEngines()
{
  while (!bumpy.pressing())
    ;

  ticky.clear();

  task::sleep(2000);
  return;
}

//==================================================================================================================
void ButtonDrop()
{
  const double vel = 20;
  //Caroline's VEX made her change this from setVelocity
  dt.setDriveVelocity(vel, velocityUnits::pct);

  // drop off the button assembly
  while(true)
  {
    if( !bumpy.pressing() )
    {
      dt.drive(directionType::rev);
    }
    else {
      dt.stop();
      vex::task::sleep(3000);
      break;
    }
  }

  // move past the starting square
  while ( line_tracker_left.sees_line() && line_tracker_right.sees_line() )
  {
    dt.drive(fwd);
  }
}

//==================================================================================================================
void SearchForCrossMark()
{
  const int vel = 20;
  double i = 0;
  const double vel_offset = .3;

  dt.setDriveVelocity(vel, pct);
  dt.drive(fwd);

  // go down center line and search for bins
  while ( true )
  {
      if ( line_tracker_left.sees_line() && line_tracker_right.sees_line() ) // 1 1
      {
        dt.stop();

        return;
        //continue;
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

    vex::task::sleep(70);
  }
}

//==================================================================================================================
void BackItUp( double distance )
{
  dt.driveFor( directionType::rev, distance, DUNITS );
}

//==================================================================================================================j
void Forward( double distance )
{
  dt.driveFor( directionType::fwd, distance, DUNITS );
}

//==================================================================================================================
void Park()
{

  int seen = 0;
  while (seen < 1) {
    SearchForCrossMark();
    Forward(1);
    seen++;
  }

  while (true) {
    dt.drive(fwd);

    if (line_tracker_left.sees_line() && line_tracker_right.sees_line()){
       break;
     }

  }

  dt.stop();
  Forward(2);

  return;
}

//==================================================================================================================
void TurnIntoBin()
{
    // Forward( 7.5 );
    while ( !line_tracker_back.sees_line() )
    {
      dt.drive(fwd);
      vex::task::sleep(40);
    }

    Forward(2);
    dt.stop();

    //Make sure door is open
    if (DoorOpen == false){
      DoorOpen = true;
      CamMotor.spinTo(90, vex::rotationUnits::deg,true);
    }

    // IDEA: record the movements made to perform the turn into the bin and reverse that movement to exit the bin
    dt.turnFor(-60, vex::rotationUnits::deg); // TODO: change this absolute value into something more consistent
}

//==================================================================================================================
void ApproachWall()
{
    dt.setDriveVelocity(10, PUNITS);
    dt.drive(fwd);

    Forward(16);
    // while (ultra.distance(DUNITS) > 1.8) {
    //   vex::task::sleep(50);
    // }

    dt.stop();

    dt.setDriveVelocity( VROOM_SPEED, PUNITS );
}

//==================================================================================================================
void ReturnToLine()
{
  while ( !line_tracker_back.sees_line()) {
    dt.drive( directionType::rev );
    vex::task::sleep(50);
  }

  dt.stop();

  Forward(1);

  dt.setTurnVelocity(5, PUNITS);

  while (!line_tracker_left.sees_line()) {
    dt.turn(turnType::right);
    vex::task::sleep(50);
  }

  dt.turnFor(-4, rotationUnits::deg);

  dt.setTurnVelocity( YAW_SPEED, PUNITS );
}

void ChaChaRealSmooth() {

  dt.setTurnVelocity(10, PUNITS);
  dt.turnFor(115, rotationUnits::deg);

  dt.setDriveVelocity(5, PUNITS);
  while (!bumpy.pressing()){
    dt.drive(directionType::rev);
  }
  dt.stop();

  return;
}

//==================================================================================================================
int main()
{
  RevThoseEngines();

  dt.setDriveVelocity( VROOM_SPEED, velocityUnits::pct);
  dt.setTurnVelocity( YAW_SPEED, PUNITS);

  //ButtonDrop();

  int bins = 0;
  while ( bins++ < 3 && ticky.time(timeUnits::sec) < 160 ) {
    SearchForCrossMark();

    TurnIntoBin();

    ApproachWall();

    RaiseBlocks();

    ReturnToLine();
  }

  Park();

  ChaChaRealSmooth();
}