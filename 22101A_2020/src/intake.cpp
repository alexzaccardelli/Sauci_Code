#include "vex.h"
using namespace vex;

namespace intake {
  motor l = motor(PORT3, ratio36_1, false);
  motor r = motor(PORT4, ratio36_1, true);

  void reset() {
    l = motor(PORT3, ratio18_1, false);
    r = motor(PORT4, ratio18_1, true);
    l.stop(coast);
    r.stop(coast);
    l.resetRotation();
    r.resetRotation();
  }

  void spin(double vel) {
    l.spin(fwd, vel, pct);
    r.spin(fwd, vel, pct);
  }

  int op() {
    while(1) {
      while(con.ButtonL1.pressing()) {
        spin(100);
      }
      while(con.ButtonL2.pressing()) {
        spin(-100);
      }
      l.stop(coast);
      r.stop(coast);
      wait(5, msec);
    }
    return 1;
  }
}