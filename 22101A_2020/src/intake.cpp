#include "vex.h"
using namespace vex;

namespace intake {
  motor l = motor(PORT5, ratio36_1, false);
  motor r = motor(PORT6, ratio36_1, true);

  void reset() {
    l = motor(PORT5, ratio18_1, false);
    r = motor(PORT6, ratio18_1, true);
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

    }
    return 1;
  }
}