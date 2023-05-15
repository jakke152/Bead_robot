#include "buggy_controller.hpp"

// Default constructor, initialises switches to random pins
BuggyController::BuggyController() : switch1(D4), switch2(D3) {}

// This constructor takes in all of the required pins for the buggy interface
// and initialises the switches and motors
BuggyController::BuggyController(
PinName switchPin1, PinName switchPin2, PinName motorPin1, PinName motorPin2,
PinName motorPin3, PinName motorPin4) : switch1(switchPin1), switch2(switchPin2), 
buggyMotors(motorPin1, motorPin2, motorPin3, motorPin4) 
{
  ticks.start();  // Starts main timer
}
BuggyController::~BuggyController() {}

int BuggyController::updateMotorSpeed() {
  return buggyMotors.Speed(motor1PWM, motor2PWM);
}