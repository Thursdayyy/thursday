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

//FUNCTIONS
void ButtonDrop()
{
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
void FollowLine()
{
  // go down center line and search for bins
  while ( true )
  {
  //   if ( line_tracker_front.sees_line() )
  //   {
  //     dt.drive(fwd);
  //     continue;
  //   }
  //   else
  //   {
  //     if ( line_tracker_left.sees_line() && line_tracker_right.sees_line() )
  //     {
  //       continue;
  //     }
  //     if ( line_tracker_left.sees_line() )
  //     {
  //       dt.stop();
  //       LeftMotor.spinFor(3, rotationUnits::deg);
  //     }
  //     else if ( line_tracker_right.sees_line() )
  //     {
  //       dt.stop();
  //       RightMotor.spinFor(3, rotationUnits::deg);
  //     }
  //   }
    // stop at a cross-mark
    if ( line_tracker_left.sees_line() && line_tracker_right.sees_line() )
    {
      dt.stop();
      return;
    }
    else 
    {
      dt.drive(directionType::fwd);
    }
  }
}

void BackItUp( double distance ) 
{
  dt.driveFor( directionType::rev, distance, DUNITS );
}

void Forward( double distance )
{
  dt.driveFor( directionType::fwd, distance, DUNITS );
}

bool OverCross()
{
  return !line_tracker_left.sees_line() && !line_tracker_right.sees_line();
}

int main() {
  // Brain.Screen.print("TurnyTurny Program has Started.");
  // Brain.Screen.newLine();

  println( "TurnyTurny Program has Started." );

  dt.setVelocity(15, velocityUnits::pct);
  vex::task::sleep(4500);

  ButtonDrop();

  FollowLine();
  
  BackItUp( 3.5 );

  // IDEA: record the movements made to perform the turn into the bin and reverse that movement to exit the bin
  RightMotor.spinFor( 235*2, vex::rotationUnits::deg );

  // for now using a distance marker to know how far to back out
  
  while( ultra.distance(DUNITS) > 3.4 )
  {
    dt.drive( directionType::fwd );
  }
  dt.stop();

  // blocks do their thang
  vex::task::sleep(3000);

  while ( !line_tracker_left.sees_line() && !line_tracker_right.sees_line() )
  {
    dt.drive( directionType::rev );
  }
  dt.stop();

  RightMotor.spinFor( -233, vex::rotationUnits::deg, false );
  LeftMotor.spinFor( 233, vex::rotationUnits::deg );
}
