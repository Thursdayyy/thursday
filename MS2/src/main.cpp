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
void println( const char* c_str ) {
  Brain.Screen.print( c_str );
  Brain.Screen.newLine();
}

// Stamps down and raises the blocks
void RaiseBlocks() {
    vex::task::sleep( 1000 );

    // Open the Door
    // Stamp down the blocks
    BlockMotor.setVelocity(30, velocityUnits::pct);
    BlockMotor.spin(directionType::rev);

    wait(1.5, vex::timeUnits::sec);
    
    BlockMotor.stop();
    
    // Pick up new blocks
    BlockMotor.spin(directionType::fwd);
    
    wait(4, vex::timeUnits::sec);
    
    BlockMotor.stop();
    
    // Shut the door
    //CamMotor.spinTo(90, vex::rotationUnits::deg,true);
    return;
}

void RevThoseEngines(){
  while (!bumpy.pressing())
    ;

  task::sleep(2000);
  return;
}

void ButtonDrop() {
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

//TODO
void FollowLine() {
  const int vel = 20;
  double i = 0;
  const double vel_offset = .1;

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
        RightMotor.setVelocity( vel + i, percentUnits::pct );
      }
      else if ( !line_tracker_left.sees_line() && line_tracker_right.sees_line() ) // 0 1
      {
        i += vel_offset;
        LeftMotor.setVelocity( vel + i, percentUnits::pct );
      }
      else if ( !line_tracker_left.sees_line() && !line_tracker_right.sees_line() ) { // 0 0
        i = 0;
        LeftMotor.setVelocity( vel, percentUnits::pct );
        RightMotor.setVelocity( vel, percentUnits::pct );
      }

    vex::task::sleep(90);
  }
}

void BackItUp( double distance ) {
  dt.driveFor( directionType::rev, distance, DUNITS );
}

void Park() {
  while (true) {
    dt.drive(fwd);

    if (line_tracker_left.sees_line() && line_tracker_right.sees_line()){
      break;
    }
  }

  dt.stop();

  return;
}


void Forward( double distance ) {
  dt.driveFor( directionType::fwd, distance, DUNITS );
}

bool OverCross() {
  return !line_tracker_left.sees_line() && !line_tracker_right.sees_line();
}

int main() {
  // Brain.Screen.print("TurnyTurny Program has Started.");
  // Brain.Screen.newLine();

  println( "TurnyTurny Program has Started." );

  RevThoseEngines();

//Caroline's VEX made her change this from setVelocity
  dt.setDriveVelocity(15, velocityUnits::pct);

  ButtonDrop();
  int bins = 0;
  while ( bins++ < 5 ) {
    FollowLine();
    
    Forward( 7.5 );

    // IDEA: record the movements made to perform the turn into the bin and reverse that movement to exit the bin
    //RightMotor.spinFor( 235*2, vex::rotationUnits::deg );
    dt.turnFor(-61, vex::rotationUnits::deg);

    Forward(20);

    // for now using a distance marker to know how far to back out
    
    while( ultra.distance(DUNITS) > 3.4 )
    {
      dt.drive( directionType::fwd );
    }
    dt.stop();

    // blocks do their thang
    //sRaiseBlocks();

    vex::task::sleep(3000);

    while ( !line_tracker_back.sees_line()) {
      dt.drive( directionType::rev );
      vex::task::sleep(50);
    }

    dt.stop();

    dt.turnFor(65, vex::rotationUnits::deg);
  }

  Park();

}
