#include "buggy_controller.hpp"

#include "progress_bar.hpp"

#include "graph.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <vector>

BuggyController::BuggyController()
{
    SDLTicks = SDL_GetTicks();
}
BuggyController::~BuggyController() {}

void BuggyController::setupDisplay()
{
    progressBars[0] = ProgressBar(33, 30, 150, 30, &motor1PWM, 1);
    progressBars[1] = ProgressBar(216, 30, 150, 30, &motor2PWM, 1);

    graphs[0] = Graph(33, 80, 150, 150, nullptr, nullptr, SDLTicks * SPEED_SCALE - 2000, SDLTicks * SPEED_SCALE + 200, 1.4);
    graphs[1] = Graph(216, 80, 150, 150, nullptr, nullptr, SDLTicks * SPEED_SCALE - 2000, SDLTicks * SPEED_SCALE + 200, 1.4);
}

void BuggyController::simulateMotors()
{

    if ((motor1PWM > 0 && motor2PWM < 0) || (motor1PWM < 0 && motor2PWM > 0))
    {
        double rotation = ((abs(motor1PWM) + abs(motor2PWM)) / 2) * BUGGY_MAX_ROTATION_SPEED;

        if (motor1PWM < motor2PWM)
        { // Rotate counterclockwise depending on motor directions
            rotation *= -1;
        }

        angle += rotation * SPEED_SCALE;
    }

    else
    {
        position[0] += (motor1PWM + motor2PWM) * cos(angle) * BUGGY_MAX_SCREEN_SPEED * SPEED_SCALE;
        position[1] += (motor1PWM + motor2PWM) * sin(angle) * BUGGY_MAX_SCREEN_SPEED * SPEED_SCALE;
    }

    // Keep buggy within bounds on screen
    if (position[0] + BUGGY_WIDTH / 2 > ARENA_SCREEN_WIDTH)
        position[0] = ARENA_SCREEN_WIDTH - BUGGY_WIDTH / 2;
    else if (position[0] - BUGGY_WIDTH / 2 < 0)
        position[0] = BUGGY_WIDTH / 2;
    if (position[1] + BUGGY_WIDTH / 2 > ARENA_SCREEN_HEIGHT)
        position[1] = ARENA_SCREEN_HEIGHT - BUGGY_WIDTH / 2;
    else if (position[1] - BUGGY_WIDTH / 2 < 0)
        position[1] = BUGGY_WIDTH / 2;
}

void BuggyController::simulateSwitches()
{
    switchPos1[0] = position[0] + ARENA_SCREEN_OFFSET_X + (cos(angle) * BUGGY_SWITCH_RADIUS);
    switchPos1[1] = position[1] + ARENA_SCREEN_OFFSET_Y + (sin(angle) * BUGGY_SWITCH_RADIUS);
    switchPos2[0] = position[0] + ARENA_SCREEN_OFFSET_X - (cos(angle) * BUGGY_SWITCH_RADIUS);
    switchPos2[1] = position[1] + ARENA_SCREEN_OFFSET_Y - (sin(angle) * BUGGY_SWITCH_RADIUS);

    if (switchPos1[0] >= ARENA_SCREEN_WIDTH + ARENA_SCREEN_OFFSET_X || switchPos1[0] <= ARENA_SCREEN_OFFSET_X || switchPos1[1] >= ARENA_SCREEN_HEIGHT + ARENA_SCREEN_OFFSET_Y || switchPos1[1] <= ARENA_SCREEN_OFFSET_Y)
        switch1 = 1;
    else
        switch1 = 0;

    if (switchPos2[0] >= ARENA_SCREEN_WIDTH + ARENA_SCREEN_OFFSET_X || switchPos2[0] <= ARENA_SCREEN_OFFSET_X || switchPos2[1] >= ARENA_SCREEN_HEIGHT + ARENA_SCREEN_OFFSET_Y || switchPos2[1] <= ARENA_SCREEN_OFFSET_Y)
        switch2 = 1;
    else
        switch2 = 0;
}

void BuggyController::drawBuggy(SDL_Renderer *renderer)
{
    float screenPos[2] = {position[0] + ARENA_SCREEN_OFFSET_X, position[1] + ARENA_SCREEN_OFFSET_Y};

    SDL_Rect arenaBorderRect = {.x = ARENA_SCREEN_OFFSET_X - 3, .y = ARENA_SCREEN_OFFSET_Y - 3, .w = ARENA_SCREEN_WIDTH + 6, .h = ARENA_SCREEN_HEIGHT + 6};
    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 200);
    SDL_RenderFillRect(renderer, &arenaBorderRect);

    SDL_Rect arenaRect = {.x = ARENA_SCREEN_OFFSET_X, .y = ARENA_SCREEN_OFFSET_Y, .w = ARENA_SCREEN_WIDTH, .h = ARENA_SCREEN_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderFillRect(renderer, &arenaRect);

    filledCircleRGBA(renderer, round(screenPos[0]), round(screenPos[1]), BUGGY_WIDTH / 2, 102, 153, 204, 255);

    Sint16 polygonVerticesX[31], polygonVerticesY[31];
    for (int i = 0; i < 30; i++)
    {
        float theta = (i / 15.0f) - 1.0f;
        polygonVerticesX[i] = screenPos[0] + (BUGGY_WIDTH * 0.51 * cos(angle + theta));
        polygonVerticesY[i] = screenPos[1] + (BUGGY_WIDTH * 0.51 * sin(angle + theta));
    }
    polygonVerticesX[30] = screenPos[0];
    polygonVerticesY[30] = screenPos[1];

    lineRGBA(renderer, screenPos[0], screenPos[1], polygonVerticesX[0], polygonVerticesY[0], 0, 0, 0, 160);
    lineRGBA(renderer, screenPos[0], screenPos[1], polygonVerticesX[29], polygonVerticesY[29], 0, 0, 0, 160);
    filledPolygonRGBA(renderer, &polygonVerticesX[0], &polygonVerticesY[0], 31, 0, 0, 0, 120);

    SDL_Rect switch1Rect = {.x = switchPos1[0] - 5, .y = switchPos1[1] - 5, .w = 10, .h = 10};
    SDL_Rect switch2Rect = {.x = switchPos2[0] - 5, .y = switchPos2[1] - 5, .w = 10, .h = 10};

    switch1 == 1 ? SDL_SetRenderDrawColor(renderer, 0, 255, 0, 200) : SDL_SetRenderDrawColor(renderer, 255, 0, 0, 120);
    SDL_RenderFillRect(renderer, &switch1Rect);

    switch2 == 1 ? SDL_SetRenderDrawColor(renderer, 0, 255, 0, 200) : SDL_SetRenderDrawColor(renderer, 255, 0, 0, 120);
    SDL_RenderFillRect(renderer, &switch2Rect);

    for (int i = 0; i < sizeof(progressBars) / sizeof(ProgressBar); i++)
    {
        progressBars[i].drawProgressBar(renderer);
    }

    for (int i = 0; i < sizeof(graphs) / sizeof(Graph); i++)
    {
        graphs[i].drawGraph(renderer, SDLTicks * SPEED_SCALE);
    }
}