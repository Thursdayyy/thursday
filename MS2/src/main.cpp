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
//=================================================================================================================
void println( const char* c_str )
{
  Brain.Screen.print( c_str );
  Brain.Screen.newLine();
}

//==================================================================================================================
void Setup()
{
  dt.setDriveVelocity( VROOM_SPEED, velocityUnits::pct);
  dt.setTurnVelocity( YAW_SPEED, PUNITS);
}

// Stamps down and raises the blocks
//==================================================================================================================
void RaiseBlocks()
{
    // vex::task::sleep( 1000 );
    // Shut the door
    CamMotor.spinTo(0, vex::rotationUnits::deg,true);
    // Stamp down the blocks
    BlockMotor.setVelocity(100, velocityUnits::pct);
    BlockMotor.spin(directionType::rev);

    wait(1.5, vex::timeUnits::sec);
    
    BlockMotor.stop();
    
    // Pick up new blocks
    BlockMotor.setVelocity(50, velocityUnits::pct);
    BlockMotor.spin(directionType::fwd);
    wait(1.2, vex::timeUnits::sec);
    
    BlockMotor.stop();
    DoorOpen = false;
}

//==================================================================================================================
void OpenDoor()
{
    //Make sure door is open
    if (DoorOpen == false){
      DoorOpen = true;
      CamMotor.spinTo(90, vex::rotationUnits::deg,true);
    }
}

//==================================================================================================================
void RevThoseEngines()
{
  while (!bumpy.pressing())
    ;

  ticky.clear();

  task::sleep(500);
}

//==================================================================================================================
void KeepScooting(){
  // move past the starting square
  while ( line_tracker_left.sees_line() && line_tracker_right.sees_line() )
  {
    dt.drive(fwd);
  }
}

//==================================================================================================================
void ButtonDrop()
{
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

  KeepScooting();
}

//==================================================================================================================
void SearchForCrossMark() // TODO: maybe add a flag to decide to continue or stop at a cross mark
{
  const int vel = 20;
  double i = 0;
  const double vel_offset = .2;

  dt.setDriveVelocity(vel, pct);
  dt.drive(fwd);

  // go down center line and search for bins
  while ( true )
  {
      if ( line_tracker_left.sees_line() && line_tracker_right.sees_line() ) // 1 1
      {
        //TODO: Move stop outside of this function
        return;
      }

      if ( line_tracker_left.sees_line() && !line_tracker_right.sees_line() ) // 1 0
      {
        i += vel_offset;
        RightMotor.setVelocity( vel + i, PUNITS );
      }
      else if ( !line_tracker_left.sees_line() && line_tracker_right.sees_line() ) // 0 1
      {
        i += vel_offset;
        LeftMotor.setVelocity( vel + i, PUNITS );
      }
      else if ( !line_tracker_left.sees_line() && !line_tracker_right.sees_line() ) { // 0 0
        i = 0;
        LeftMotor.setVelocity( vel, PUNITS );
        RightMotor.setVelocity( vel, PUNITS );
      }

    vex::task::sleep(70);
  }
}

//==================================================================================================================
void BackItUp( double distance )
{
  dt.driveFor( directionType::rev, distance, DUNITS );
}

//==================================================================================================================
void Forward( double distance ) // TODO: make it accellerate to max speed instead of immediately starting full speed to prevent jerking
{
  dt.driveFor( directionType::fwd, distance, DUNITS );
}

void Creep( double distance )
{
  const double CREEP_SPEED = 5;
  dt.setDriveVelocity( CREEP_SPEED, PUNITS );
  Forward( distance );
  dt.setDriveVelocity( VROOM_SPEED, PUNITS );
}

//==================================================================================================================
void Park( const int cross_marks )
{

  int seen = 0;
  while (seen < cross_marks) {
    SearchForCrossMark();
    Forward(2.5);
    seen++;
  }

  while (true) { // TODO: replace this code with SearchForCrossMark()
    dt.drive(fwd);

    if (line_tracker_left.sees_line() && line_tracker_right.sees_line()){
       break;
     }

  }

  dt.stop();
  Forward(7);
}

//==================================================================================================================
void TurnIntoBin()
{
    // Forward( 7.5 );
    while ( !line_tracker_back.sees_line() )
    {
      dt.drive(fwd);
      vex::task::sleep(40);
    }

    Creep(2.5);
    dt.stop();

    OpenDoor();

    dt.setTurnVelocity(8, PUNITS);
    while( !line_tracker_back.sees_line() )
    {
      dt.turn(turnType::left);
      vex::task::sleep(20);
    }
    dt.turnFor(-4, RUNITS);
    while( line_tracker_back.sees_line() )
    {
      dt.turn(turnType::left);
      vex::task::sleep(20);
    }
    dt.turnFor(-15, RUNITS);
    dt.stop();
    dt.setTurnVelocity(YAW_SPEED, PUNITS);
    // IDEA: record the movements made to perform the turn into the bin and reverse that movement to exit the bin
    // dt.turnFor(-58, vex::rotationUnits::deg); // TODO: change this absolute value into something more consistent
    
    vex::task::sleep(5000);
}

//==================================================================================================================
void ApproachWall()
{
    dt.setDriveVelocity(10, PUNITS);
    dt.drive(fwd);

    Forward(16);

    dt.stop();

    dt.setDriveVelocity( VROOM_SPEED, PUNITS );
}

//==================================================================================================================
void ReturnToLine()
{
  while ( !line_tracker_back.sees_line()) {
    dt.drive( directionType::rev );
    vex::task::sleep(100);
  }

  dt.stop();

  Creep(1.0);

  dt.setTurnVelocity(5, PUNITS);

  while (!line_tracker_left.sees_line()) {
    dt.turn(turnType::right);
    vex::task::sleep(50);
  }

  dt.turnFor(-4, rotationUnits::deg);

  dt.setTurnVelocity( YAW_SPEED, PUNITS );
}

//=================================================================================================================
void ChaChaRealSmooth() {

  dt.setTurnVelocity(YAW_SPEED, PUNITS);

  dt.turnFor(100, rotationUnits::deg); // TODO: use line sensor to determine if turn is complete instead of absolute

  while( !line_tracker_left.sees_line() )
     dt.turn(turnType::right);

  dt.turnFor(-4, rotationUnits::deg);
}

//==================================================================================================================
void HitTheBooty(){
  dt.setDriveVelocity(VROOM_SPEED/2, PUNITS);
  while (!bumpy.pressing()){
    dt.drive(directionType::rev);
  }

  dt.stop();
}

//==================================================================================================================
int main()
{
  Setup();
  RevThoseEngines();

  ButtonDrop();

  int laps = 0;

    int bins = 0;

    while ( bins++ < 5 ) // takes ~34 seconds to enter a bin and then return 
    {
      SearchForCrossMark();
      dt.stop();

      TurnIntoBin();

      ApproachWall();

      RaiseBlocks();

      ReturnToLine();
    }

    Park(0);

    ChaChaRealSmooth();

    //------- For now we are running 8 bins
    
  bins = 0;
while ( bins++ < 3 ) // takes ~34 seconds to enter a bin and then return 
    {
      SearchForCrossMark();
      dt.stop();

      TurnIntoBin();

      ApproachWall();

      RaiseBlocks();

      ReturnToLine();
    }

    Park(0);

    ChaChaRealSmooth();
    //-------

  Park(5);

  ChaChaRealSmooth();

  HitTheBooty();
}