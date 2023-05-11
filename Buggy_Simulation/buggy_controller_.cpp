#include "buggy_controller_.hpp"

BuggyController::BuggyController();
BuggyController::BuggyController~()

int BuggyController::updateMotorSpeed()
{
    return buggyMotors.speed(motor1PWM, motor2PWM);    
}