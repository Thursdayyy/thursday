#ifndef PORTCONFIG_H
#define PORTCONFIG_H

#include "vex.h"
#include "LineTracker.h"

using namespace vex;


// A global instance of vex::brain used for printing to the V5 brain screen
extern vex::brain       Brain;

// define your global instances of motors and other devices here
// MOTORS
extern vex::motor RightMotor;
extern vex::motor LeftMotor;
extern vex::motor BlockMotor;
extern vex::motor CamMotor;
extern vex::drivetrain dt; 

// SENSORS
extern LineTracker line_tracker_left;
extern LineTracker line_tracker_right;
extern LineTracker line_tracker_back_right;
extern LineTracker line_tracker_back_left;

extern vex::sonar ultra;
extern vex::bumper bumpy;

// TIMER
extern timer ticky;

//UNIT
extern const distanceUnits DUNITS;
extern const percentUnits PUNITS;
extern const rotationUnits RUNITS;

#endif
