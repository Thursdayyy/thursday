#include "PortConfig.h"

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
// MOTORS
vex::motor RightMotor = vex::motor( vex::PORT1, true );
vex::motor LeftMotor = vex::motor( vex::PORT10, false );
vex::motor BlockMotor = vex::motor( vex::PORT3, false );
vex::motor CamMotor = vex::motor( vex::PORT9, false );
vex::drivetrain dt( LeftMotor, RightMotor ); 

// SENSORS
LineTracker line_tracker_left( line( Brain.ThreeWirePort.H ) );
LineTracker line_tracker_right( line( Brain.ThreeWirePort.G ) );
LineTracker line_tracker_back_right( line( Brain.ThreeWirePort.D ) );
LineTracker line_tracker_back_left( line( Brain.ThreeWirePort.E ) );
LineTracker line_tracker_back_center( line( Brain.ThreeWirePort.C ) );

vex::sonar ultra( Brain.ThreeWirePort.A );
vex::bumper bumpy( Brain.ThreeWirePort.C );

// TIMER
timer ticky = vex::timer();

// UNITS
const distanceUnits DUNITS = distanceUnits::in;
const percentUnits PUNITS = percentUnits::pct;
const rotationUnits RUNITS = rotationUnits::deg;
