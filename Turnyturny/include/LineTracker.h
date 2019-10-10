#pragma once
#include "vex.h"

using namespace vex;

constexpr int LINE_ANALOG_PCT = 65;

class LineTracker
{
  vex::line line_tracker;
public:
  LineTracker( const line &lt ): line_tracker( lt ) {}

  bool sees_line() { return line_tracker.value( analogUnits::pct ) <= LINE_ANALOG_PCT; }

};