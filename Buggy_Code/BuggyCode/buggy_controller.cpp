#include "buggy_controller.hpp"

BuggyController::BuggyController() : switch1(D4), switch2(D3) {}
BuggyController::BuggyController(PinName switchPin1, PinName switchPin2,
                                 PinName motorPin1, PinName motorPin2,
                                 PinName motorPin3, PinName motorPin4)
    : switch1(switchPin1), switch2(switchPin2),
      buggyMotors(motorPin1, motorPin2, motorPin3, motorPin4) {
  ticks.start();
  // switch1 d4 switch2 d3
}
BuggyController::~BuggyController() {}

int BuggyController::updateMotorSpeed() {
  return buggyMotors.Speed(motor1PWM, motor2PWM);
}