#include "vex.h"
using namespace vex;

namespace arm {
  motor m = motor(PORT8, ratio36_1, false);
  bool holding = false;
  task holdTask;

  void reset() {
    holdTask = task(hold);
    holding = false;
    m = motor(PORT8, ratio36_1, false);
    m.stop(coast);
    m.resetRotation();
  }

  void stop() {
    m.stop(coast);
  }

  int op() {
    double upVel = 100, downVel = -100;
    while(1) {
      while(con.ButtonL1.pressing()) {
        holding = false;
        m.spin(fwd, upVel, pct);
      }
      while(con.ButtonL2.pressing()) {
        holding = false;
        m.spin(fwd, downVel, pct);
      }
      holding = true;
    }
    return 1;
  }

  int move(double height, double max, double kP, double range, double time) {
    reset();
    double ticks = height * 1.7, err, vel; //Temporary
    timer t;
    while(1) {
      err = ticks - m.rotation(vex::deg);

      if(err * kP > max) vel = max;
      else if(err * kP < -max) vel = -max;

      m.spin(fwd, vel, pct);

      if(fabs(err) > range) t.reset();
      if(t.time(msec) > time) break;

      wait(5, msec);
    }
    reset();
    return 1;
  }

  int hold() {
    double max = 100, kP = 0.4; //Temporary
    while(true) {
      if(holding) {
        double ticks = m.rotation(deg);
        double err, vel;
        while(holding) {
          err = ticks - m.rotation(vex::deg);

          if(err * kP > max) vel = max;
          else if(err * kP < -max) vel = -max;

          m.spin(fwd, vel, pct);

          wait(5, msec);
        }
      }
    }
    return 1;
  }

}