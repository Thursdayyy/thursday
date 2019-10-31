#pragma once
#include "vex.h"
#include "LineTracker.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
// MOTORS
vex::motor RightMotor = vex::motor( vex::PORT1, true );
vex::motor LeftMotor = vex::motor( vex::PORT10, false );
vex::motor BlockMotor = vex::motor( vex::PORT4, false );
vex::motor CamMotor = vex::motor( vex::PORT5, false );
vex::drivetrain dt( LeftMotor, RightMotor ); 

// SENSORS
LineTracker line_tracker_left( line(Brain.ThreeWirePort.G) );
LineTracker line_tracker_right( line(Brain.ThreeWirePort.H) );
LineTracker line_tracker_back_right( line( Brain.ThreeWirePort.D) );
LineTracker line_tracker_back_left( line( Brain.ThreeWirePort.E) );

vex::sonar ultra(Brain.ThreeWirePort.A);
vex::bumper bumpy( Brain.ThreeWirePort.F );

// UNITS
constexpr auto DUNITS = distanceUnits::in;
constexpr auto PUNITS = percentUnits::pct;
constexpr auto RUNITS = rotationUnits::deg;

// CONSTANTS
constexpr double VROOM_SPEED = 15;
constexpr double YAW_SPEED = 15;
constexpr double CREEP_SPEED = 5;


// STATE VARIABLES
bool DoorOpen = false;

// TIMER
timer ticky = vex::timer();
