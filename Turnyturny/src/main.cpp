/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Mon Mar 25 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// Drive Forward
// This program instructs your robot to move forward at half power for three
// seconds. There is a two second pause at the beginning of the program.
//
// Robot Configuration: 
// [Smart Port]    [Name]        [Type]           [Description]       [Reversed]
// Motor Port 1    LeftMotor     V5 Smart Motor    Left side motor     false
// Motor Port 10   RightMotor    V5 Smart Motor    Right side motor    true
//
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
vex::motor RightMotor   = vex::motor( vex::PORT1, true );
vex::motor LeftMotor  = vex::motor( vex::PORT10, false );
vex::line line_tracker( Brain.ThreeWirePort.A );
vex::drivetrain dt( LeftMotor, RightMotor ); 
vex::sonar ultra(Brain.ThreeWirePort.A);

vex::bumper bumpy( Brain.ThreeWirePort.C );

bool see_white_line( int value ) {
  return value <= 67;
}

int main() {
  Brain.Screen.print("TurnyTurny Program has Started.");

  vex::task::sleep(3000);

  dt.setVelocity(20, velocityUnits::pct);

  dt.driveFor(directionType::fwd, 30, distanceUnits::cm );

  while ( true )
  {
    Brain.Screen.print("sensor value:%d", ultra.value());
    Brain.Screen.newLine();
    if ( see_white_line( line_tracker.value( pct ) ) )
    {
      dt.stop();
      break;
    }
    else 
    {
      dt.drive(directionType::fwd);
    }
  }

  dt.driveFor( directionType::fwd, 7, distanceUnits::cm );

  LeftMotor.spinFor( 235*2, vex::rotationUnits::deg );

  vex::task::sleep(1000);

  LeftMotor.spinFor( -235*2, vex::rotationUnits::deg );

  while(1) {
    vex::task::sleep(100);
  }
}
