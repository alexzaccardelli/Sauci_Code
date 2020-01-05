#ifndef _TILTER_H_
#define _TILTER_H_
using namespace vex;

namespace tilter {
  extern motor m;
  extern bool holding;
  extern task holdTask;

  void reset();
  void stop();

  int move(double deg, double max, double kP, double range, double time);
  int hold();

  int op();
}

#endif