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

  // Microswitches
  DigitalIn switch1;
  DigitalIn switch2;

  // Intermediate motor PWM floats
  float motor1PWM, motor2PWM;

  // Technically inefficient, yet modular interface between the PID controller
  // and the motor speeds
  int updateMotorSpeed();

  // Main buggy motors
  Motor buggyMotors;

  // Main timer that almost every system runs according to
  Timer ticks;
};

#endif