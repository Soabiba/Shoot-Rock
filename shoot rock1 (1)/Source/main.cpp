#include "global.h"
#include "init.cpp"
#include "update.cpp"
#include "draw.cpp"
#include "unload.cpp"

int main()
{
    screenWidth = 600;
    screenHeight = 700;
    InitWindow(screenWidth, screenHeight, "Space Invader - Sample");

    level.InitGame();

    InitAudioDevice();

    SetTargetFPS(60);


    // Main game loop
    while (!WindowShouldClose())
    {
        // Update and Draw
        level.UpdateDrawFrame();
    }

    level.UnloadGame();

    CloseWindow();
    return 0;
}

