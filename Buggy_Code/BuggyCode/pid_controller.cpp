#include "pid_controller.hpp"

PIDController::PIDController() {}
PIDController::~PIDController() {}
PIDController::PIDController(BuggyController *buggyController) {
  // Resets setpoints
  setPoints[0] = 0;
  setPoints[1] = 0;

  // Sets pointers to the buggy controller as well as its individual motor PWM
  // values
  linkedBuggyController = buggyController;
  current[0] = &linkedBuggyController->motor1PWM;
  current[1] = &linkedBuggyController->motor2PWM;
}

void PIDController::updatePIDController() {
  // Uses prev poll time to calculate delta time
  float dt = ((linkedBuggyController->ticks * 1000) - prevPollTime) / 1000.0f;
  // Resets prev poll time
  prevPollTime = (linkedBuggyController->ticks * 1000);

  // Calls 'calculateControlValue' and stores the values in the motor PWM
  // variables
  linkedBuggyController->motor1PWM = calculateControlValue(0, *current[0], dt);
  linkedBuggyController->motor2PWM = calculateControlValue(1, *current[1], dt);
  // Updates the actual pin duty cycle to the stores motor PWM values
  linkedBuggyController->updateMotorSpeed();
}

float PIDController::calculateControlValue(int index, float current, float dt) {
  // There will never be any unexpected error due to the lack of feedback making
  // this an open-loop system
  float error = setPoints[index] - current;

  integral[index] = integral[index] + error * dt;
  // Uses a general PID formula for calculating what the output should be set to
  float output =
      Kp * error + Ki * integral[index] + Kd * (error - prevError[index]) / dt;
  prevError[index] = error;

  return current + output;
}