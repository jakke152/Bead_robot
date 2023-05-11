#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP

#include "functions.hpp"

#include "buggy_controller.hpp"

class PIDController
{
private:
    float Kp = PID_KP;
    float Ki = PID_KI;
    float Kd = PID_KD;

    float prevError[2] = {0, 0};  // Previous error values for motors 1 & 2
    float integral[2] = {0, 0};
    long prevPollTime = 0;

    BuggyController *linkedBuggyController;
public:
    PIDController();
    ~PIDController();
    PIDController(BuggyController *linkedBuggyController);

    void updatePIDController();
    float calculateControlValue(int index, float current, float dt);

    int setPoints[2];
    float *current[2];
};

#endif