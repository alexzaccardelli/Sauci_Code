#include "vex.h"
using namespace vex;

namespace arm {
  motor m = motor(PORT1, ratio36_1, false);

  void reset() {
    m = motor(PORT1, ratio36_1, false);
    m.stop(coast);
    m.resetRotation();
  }

  void stop() {
    m.stop(coast);
  }

  int op() {
    double upVel = 60, downVel = -100, kP = .4, max = 100;
    while(1) {
      while(con.ButtonX.pressing()) {
        m.spin(fwd, upVel, pct);
      }
      while(con.ButtonB.pressing()) {
        m.spin(fwd, downVel, pct);
      }
      if(!con.ButtonB.pressing() && !con.ButtonX.pressing()) {
        double ticks = m.rotation(deg);
        double err, vel;
        while(!con.ButtonB.pressing() && !con.ButtonX.pressing()) {
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