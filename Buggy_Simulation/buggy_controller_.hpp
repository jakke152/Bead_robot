#ifndef BUGGY_CONTROLLER__HPP
#define BUGGY_CONTROLLER__HPP

#include <motor.h>
#include <mbed.h>

class BuggyController
{
private:
public:
    BuggyController();
    ~BuggyController();

    DigitalIn switch1(D4);
    DigitalIn switch2(D3);

    float motor1PWM, motor2PWM;

    int updateMotorSpeed();
    Motor buggyMotors(D13, D11, D9, D10);
}

#endif