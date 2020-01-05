#include "vex.h"
using namespace vex;

namespace drive {
  motor l1 = motor(PORT1, ratio18_1, false);
  motor l2 = motor(PORT2, ratio18_1, false);
  motor r1 = motor(PORT3, ratio18_1, true);
  motor r2 = motor(PORT4, ratio18_1, true);
  encoder lEnc = encoder(cpu.ThreeWirePort.A);
  encoder rEnc = encoder(cpu.ThreeWirePort.C);

  void reset() {
    l1 = motor(PORT1, ratio18_1, false);
    l2 = motor(PORT2, ratio18_1, false);
    r1 = motor(PORT3, ratio18_1, true);
    r2 = motor(PORT4, ratio18_1, true);
    l1.stop(coast);
    l2.stop(coast);
    r1.stop(coast);
    r2.stop(coast);
    l1.resetRotation();
    l2.resetRotation();
    r1.resetRotation();
    r2.resetRotation();
    lEnc.resetRotation();
    rEnc.resetRotation();
  }

  int op() {
    double y1, y2, x1, x2, lVel, rVel;
    double accel = 0.8, max = 100;
    while(1) {
      y1 = con.Axis3.position();
      y2 = con.Axis2.position();
      x1 = con.Axis4.position();
      x2 = con.Axis1.position();

      if(y1 > max) lVel = max;
      else if(y1 < -max) lVel = -max;
      else if(y1 > lVel) lVel += accel;
      else if(y1 < lVel) lVel -= accel;
      if(y2 > max) rVel = max;
      else if(y2 < -max) rVel = -max;
      else if(y2 > rVel) rVel += accel;
      else if(y2 < rVel) rVel -= accel;

      l1.spin(fwd, lVel, pct);
      l2.spin(fwd, lVel, pct);
      r1.spin(fwd, rVel, pct);
      r2.spin(fwd, rVel, pct);
      
      wait(5, msec);
    }
  }

  int forward(double dist, double max, double accel, double kP, double range, double time) {
    reset();
    double ticks = dist / (2 * 3.1415 * 1.375) * 360.0;
    double lErr, rErr, lVel, rVel;
    timer t;
    while(1) {
      lErr = ticks - lEnc.rotation(deg);
      rErr = ticks - rEnc.rotation(deg);

      if(lErr * kP > max) lVel = max;
      else if(lErr * kP < -max) lVel = -max;
      else if(lErr * kP > lVel) lVel += accel;
      else if(lErr * kP < lVel) lVel -= accel;
      if(rErr * kP > max) rVel = max;
      else if(rErr * kP < -max) rVel = -max;
      else if(rErr * kP > rVel) rVel += accel;
      else if(rErr * kP < rVel) rVel -= accel;

      l1.spin(fwd, lVel, pct);
      l2.spin(fwd, lVel, pct);
      r1.spin(fwd, rVel, pct);
      r2.spin(fwd, rVel, pct);

      if(fabs(lErr) > range || fabs(rErr) > range) t.reset();
      if(t.time(msec) > time) break;

      wait(5, msec);
    }
    reset();
    return 1;
  }

  int turn(double deg, double max, double accel, double kP, double range, double time) {
    reset();
    double ticks = deg * 1; //Get constant
    double lErr, rErr, lVel, rVel;
    timer t;
    while(1) {
      lErr = ticks - lEnc.rotation(vex::deg);
      rErr = -(ticks - rEnc.rotation(vex::deg));

      if(lErr * kP > max) lVel = max;
      else if(lErr * kP < -max) lVel = -max;
      else if(lErr * kP > lVel) lVel += accel;
      else if(lErr * kP < lVel) lVel -= accel;
      if(rErr * kP > max) rVel = max;
      else if(rErr * kP < -max) rVel = -max;
      else if(rErr * kP > rVel) rVel += accel;
      else if(rErr * kP < rVel) rVel -= accel;

      l1.spin(fwd, lVel, pct);
      l2.spin(fwd, lVel, pct);
      r1.spin(fwd, rVel, pct);
      r2.spin(fwd, rVel, pct);

      if(fabs(lErr) > range || fabs(rErr) > range) t.reset();
      if(t.time(msec) > time) break;

      wait(5, msec);
    }
    reset();
    return 1;
  }

  void spin(int vel) {
    l1.spin(fwd, vel, pct);
    l2.spin(fwd, vel, pct);
    r1.spin(fwd, vel, pct);
    r2.spin(fwd, vel, pct);
  }

  void spinRight(int vel) {
    r1.spin(fwd, vel, pct);
    r2.spin(fwd, vel, pct);
  }

  void spinLeft(int vel) {
    l1.spin(fwd, vel, pct);
    l2.spin(fwd, vel, pct);
  }
}