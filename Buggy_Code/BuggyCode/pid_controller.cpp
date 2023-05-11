#include "pid_controller.hpp"

PIDController::PIDController() {}
PIDController::~PIDController() {}
PIDController::PIDController(BuggyController *buggyController)
{
    setPoints[0] = 0;
    setPoints[1] = 0;
    linkedBuggyController = buggyController;
    current[0] = &linkedBuggyController->motor1PWM;
    current[1] = &linkedBuggyController->motor2PWM;
}

void PIDController::updatePIDController()
{
    float dt = ((linkedBuggyController->ticks*1000) - prevPollTime) / 1000.0f;
    prevPollTime = (linkedBuggyController->ticks*1000);

    linkedBuggyController->motor1PWM = calculateControlValue(0, *current[0], dt);
    linkedBuggyController->motor2PWM = calculateControlValue(1, *current[1], dt);
    if(linkedBuggyController->updateMotorSpeed() != 0){
    }
}

float PIDController::calculateControlValue(int index, float current, float dt)
{
    float error = setPoints[index] - current;

    integral[index] = integral[index] + error * dt;
    float output = Kp * error + Ki * integral[index] + Kd * (error - prevError[index]) / dt;
    prevError[index] = error;

    return current + output;
}