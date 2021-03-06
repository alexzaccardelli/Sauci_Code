#include "vex.h"
using namespace vex;

competition Competition;
vex::brain cpu;
controller con;
task driveTask, intakeTask, tilterTask, armTask;

void usercontrol(void) {
  auton::resetAll();
  driveTask = task(drive::op);
  intakeTask = task(intake::op);
  tilterTask = task(tilter::op);
  armTask = task(arm::op);
  while(1) {
    wait(5, msec);
    cpu.Screen.clearScreen();
    cpu.Screen.setCursor(5,5);
    cpu.Screen.print("hello");
  }
}

void pre_auton(void) {
  vexcodeInit();
  auton::resetAll();
}

void autonomous(void) {
  
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();
  //auton::resetAll();
  
  while (true) wait(100, msec);
}
