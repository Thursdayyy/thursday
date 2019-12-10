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

  ChaChaRealSmooth();

  Park(3);

  ChaChaRealSmooth();

  ThatsAWrapFolks();
}

//==================================================================================================================
int MissionAbort()
{
  while ( !bumpy.pressing() )
  {
    wait(10, msec);
  }

  vexSystemExitRequest();
  return -1;
}

//==================================================================================================================
int main()
{
  Setup();

  RevThoseEngines();

  // task abort_mission = task( MissionAbort );

  ButtonDrop();

  CorrectForDropOff();

  int bins = 0;

    while ( bins++ < 8 ) // bins represents the # of the bin we are about to visit
    {
      SearchForCrossMark();
      dt.stop();

      TurnIntoBin( creep_offsets[bins - 1], turn_angles[bins - 1] );

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