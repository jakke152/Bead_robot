#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP

#include "constants.hpp"

#include "buggy_controller.hpp"

class PIDController {
private:
  // Uses predefined constants to assign PID values
  float Kp = PID_KP;
  float Ki = PID_KI;
  float Kd = PID_KD;

  // -- Variables storing information from the previous cycle --
  float prevError[2] = {0, 0};
  float integral[2] = {0, 0};
  // Stores the previous cycle time, used to find dT
  long prevPollTime = 0;

  BuggyController *linkedBuggyController;

public:
  PIDController();
  ~PIDController();
  // Initalises PID controller with a linked buggy controller
  PIDController(BuggyController *linkedBuggyController);

  // Update the entire PID controller
  void updatePIDController();
  // Calculates the speed the motors should spin in order to smoothly transition
  // towards their setpoint
  float calculateControlValue(int index, float current, float dt);

  // Motor setpoints
  int setPoints[2];
  // Pointers to current motor PWM values
  float *current[2];
};

#endif