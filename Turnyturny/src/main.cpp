/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Mon Mar 25 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
// MOTORS
vex::motor RightMotor = vex::motor( vex::PORT1, true );
vex::motor LeftMotor = vex::motor( vex::PORT10, false );
vex::drivetrain dt( LeftMotor, RightMotor ); 

// SENSORS
vex::line line_tracker_left( Brain.ThreeWirePort.G );
vex::line line_tracker_right( Brain.ThreeWirePort.H );
vex::sonar ultra(Brain.ThreeWirePort.A);
vex::bumper bumpy( Brain.ThreeWirePort.F );

constexpr int LINE_ANALOG_PCT = 65;

bool over_line( vex::line& line_tracker ) // TODO: Make classes for each sensor
{
  return line_tracker.value( analogUnits::pct ) <= LINE_ANALOG_PCT;
}

// Prints a formatted std::string to the VEX Brain screen
void println( const char* c_str )
{
  Brain.Screen.print( c_str );
  Brain.Screen.newLine();
}

int main() {
  // Brain.Screen.print("TurnyTurny Program has Started.");
  // Brain.Screen.newLine();

  println( "TurnyTurnt Program has Started." );

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
    if ( over_line( line_tracker_left ) && over_line( line_tracker_right ) )
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
