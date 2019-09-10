// VEX V5 C++ Project
#include "vex.h"
using namespace vex;

//#region config_globals
vex::brain      Brain;
vex::motor      motor_right(vex::PORT1, vex::gearSetting::ratio18_1, true);
vex::motor      motor_left(vex::PORT10, vex::gearSetting::ratio18_1, false);
vex::line       line_tracker_left(Brain.ThreeWirePort.A);
vex::line       line_tracker_right(Brain.ThreeWirePort.B);
vex::drivetrain dt(motor_left, motor_right, 319.1764, 292.1, vex::distanceUnits::mm);
//#endregion config_globals

//value returned when staring at a line:
int line_value = 71;
//value returned when staring at the floor:
int floor_value = 30;

bool sees_line(int tracker_value) {
    return abs(tracker_value - line_value) <= abs(tracker_value - floor_value);
}

bool see_white_line( int value ) {
    return value <= 67;
}

int main(void) {
    //go slow, as this algorithm doesn't handle overshooting the line very well
    dt.setVelocity(10,velocityUnits::pct);
    // while(true)
    // {
    //   Brain.Screen.print(line_tracker_left.value(pct));
    //   Brain.Screen.newLine();
    // }
    while(true) {
        // if(sees_line(line_tracker_right.value(pct)) || sees_line(line_tracker_left.value(pct)) )
        // {
        //     //right tracker saw line, we're drifting left
        //     dt.setVelocity( 0, velocityUnits::pct );
        // } 
        if( see_white_line( line_tracker_right.value( pct ) ) )
        {
          dt.turn(turnType::right);
          Brain.Screen.print( line_tracker_right.value( pct ) );
          Brain.Screen.newLine();
        } 
        else if( see_white_line( line_tracker_left.value( pct ) ) )
        {
          dt.turn(turnType::left);
          Brain.Screen.print( line_tracker_left.value( pct ) );
          Brain.Screen.newLine();
        } 
        else 
        {
            //neither tracker sees the line, so we're straddling it
            dt.drive(fwd);
        }
    }
}

