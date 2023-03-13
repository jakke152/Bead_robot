#include "graph.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

Graph::Graph() {}
Graph::~Graph() {}
Graph::Graph(int xPos, int yPos, int xSize, int ySize, float *value1, float *value2, float xMin, float xMax, float yMax_)
{
    linkedValues[0] = value1;
    linkedValues[1] = value2;
    xRange[0] = xMin;
    xRange[1] = xMax;
    yMax = yMax_;

    position[0] = xPos;
    position[1] = yPos;
    size[0] = xSize;
    size[1] = ySize;
}

void Graph::scrollGraphX(float dt)
{
    xRange[0] += dt;
    xRange[1] += dt;
}

void Graph::drawGraph(SDL_Renderer *renderer, float t)
{
    SDL_Rect graphRects[2] = {
        {.x = position[0], .y = position[1], .w = size[0], .h = size[1]},
        {.x = position[0] + 2, .y = position[1] + 2, .w = size[0] - 4, .h = size[1] - 4}};

    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 200);
    SDL_RenderFillRect(renderer, &graphRects[0]);

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderFillRect(renderer, &graphRects[1]);

    if (prevValuesX.size() > 1)
        scrollGraphX(t - prevValuesX[prevValuesX.size() - 1]);

    prevValuesX.push_back(t);

    prevValuesY1.push_back(abs(*linkedValues[0]));
    prevValuesY2.push_back(abs(*linkedValues[1]));

    if (prevValuesX.size() >= 1500)
    {
        prevValuesX.erase(prevValuesX.begin());
        prevValuesY1.erase(prevValuesY1.begin());
        prevValuesY2.erase(prevValuesY2.begin());
    }

    std::vector<int> validIndexes;
    for (int i = 0; i < prevValuesX.size(); i++)
    {
        if (prevValuesX[i] >= xRange[0] && prevValuesX[i] <= xRange[1] &&
            prevValuesY1[i] <= yMax && prevValuesY2[i] <= yMax)
        {
            validIndexes.push_back(i);
        }
    }

    float xScale = (size[0] - 4) / (xRange[1] - xRange[0]);
    float yScale = size[1] - 4;
    for (int i = 1; i < validIndexes.size(); i++)
    {
        thickLineRGBA(renderer, position[0] + (prevValuesX[validIndexes[i] - 1] - xRange[0]) * xScale,
                 position[1] + (size[1] - prevValuesY1[validIndexes[i] - 1] * yScale),
                 position[0] + (prevValuesX[validIndexes[i]] - xRange[0]) * xScale,
                 position[1] + (size[1] - prevValuesY1[validIndexes[i]] * yScale), 2, 0, 191, 255, 180);

        thickLineRGBA(renderer, position[0] + (prevValuesX[validIndexes[i] - 1] - xRange[0]) * xScale,
                 position[1] + (size[1] - prevValuesY2[validIndexes[i] - 1] * yScale),
                 position[0] + (prevValuesX[validIndexes[i]] - xRange[0]) * xScale,
                 position[1] + (size[1] - prevValuesY2[validIndexes[i]] * yScale), 2, 50, 205, 50, 180);
    }
}