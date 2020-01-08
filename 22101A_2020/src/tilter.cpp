#include "vex.h"
using namespace vex;

namespace tilter {
  motor m = motor(PORT2, ratio36_1, false);

  void reset() {
    m = motor(PORT2, ratio36_1, false);
    m.stop(coast);
    m.resetRotation();
  }

  void stop() {
    m.stop(coast);
  }

  int op() {
    double upVel = 100, downVel = -100, kP = .4, max = 100;
    while(1) {
      while(con.ButtonR1.pressing()) {
        m.spin(fwd, upVel, pct);
      }
      while(con.ButtonR2.pressing()) {
        m.spin(fwd, downVel, pct);
      }
      if(!con.ButtonR1.pressing() && !con.ButtonR2.pressing()) {
        double ticks = m.rotation(deg);
        double err, vel;
        while(!con.ButtonR1.pressing() && !con.ButtonR2.pressing()) {
          err = ticks - m.rotation(vex::deg);

          if(err * kP > max) vel = max;
          else if(err * kP < -max) vel = -max;

          m.spin(fwd, vel, pct);

          wait(5, msec);
        }
      }
      wait(5, msec);
    }
    return 1;
  }

  int move(double deg, double max, double kP, double range, double time) {
    reset();
    double ticks = deg, err, vel;
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

  /*int hold() {
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
  }*/

}