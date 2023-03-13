#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

#include <SDL2/SDL.h>

class Graph
{
private:
    int position[2], size[2];
    float xRange[2];
    float yMax;

    std::vector<float> prevValuesX, prevValuesY1, prevValuesY2;

public:
    Graph();
    ~Graph();
    Graph(int xPos, int yPos, int xSize, int ySize, float *value1, float *value2, float xMin, float xMax, float yMax);

    void scrollGraphX(float dt);
    void drawGraph(SDL_Renderer *renderer, float t);
    
    float *linkedValues[2];
};

#endif