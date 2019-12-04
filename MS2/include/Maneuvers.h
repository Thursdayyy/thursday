#pragma once
#include "PortConfig.h"
#include "Blocks.h"

extern const double creep_offsets[];
extern const double turn_angles[];

void SearchForCrossMark();
void TurnIntoBin( double creepin, double left_turn_angle = 58 );
void ApproachWall();
void ReturnToLine();
void Park( const int cross_marks );
void ChaChaRealSmooth();
void ThatsAWrapFolks();
void ButtonDrop();