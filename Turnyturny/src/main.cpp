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
vex::motor RightMotor   = vex::motor( vex::PORT2, true );
vex::motor LeftMotor  = vex::motor( vex::PORT3, false );
vex::line line_tracker( Brain.ThreeWirePort.A );
vex::drivetrain dt( RightMotor, LeftMotor ); 

bool see_white_line( int value ) {
    return value <= 67;
}

int main() {
    vex::task::sleep( 3000 );
    // Brain.Screen.print("TurnyTurny Program has Started.");

    dt.setVelocity(30, velocityUnits::pct);

    while ( true )
    {
      if ( see_white_line( line_tracker.value( pct ) ) )
      {
        dt.stop();
        break;
      }
      else 
      {
        dt.drive(fwd);
      }
    }

    dt.driveFor( directionType::rev, 5, distanceUnits::cm );

    LeftMotor.spinFor( 210, vex::rotationUnits::deg, false );
    RightMotor.spinFor( -210, vex::rotationUnits::deg );

    while(1) {
      vex::task::sleep(100);
    }
}
