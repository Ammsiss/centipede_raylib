#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

#include "raylib.h"

struct Point
{
    int x{};
    int y{};
};

class Mushroom
{
public:
    void drawMushies(Texture2D texture)
    {
        for(std::size_t i{0}; i < mushies.size(); ++i)
        {
            DrawTexture(texture, mushies[i].x, mushies[i].y, WHITE);
        }
    }

private:
    std::array<Point, 3> mushies{Point{200, 100}, Point{400, 100}, Point{600, 100}};
};

class Shooter
{
public:
    Shooter()
    {
    }

    void update(Mushroom& mushies)
    {
        checkInput();
        checkShoot();
        checkMushroom(mushies);
        DrawRectangle(m_position.x, m_position.y, 30, 30, RED);
    }

private:
    Point m_position{400, 700};
    std::vector<Point> m_shotPosition{};

    void checkMushroom(Mushroom& mushies)
    {

    }

    void checkInput()
    {
        if(IsKeyDown(KEY_W))
        {
            if(m_position.y >= 600)
                m_position.y -= 5;
        }

        if(IsKeyDown(KEY_S))
        {
            if(m_position.y <= 765)
                m_position.y += 5;
        }

        if(IsKeyDown(KEY_A))
        {
            if(m_position.x >= 5)
                m_position.x -= 5;
        }

        if(IsKeyDown(KEY_D))
        {
            if(m_position.x <= 765)
                m_position.x += 5;
        }
    }

    void checkShoot()
    {
        if(IsKeyPressed(KEY_SPACE))
        {   
            m_shotPosition.emplace_back(Point{m_position.x, m_position.y});
        }

        for(auto& shot : m_shotPosition)
        {
            DrawCircle(shot.x + 15, shot.y, 10, RED);
            shot.y -= 7;
        }

        m_shotPosition.erase
        (
            std::remove_if
            (
                m_shotPosition.begin(), m_shotPosition.end(),
                    [](const Point &shot)
                    { 
                        return shot.y <= -5; 
                    }
            ),
            m_shotPosition.end()
        );

        DrawText(std::to_string(m_shotPosition.size()).c_str(), 1, 1, 50, RED);
    }
};

int main(int argc, char *argv[])
{
    InitWindow(800, 800, "block shooter");
    SetTargetFPS(60);

    Shooter player{};
    Mushroom mushies{};

    Texture2D texture{ 0 };

    if(argc > 1)
    {
        Image myImage{LoadImage(argv[1])};
        if (myImage.data != NULL)
        {
            texture = LoadTextureFromImage(myImage);
            UnloadImage(myImage);
        }
    }

    while(!WindowShouldClose())
    {
        if(IsKeyPressed(KEY_F11))
            ToggleFullscreen();

        BeginDrawing();
        ClearBackground(BLACK);

            player.update(mushies);
            mushies.drawMushies(texture);

        EndDrawing();
    }   

    if(texture.id != 0)
    {
        UnloadTexture(texture);
    }

    CloseWindow();
    return 0;
}
