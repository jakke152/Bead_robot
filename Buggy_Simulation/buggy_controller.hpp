#ifndef BUGGY_CONTROLLER_HPP
#define BUGGY_CONTROLLER_HPP

#include "functions.hpp"

#include "progress_bar.hpp"

#include "graph.hpp"

#include <math.h>

#include <SDL2/SDL.h>

#include <vector>

class BuggyController
{
private:
    //-----Data for buggy simulation-----
    float position[2] = {BUGGY_SWITCH_RADIUS * 1.1, SCREEN_HEIGHT - BUGGY_SWITCH_RADIUS * 1.5};
    double angle = 1.5 * M_PI;

    float switchPos1[2] = {position[0] + (cos(angle) * BUGGY_SWITCH_RADIUS) + ARENA_SCREEN_OFFSET_X, position[1] + (sin(angle) * BUGGY_SWITCH_RADIUS + ARENA_SCREEN_OFFSET_Y)};
    float switchPos2[2] = {position[0] - (cos(angle) * BUGGY_SWITCH_RADIUS) + ARENA_SCREEN_OFFSET_X, position[1] - (sin(angle) * BUGGY_SWITCH_RADIUS + ARENA_SCREEN_OFFSET_Y)};

    ProgressBar progressBars[2];

public:
    BuggyController();
    ~BuggyController();

    //-----Functions for buggy simulation-----
    void setupDisplay();
    void drawBuggy(SDL_Renderer *renderer);
    void simulateSwitches();
    void simulateMotors();
    
    //-----Data for buggy simulation-----
    long SDLTicks = SDL_GetTicks();
    Graph graphs[2];

    //-----Data that will be available through the Plymouth Shell board-----
    float motor1PWM, motor2PWM = 0; // 0->1  -- motor1 = left, motor2 = right
    short switch1, switch2 = 0;     // 0, 1  -- switch1 = front, switch2 = back
};

#endif