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
// Stamps down and raises the blocks
void raise_blocks(){
    vex::task::sleep( 3000 );
    // Open the Door
    CamMotor.spinTo(90,vex::rotationUnits::deg, true );
    // Stamp downt the blocks
    BlockMotor.setVelocity(40,velocityUnits::pct);
    BlockMotor.spin(directionType::fwd);
    wait(1.5,vex::timeUnits::sec);
    BlockMotor.stop();
    // Pick up new blocks
    BlockMotor.spin(directionType::rev);
    wait(4,vex::timeUnits::sec);
    BlockMotor.stop();
    // Shut the door
    CamMotor.spinTo(0, vex::rotationUnits::deg,true);
    return;
}
//FUNCTIONS
void ButtonDrop()
{
  const double vel = 20;
  dt.setVelocity(vel, velocityUnits::pct);
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
  const int vel = 20;
  double i = 0;
  const double vel_offset = .1;

  LeftMotor.setVelocity( vel, percentUnits::pct );
  RightMotor.setVelocity( vel, percentUnits::pct );
  dt.drive(fwd);

  // go down center line and search for bins
  while ( true )
  {
      if ( line_tracker_left.sees_line() && line_tracker_right.sees_line() ) // 1 1
      {
        dt.stop();
        return;
        // continue;
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

void BackItUp( double distance ) 
{
  dt.driveFor( directionType::rev, distance, DUNITS );
}

void Park(){

  while (true) {
    dt.drive(fwd);

    if (line_tracker_left.sees_line() && line_tracker_right.sees_line()){
      break;
    }
  }

  dt.driveFor(fwd, 3.5, DUNITS);

  dt.stop();

  return;
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
  raise_blocks();

  vex::task::sleep(3000);

  while ( !line_tracker_left.sees_line() && !line_tracker_right.sees_line() )
  {
    dt.drive( directionType::rev );
  }
  dt.stop();

  RightMotor.spinFor( -233, vex::rotationUnits::deg, false );
  LeftMotor.spinFor( 233, vex::rotationUnits::deg );

  // //Caroline attempts to make it into a loop in the comments belowwwww

  // int bins = 0;

  // while (bins < 5) {

  //   FollowLine();
  
  //   BackItUp( 3.5 );

  //   RightMotor.spinFor( 235*2, vex::rotationUnits::deg );
    
  //   while( ultra.distance(DUNITS) > 3.4 )
  //   {
  //     dt.drive( directionType::fwd );
  //   }
  //   dt.stop();

  //   // blocks do their thang
  //   raise_blocks();

  //   vex::task::sleep(3000);

  //   while ( !line_tracker_left.sees_line() && !line_tracker_right.sees_line() )
  //   {
  //     dt.drive( directionType::rev );
  //   }
  //   dt.stop();

  //   RightMotor.spinFor( -233, vex::rotationUnits::deg, false );
  //   LeftMotor.spinFor( 233, vex::rotationUnits::deg );

  //   bins++;
  // }

  // Park();

}
