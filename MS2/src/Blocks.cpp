#include "Blocks.h"

// STATE VARIABLES
bool DoorOpen = false;

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

    wait(0.6, vex::timeUnits::sec);
    
    BlockMotor.stop();
    
    // Pick up new blocks
    BlockMotor.setVelocity(50, velocityUnits::pct);
    BlockMotor.spin(directionType::fwd);
    wait(0.4, vex::timeUnits::sec);
    
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
    return;
}