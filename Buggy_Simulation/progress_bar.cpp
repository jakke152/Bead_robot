#include "progress_bar.hpp"

#include <SDL2/SDL.h>

ProgressBar::ProgressBar() {}
ProgressBar::~ProgressBar() {}
ProgressBar::ProgressBar(float xPos, float yPos, float xSize, float ySize, float *value, float max)
{
    linkedValue = value;
    maxValue = max;

    position[0] = xPos;
    position[1] = yPos;
    size[0] = xSize;
    size[1] = ySize;
}

void ProgressBar::drawProgressBar(SDL_Renderer *renderer)
{
    float barLength = abs(*linkedValue) / maxValue;

    SDL_Rect progressBarRects[4] = {
        {.x = position[0], .y = position[1], .w = size[0], .h = size[1]},
        {.x = position[0] + 2, .y = position[1] + 2, .w = size[0] - 4, .h = size[1] - 4},
        {.x = position[0] + 2, .y = position[1] + 2, .w = (size[0] - 4) * barLength, .h = size[1] - 4},
        {.x = position[0] + 2 + (size[0] - 4) * barLength, .y = position[1] + 2, .w = 2, .h = size[1] - 4}};

    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 200);
    SDL_RenderFillRect(renderer, &progressBarRects[0]);

    SDL_SetRenderDrawColor(renderer, 153, 255, 255, 255);
    SDL_RenderFillRect(renderer, &progressBarRects[1]);

    SDL_SetRenderDrawColor(renderer, 50, 205, 50, 255);
    SDL_RenderFillRect(renderer, &progressBarRects[2]);

    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 150);
    SDL_RenderFillRect(renderer, &progressBarRects[3]);
}