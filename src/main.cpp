#include "raylib.h"

int main(int argc, const char** argv) {
    int screenWidth = 512;
    int screenHeight = 512;

    InitWindow(screenWidth, screenHeight, "New Game");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update Here

        BeginDrawing();
        {
            ClearBackground(BLACK);
            DrawText("My new game", 10, 10 , 10, WHITE);
        }
        EndDrawing();
    }   

    CloseWindow();
    return 0;
}