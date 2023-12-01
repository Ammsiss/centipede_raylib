#include "raylib.h"

int main() 
{
    InitWindow(800, 600, "Raylib Libraries Test");

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(GRAY);

        DrawCircle(400, 300, 100.0, RED);
        DrawText("Hello", 100, 50, 12, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
