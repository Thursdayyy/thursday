/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Mon Mar 25 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

#include "Driving.h"
#include "Maneuvers.h"
#include "Blocks.h"

using namespace vex;

//==================================================================================================================
void Setup()
{
  dt.setDriveVelocity( VROOM_SPEED, PUNITS);
  dt.setTurnVelocity( YAW_SPEED, PUNITS);
}

//==================================================================================================================
void TheConclusionOfThings()
{
  
  Park(0);

  ChaChaRealSmooth();

  Park(5);

  ChaChaRealSmooth();

  ThatsAWrapFolks();
}

//==================================================================================================================
int main()
{
  Setup();

  RevThoseEngines();

  // ButtonDrop();

  int bins = 0;

    while ( bins++ < 8 ) // takes ~34 seconds to enter a bin and then return 
    {
      SearchForCrossMark();
      dt.stop();

      TurnIntoBin();

      ApproachWall();

      RaiseBlocks();

      ReturnToLine();

      if ( bins == 5 ) // Turn around to begin visiting bins on the other side
      {

        Park(0);

        ChaChaRealSmooth();
      }

    }

  TheConclusionOfThings();
}