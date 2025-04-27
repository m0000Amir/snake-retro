#include "raylib.h"
#include "Game.hpp"
#include "utils.hpp"
#include <iostream>

#include <raymath.h>

int main()
{
    std::cout << "Start!" << std::endl;
    InitWindow(
        2 * OFFSET + CELL_SIZE * CELL_COUNT,
        2 * OFFSET + CELL_SIZE * CELL_COUNT,
        "Snake Retro");
    SetTargetFPS(60);
    
    Game game;

    // Button settings
    float screenWidth = 2 * OFFSET + CELL_SIZE * CELL_COUNT;
    float screenHeight = 2 * OFFSET + CELL_SIZE * CELL_COUNT;
    Rectangle playButton = { screenWidth / 2 - 100, screenHeight / 2 - 25, 200, 50 };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(SNAKE_DARK_GREEN);

        DrawRectangleLinesEx(
            Rectangle{
                OFFSET - 5,
                OFFSET - 5,
                CELL_SIZE * CELL_COUNT + 10,
                CELL_SIZE * CELL_COUNT + 10},
            5,
            SNAKE_GREEN);

        DrawText(
            "SNAKE RETRO GAME",
            (screenWidth - MeasureText("SNAKE RETRO GAME", 40)) / 2,
            10,
            40,
            SNAKE_GREEN);

        Vector2 mousePoint = GetMousePosition();
        Color buttonColor = CheckCollisionPointRec(mousePoint, playButton)
                                ? SNAKE_DARK_GREEN
                                : SNAKE_GREEN;
        Color buttonTextColor = colorsEqual(buttonColor, SNAKE_DARK_GREEN)
                                    ? SNAKE_GREEN
                                    : SNAKE_DARK_GREEN;

        if (!game.isRunning)
        {
            DrawRectangleRec(playButton, buttonColor);
            DrawText("Play", playButton.x + 75, playButton.y + 10, 20, buttonTextColor);

            if (CheckCollisionPointRec(mousePoint, playButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                game.isRunning = true;
            }
        }
        else
        {
            game.draw();
            if (eventTriggered(0.2))
            {
                game.update();
            }

            if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
            {
                game.snake.direction = {0, -1};
            }
            if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
            {
                game.snake.direction = {0, 1};
            }
            if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
            {
                game.snake.direction = {1, 0};
            }
            if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
            {
                game.snake.direction = {-1, 0};
            }
        }

        DrawText(
            TextFormat("Score: %i", game.score),
            OFFSET - 5,
            OFFSET + CELL_COUNT * CELL_SIZE + 10,
            40,
            SNAKE_GREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}