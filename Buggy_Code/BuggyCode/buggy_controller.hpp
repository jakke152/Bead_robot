#ifndef BUGGY_CONTROLLER_HPP
#define BUGGY_CONTROLLER_HPP

#include <mbed.h>
#include <motor.hpp>

class BuggyController {
private:
public:
BuggyController();
  BuggyController(PinName switchPin1, PinName switchPin2, PinName motorPin1,
                  PinName motorPin2, PinName motorPin3, PinName motorPin4);
  ~BuggyController();

  DigitalIn switch1;
  DigitalIn switch2;

  float motor1PWM, motor2PWM;

  int updateMotorSpeed();
  // Motor buggyMotors(D13, D11, D9, D10);
  Motor buggyMotors;

  Timer ticks;
};

#endif