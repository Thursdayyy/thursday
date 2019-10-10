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
vex::motor RightMotor   = vex::motor( vex::PORT1, true );
vex::motor LeftMotor  = vex::motor( vex::PORT10, false );
vex::line line_tracker_left( Brain.ThreeWirePort.G );
vex::line line_tracker_right( Brain.ThreeWirePort.H );

vex::drivetrain dt( LeftMotor, RightMotor ); 
vex::sonar ultra(Brain.ThreeWirePort.A);

vex::bumper bumpy( Brain.ThreeWirePort.F );

bool see_white_line( int value ) {
  return value <= 65;
}

void println( const char* string )
{
  Brain.Screen.print(string);
  Brain.Screen.newLine();
}

int main() {
  // Brain.Screen.print("TurnyTurny Program has Started.");
  // Brain.Screen.newLine();

  println( "TurnyTurnt Program has Started." );

  // while(true)
  // {
  //   Brain.Screen.print("%f", ultra.distance(distanceUnits::in));
  //   Brain.Screen.newLine();
  // }

  vex::task::sleep(4500);

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

  dt.setVelocity(20, velocityUnits::pct);

  dt.driveFor(directionType::fwd, 13, distanceUnits::in );

  while ( true )
  {
    // Brain.Screen.print("sensor value:%d", ultra.value());
    // Brain.Screen.newLine();
    Brain.Screen.newLine();
    if ( see_white_line( line_tracker_left.value( pct ) ) && see_white_line( line_tracker_right.value( pct ) ) )
    {
      dt.stop();
      break;
    }
    else 
    {
      dt.drive(directionType::fwd);
    }
  }

  dt.driveFor( directionType::rev, 3.5, distanceUnits::in );

  LeftMotor.spinFor( 235*2, vex::rotationUnits::deg );

  vex::task::sleep(500);

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
