#include <vector>

#include "raylib.h"

int main() 
{
    InitWindow(800, 600, "Raylib Libraries Test");

    SetTargetFPS(144);

    std::vector<Vector2> storedMousePositions;

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(GRAY);

        if(IsKeyPressed(KEY_F11))
            ToggleFullscreen();

        Vector2 mousePosition{ GetMousePosition() };

        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            storedMousePositions.emplace_back(mousePosition);

        for(std::size_t i{0}; i < storedMousePositions.size(); ++i)
        {
            DrawCircle(storedMousePositions[i].x, storedMousePositions[i].y, 5.0, RED);
        }
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
