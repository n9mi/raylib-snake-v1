#include <raylib.h>
#include <iostream>
#include "Game.h"
#include "Config/Screen.h"

namespace RetroSnake
{
    Game::Game()
    {
        m_food = new Food();
        m_snake = new Snake();

        InitWindow(
            Screen::s_cellSize * Screen::s_cellCount, 
            Screen::s_cellSize * Screen::s_cellCount, 
            "Snake");
        SetTargetFPS(60);
        m_isRunning = true;
        
        SetRandomSeed(42);
    }

    Game::~Game()
    {
        delete m_food;
        delete m_snake;
    }

    void Game::updateSnakePerFrame()
    {
        if (m_snake->isFacingUp()) m_snake->moveUp();
        if (m_snake->isFacingDown()) m_snake->moveDown();
        if (m_snake->isFacingRight()) m_snake->moveRight();
        if (m_snake->isFacingLeft()) m_snake->moveLeft();
    }

    bool Game::checkSnakeFoodCollision()
    {
        return m_snake->getHeadPosition().x == m_food->getPositon().x &&
            m_snake->getHeadPosition().y == m_food->getPositon().y;
    }

    bool Game::checkSnakeWallCollision()
    {
        return m_snake->getHeadPosition().x == 0 || m_snake->getHeadPosition().x == (Screen::s_cellCount - 1) ||
            m_snake->getHeadPosition().y == 0 || m_snake->getHeadPosition().y == (Screen::s_cellCount - 1);
    }

    void Game::run()
    {
        while (!WindowShouldClose())
        {
            BeginDrawing();

            ClearBackground(Screen::s_backgroundColor);

            DrawRectangleLinesEx(
                Rectangle{
                    0, 0,
                    Screen::s_cellCount * Screen::s_cellSize,
                    Screen::s_cellCount * Screen::s_cellSize, 
                },
                Screen::s_cellSize,
                SKYBLUE);

            std::string scoreTitle = "score: " + std::to_string(m_score);
            DrawText(
                scoreTitle.c_str(), 
                Screen::s_cellSize + 10, 
                Screen::s_cellSize + 10, 
                20, SKYBLUE);

            m_food->draw();
            m_snake->draw();

            if (IsKeyPressed(KEY_SPACE))
            {
                m_isPlay = true;
            }

            if (m_isPlay)
            {
                Game::trackFps();

                if (Game::isFrameIntervalPassed())
                {
                    updateSnakePerFrame();
                }

                if (checkSnakeFoodCollision())
                {
                    m_score++;

                    Vector2 newFoodPos = {0, 0};
                    do {
                        newFoodPos.x = GetRandomValue(1, Screen::s_cellCount - 2);
                        newFoodPos.y = GetRandomValue(1, Screen::s_cellCount - 2);
                    } while (m_snake->checkIfPositionOccupiedByHeadOrBody(newFoodPos));
                    m_food->setPosition(newFoodPos);
                    m_snake->growTailByOne();
                }
                if (checkSnakeWallCollision())
                {
                    m_score = 0;
                    m_isPlay = false;
                    m_snake->reset();
                    m_food->resetPosition();
                    continue;
                }

                if (IsKeyPressed(KEY_UP) && !m_snake->isVertical())
                {
                    m_snake->moveUp();
                }
                if (IsKeyPressed(KEY_DOWN) && !m_snake->isVertical())
                {
                    m_snake->moveDown();
                }
                if (IsKeyPressed(KEY_RIGHT) && !m_snake->isHorizontal())
                {
                    m_snake->moveRight();
                }
                if (IsKeyPressed(KEY_LEFT) && !m_snake->isHorizontal())
                {
                    m_snake->moveLeft();
                }                    
            } else 
            {
                DrawText(
                    "press [space] to play", 
                    Screen::s_cellSize * Screen::s_cellCount / 4, 
                    Screen::s_cellSize * Screen::s_cellCount / 2, 
                    25, RAYWHITE);
            }

            EndDrawing();
        }

        CloseWindow();
    }

    void Game::trackFps()
    {
        m_fpsCounter++;
        if (m_fpsCounter > 1000) m_fpsCounter = 0;
    }

    bool Game::isFrameIntervalPassed()
    {
        return m_fpsCounter % m_snake->getFrameInterval() == 0;
    }
}