#ifndef _ARM_H_
#define _ARM_H_
using namespace vex;

namespace arm {
  extern vex::motor m;
  extern bool holding;
  extern task holdTask;

  void reset();
  void stop();

  int move(double height, double max, double kP, double range, double time);
  int hold();

  int op();
}

#endif