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
        for(std::size_t i{0}; i < m_mushies.size(); ++i)
        {
            DrawTexture(texture, m_mushies[i].x, m_mushies[i].y, WHITE);
        }
    }

    Point& operator[](std::size_t i)
    {
        return m_mushies[i];
    }

    std::vector<Point>& getMushies()
    {
        return m_mushies;
    }

private:
    std::vector<Point> m_mushies{Point{200, 100}, Point{400, 100}, Point{600, 100}};
};

class Shooter
{
public:
    Shooter()
    {
    }

    void update(Mushroom& mushies, Texture2D texture2, Texture2D texture3, Sound lazer)
    {
        checkInput();
        checkShoot(texture3, lazer);
        checkMushroom(mushies);
        DrawTexture(texture2, m_position.x, m_position.y, WHITE);
    }

private:
    Point m_position{400, 700};
    std::vector<Point> m_shotPosition{};

    void checkMushroom(Mushroom& mushies)
    {
        for(std::size_t i{mushies.getMushies().size() - 1}; static_cast<int>(i) >= 0; --i)
        {
            for(std::size_t i2{0}; i2 < m_shotPosition.size(); ++i2)
            {
                if(m_shotPosition[i2].y == mushies.getMushies()[i].y && m_shotPosition[i2].x >= mushies.getMushies()[i].x && m_shotPosition[i2].x <= mushies.getMushies()[i].x + 15)
                    mushies.getMushies().erase(mushies.getMushies().begin() + i);
            }
        }

        DrawText(std::to_string(mushies.getMushies().size()).c_str(), 1, 50, 50, RED);
    }

    void checkInput()
    {
        if(IsKeyDown(KEY_W))
        {
            if(m_position.y >= 600)
                m_position.y -= 2;
        }

        if(IsKeyDown(KEY_S))
        {
            if(m_position.y <= 765)
                m_position.y += 2;
        }

        if(IsKeyDown(KEY_A))
        {
            if(m_position.x >= 5)
                m_position.x -= 2;
        }

        if(IsKeyDown(KEY_D))
        {
            if(m_position.x <= 765)
                m_position.x += 2;
        }
    }

    void checkShoot(Texture2D texture3, Sound lazer)
    {
        if(IsKeyPressed(KEY_SPACE))
        {   
            PlaySound(lazer);
            m_shotPosition.emplace_back(Point{m_position.x, m_position.y});
        }

        for(auto& shot : m_shotPosition)
        {
            DrawTexture(texture3, shot.x + 10, shot.y, WHITE);
            shot.y -= 3;
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
    SetTargetFPS(144);

    InitAudioDevice();
    SetMasterVolume(5);

    Sound lazer{LoadSound("sounds/shoot.mp3")};

    Shooter player{};
    Mushroom mushies{};

    Texture2D texture{ 0 };
    Texture2D texture2{ 0 };
    Texture2D texture3{ 0 };

    if(argc > 1)
    {
        Image myImage{LoadImage(argv[1])};
        if (myImage.data != NULL)
        {
            texture = LoadTextureFromImage(myImage);
            UnloadImage(myImage);
        }

        Image myImageShooter{LoadImage(argv[2])};
        if (myImageShooter.data != NULL)
        {
            texture2 = LoadTextureFromImage(myImageShooter);
            UnloadImage(myImageShooter);
        }

        Image myImageShot{LoadImage(argv[3])};
        if (myImageShot.data != NULL)
        {
            texture3 = LoadTextureFromImage(myImageShot);
            UnloadImage(myImageShot);
        }
        
    }

    while(!WindowShouldClose())
    {
        if(IsKeyPressed(KEY_F11))
            ToggleFullscreen();

        BeginDrawing();
        ClearBackground(BLACK);

            player.update(mushies, texture2, texture3, lazer);
            mushies.drawMushies(texture);

        EndDrawing();
    }   

    if(texture.id != 0)
    {
        UnloadTexture(texture);
    }

    if(texture2.id != 0)
    {
        UnloadTexture(texture2);
    }

    if(texture3.id != 0)
    {
        UnloadTexture(texture3);
    }

    UnloadSound(lazer);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
