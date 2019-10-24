#pragma once
#include "vex.h"

using namespace vex;

constexpr int LINE_ANALOG_PCT = 60;

class LineTracker
{
  vex::line line_tracker;
public:
  LineTracker( const line &lt ): line_tracker( lt ) {}

  const int val() { return line_tracker.value(analogUnits::pct); }

  bool sees_line() { return line_tracker.value( analogUnits::pct ) <= LINE_ANALOG_PCT; }
};
