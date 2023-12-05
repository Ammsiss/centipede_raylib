#include <vector>
#include <random>

#include "raylib.h"

namespace Random
{
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<int> angle{1, 5};
}

struct Vector
{
    int x{};
    int y{};
};

class Paddle
{
public:
    Paddle(int x, int y, int moveUp, int moveDown)
    : m_x{ x }, m_y{ y } , m_moveUp{ moveUp }, m_moveDown{ moveDown }
    {
    }

    void update()
    {
        // check for input & update paddle position
        if(IsKeyDown(m_moveUp) && m_y >= 0)
            m_y -= 5;
        if(IsKeyDown(m_moveDown) && m_y <= 650)
            m_y += 5;

        // print rectangle
        DrawRectangle(m_x, m_y, m_dimension.x, m_dimension.y, RED);
    }

    int getY() { return m_y; }

private:
    int m_x{}; 
    int m_y{};
    int m_moveUp{};
    int m_moveDown{};
    Vector m_dimension{10, 150};
};

class Ball
{
public:
    void update(Paddle p1, Paddle p2)
    {
        if(m_position.x == 10)
            movingForward = true;
        
        if(m_position.x == 790)
            movingForward = false;

        if(m_position.x == 40 && m_position.y + 10 >= p1.getY() && m_position.y - 10 <= p1.getY() + 150)
            movingForward = true;

        if(m_position.x == 760 && m_position.y + 10 >= p2.getY() && m_position.y - 10 <= p2.getY() + 150)
            movingForward = false;

        if(movingForward)
            m_position.x += 5;
        else
            m_position.x -= 5;

        DrawCircle(m_position.x, m_position.y, m_radius, RED);
    }

private:
    float m_radius{10.0};
    Vector m_position{ 400, 400 };
    bool movingForward{true};
};

int main() 
{
    InitWindow(800, 800, "Raylib Libraries Test");
    SetTargetFPS(60);

    Paddle p1{20, 400, KEY_W, KEY_S};
    Paddle p2{770, 400, KEY_I, KEY_K};
    Ball ball{};

    while (!WindowShouldClose()) 
    {
        if(IsKeyPressed(KEY_F11))
            ToggleFullscreen();

        BeginDrawing();
        ClearBackground(GRAY);

            p1.update(); 
            p2.update();
            ball.update(p1, p2);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
