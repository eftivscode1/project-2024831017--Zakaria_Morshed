
#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

int radius = 100;
int initialRadius = 100;
float radiusSpeed = 100.0f; // pixels per second

// Global variables
bool gameIsRunning = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

Uint32 lastTime = 0;
Uint32 currentTime = 0;
float deltaTime = 0;

bool initializeWindow(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        "Task_102",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0);

    if (!window)
    {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }

    return true;
}

void process_input(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            gameIsRunning = false;
        }
    }
}

void drawcircle(int cx, int cy, int r)
{
    for (int y = -r; y <= r; y++)
    {
        for (int x = -r; x <= r; x++)
        {
            if (x * x + y * y <= r * r)
            {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

void update()
{
    currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    radius += radiusSpeed * deltaTime;

    if (radius >= SCREEN_WIDTH / 2 || radius >= SCREEN_HEIGHT / 2)
    {
        radius = initialRadius;
    }
}

void draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    drawcircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, radius);

    SDL_RenderPresent(renderer);
}

void destroyWindow(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char **argv)
{
    gameIsRunning = initializeWindow();
    lastTime = SDL_GetTicks();

    while (gameIsRunning)
    {
        process_input();
        update();
        draw();
    }

    destroyWindow();
    return 0;
}
//g++ task102.cpp -I"C:/Users/mdzak/OneDrive/Desktop/sdl/include" -L"C:/Users/mdzak/OneDrive/Desktop/sdl/lib" -lmingw32 -lSDL2main -lSDL2 -o task102.exe ; ./task102.exe
