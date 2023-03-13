#include <SDL2/SDL.h>
#include <iostream>
#include <windows.h>

#include "functions.hpp"

#include "buggy_controller.hpp"

#include "path_executor.hpp"

#include "path_processor.hpp"

bool running, fullscreen;

SDL_Renderer *renderer;
SDL_Window *window;

int frameCount, timerFPS, lastFrame, fps;

static BuggyController buggyController;

static PathExecutor pathExecutor;

void setupSimulation()
{
    buggyController = BuggyController();
    buggyController.setupDisplay();

    static PIDController pidController = PIDController(&buggyController);
    pidController.current[0] = &buggyController.motor1PWM;
    pidController.current[1] = &buggyController.motor2PWM;

    static PathProcessor pathProcessor = PathProcessor(&buggyController, &pidController);

    pathExecutor = PathExecutor(&pathProcessor);

    buggyController.graphs[0].linkedValues[1] = buggyController.graphs[1].linkedValues[1] = pidController.current[0];
    buggyController.graphs[0].linkedValues[0] = &pidController.setPoints[0];
    buggyController.graphs[1].linkedValues[0] = &pidController.setPoints[1];
}

void update()
{
    if (fullscreen)
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    if (!fullscreen)
        SDL_SetWindowFullscreen(window, 0);

    buggyController.simulateMotors();
    buggyController.simulateSwitches();

    if (pathExecutor.linkedPathProcessor->checkSequenceTime())
        pathExecutor.iterateSequence();

    pathExecutor.linkedPathProcessor->linkedPIDController->updatePIDController();
    buggyController.SDLTicks += 17;
    //buggyController.SDLTicks = SDL_GetTicks();
}
void input()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            running = false;
    }
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    if (keystates[SDL_SCANCODE_ESCAPE])
        running = false;
    if (keystates[SDL_SCANCODE_F11])
        fullscreen = !fullscreen;
    if (keystates[SDL_SCANCODE_SPACE])
    {
        setupSimulation();
    }
}
void draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect rect;
    rect.x = rect.y = 0;
    rect.w = SCREEN_WIDTH;
    rect.h = SCREEN_HEIGHT;
    SDL_RenderFillRect(renderer, &rect);

    frameCount++;
    int timerFPS = SDL_GetTicks() - lastFrame;

    buggyController.drawBuggy(renderer);
    
    if (timerFPS < 1000 / 60)
    {
        SDL_Delay((1000 / 60) - timerFPS);
    }

    SDL_RenderPresent(renderer);
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    running = 1;
    fullscreen = 0;
    static int lastTime = 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        std::cout << "Failed at SDL_Init()" << std::endl;
    if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer) < 0)
        std::cout << "Failed at SDL_CreateWindowAndRenderer()" << std::endl;

    SDL_SetWindowTitle(window, "SDL2 Window");
    SDL_ShowCursor(1);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    
    setupSimulation();

    while (running)
    {
        lastFrame = SDL_GetTicks();
        if (lastFrame >= lastTime + 1000)
        {
            lastTime = lastFrame;
            fps = frameCount;
            frameCount = 0;
        }

        std::cout << fps << std::endl;

        update();
        input();
        draw();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}