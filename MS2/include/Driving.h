#pragma once
#include "Blocks.h"
#include "Driving.h"
#include "LineTracker.h"
#include "PortConfig.h"

extern const double VROOM_SPEED;
extern const double YAW_SPEED;
extern const double CREEP_SPEED;

void Sleep( double sleep_time );
void Creep( double distance );
void CreepReverse( double distance );
void Forward( double distance );
void KeepScooting(); // drives forward until the forward line sensors no longer see white. Assumes the robot starts on white.
void ResumeDriveSpeed();
void Reverse( double distance );
void RevThoseEngines();
