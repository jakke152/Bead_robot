#include "pid_controller.hpp"

PIDController::PIDController() {}
PIDController::~PIDController() {}
PIDController::PIDController(BuggyController *buggyController)
{
    linkedBuggyController = buggyController;
    current[0] = &linkedBuggyController->motor1PWM;
    current[1] = &linkedBuggyController->motor2PWM;
}

void PIDController::updatePIDController()
{
    float dt = (linkedBuggyController->SDLTicks - prevPollTime / 1000.0f);
    prevPollTime = linkedBuggyController->SDLTicks;

    linkedBuggyController->motor1PWM = calculateControlValue(0, *current[0], dt);
    linkedBuggyController->motor2PWM = calculateControlValue(1, *current[1], dt);
}

float PIDController::calculateControlValue(int index, float current, float dt)
{
    float error = setPoints[index] - current;

    integral[index] = integral[index] + error * dt;
    float output = Kp * error + Ki * integral[index] + Kd * (error - prevError[index]) / dt;
    prevError[index] = error;

    return current + output * SPEED_SCALE;
}