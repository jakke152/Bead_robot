#ifndef PROGRESS_BAR_HPP
#define PROGRESS_BAR_HPP

#include <SDL2/SDL.h>

class ProgressBar
{
private:
    float *linkedValue;
    float maxValue;

    float position[2], size[2];

public:
    ProgressBar();
    ~ProgressBar();
    ProgressBar(float xPos, float yPos, float xSize, float ySize, float *linkedValue, float maxValue);

    void drawProgressBar(SDL_Renderer *renderer);
};

#endif