#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP

#include "functions.hpp"

#include "buggy_controller.hpp"

#include <SDL2/SDL.h>

class PIDController
{
private:
    float Kp = PID_KP;
    float Ki = PID_KI;
    float Kd = PID_KD;

    float prevError[2] = {0, 0};  // Previous error values for motors 1 & 2
    float integral[2] = {0, 0};
    long prevPollTime = SDL_GetTicks();

    BuggyController *linkedBuggyController;
public:
    PIDController();
    ~PIDController();
    PIDController(BuggyController *linkedBuggyController);

    void updatePIDController();
    float calculateControlValue(int index, float current, float dt);

    float setPoints[2] = {0,0};
    float *current[2];
};

#endif