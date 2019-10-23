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

// Prints a formatted std::string to the VEX Brain screen
void println( const char* c_str )
{
  Brain.Screen.print( c_str );
  Brain.Screen.newLine();
}

// Stamps down and raises the blocks
void raise_blocks(){
    vex::task::sleep( 3000 );
    // Open the Door
    CamMotor.spinTo(90,vex::rotationUnits::deg, true );
    // Stamp downt the blocks
    BlockMotor.setVelocity(40,velocityUnits::pct);
    BlockMotor.spin(directionType::fwd);
    wait(1.5,vex::timeUnits::sec);
    BlockMotor.stop();
    // Pick up new blocks
    BlockMotor.spin(directionType::rev);
    wait(4,vex::timeUnits::sec);
    BlockMotor.stop();
    // Shut the door
    CamMotor.spinTo(0, vex::rotationUnits::deg,true);
    return;
}

int main() {
  // Brain.Screen.print("TurnyTurny Program has Started.");
  // Brain.Screen.newLine();

  println( "TurnyTurny Program has Started." );

  dt.setVelocity(20, velocityUnits::pct);
  vex::task::sleep(4500);

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

  // drive past starting square (for now 13 is an arbitrary value that gets us past the square. Probably need to use the line sensors to determine when we've passed the square)
  dt.driveFor(directionType::fwd, 13, distanceUnits::in );

  // go down center line and search for bins
  while ( true )
  {
    Brain.Screen.newLine();

    // stop at a cross-mark
    if ( line_tracker_left.sees_line() && line_tracker_right.sees_line() )
    {
      dt.stop();
      break;
    }
    else 
    {
      dt.drive(directionType::fwd);
    }
  }

  // need to back up a slight bit in order for the front wheels to not collide with the bin wall when turning in
  dt.driveFor( directionType::rev, 3.5, distanceUnits::in );

  LeftMotor.spinFor( 235*2, vex::rotationUnits::deg );

  vex::task::sleep(500);

  // for now using a distance marker to know how far to back out
  double dist = ultra.distance(distanceUnits::in);
  
  while( ultra.distance(distanceUnits::in) > 3.4 )
  {
    dt.drive(directionType::fwd);
  }
  dt.stop();
  vex::task::sleep(3000);

  while( ultra.distance(distanceUnits::in) < dist )
  {
    dt.drive(directionType::rev);
  }
  dt.stop();

  LeftMotor.spinFor( -233*2, vex::rotationUnits::deg );
}
