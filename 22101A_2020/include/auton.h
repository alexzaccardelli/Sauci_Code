#ifndef _AUTON_H_
#define _AUTON_H_
using namespace vex;

namespace auton {
  enum {
    red = 1,
    blue = 2
  };

  void resetAll();

  void small(int side);
  void big(int side);
  void stack();
}

#endif