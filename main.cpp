// main.cpp
#include "raylib.h"
#include <iostream>
#include <deque>
#include <raymath.h>


// Color green = {173, 204, 96, 255};
// Color green = {28, 207, 0, 255};
Color green = {32, 238, 0, 255};
// Color darkGreen = {43, 51, 24, 255};
Color darkGreen = {3, 25, 0, 255};

float cellSize = 30;
float cellCount = 25;

double lastUpdateTime = 0;

bool eventTriggered(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Snake {
public:
    std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};

    void draw() {
        for (int i = 0; i < body.size(); i++) {
            int x = body[i].x;
            int y = body[i].y;
            Rectangle segment = Rectangle{
                (float)x * cellSize, 
                (float)y * cellSize, 
                cellSize, 
                cellSize
            };
            DrawRectangleRounded(segment, 0.5, 8, green);
        }
    }

    void update() {
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));
    }

};


class Food {
public:
    Vector2 position = generateRandomPos();

    Texture2D texture;

    // Constructor
    Food() {
        Image image = LoadImage("graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    // Destructor
    ~Food() {
        UnloadTexture(texture);
    }

    void draw() {
        // DrawRectangle(
        //     position.x * cellSize, 
        //     position.y * cellSize, 
        //     cellSize, 
        //     cellSize, 
        //     green
        // );
        DrawTexture(
            texture, 
            position.x * cellSize, 
            position.y * cellSize, 
            green
        );
    }

    Vector2 generateRandomPos() {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }

};


int main() {
    std::cout << "Start!" << std::endl;
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Snake Retro");
    SetTargetFPS(60);

    Food food = Food();

    Snake snake = Snake();
    
    while (!WindowShouldClose()) { 
        // Update
        if (eventTriggered(0.2)) {
            snake.update();
        }

        if (IsKeyPressed(KEY_UP)) {
            snake.direction = {0, -1};
        }

        if (IsKeyPressed(KEY_DOWN)) {
            snake.direction = {0, 1};
        }

        if (IsKeyPressed(KEY_RIGHT)) {
            snake.direction = {1, 0};
        }

        if (IsKeyPressed(KEY_LEFT)) {
            snake.direction = {-1, 0};
        }

        // Draw
        BeginDrawing();
        ClearBackground(darkGreen);
        food.draw();
        snake.draw();
        DrawText("AAAAAAAWelcome to Raylib 5.0!`", 190, 200, 20, green);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
