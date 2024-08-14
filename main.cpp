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
float offSet = 75;

double lastUpdateTime = 0;

bool eventTriggered(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

bool elementInDeque(Vector2 element, std::deque<Vector2> deque) {
    for (int i = 0; i < deque.size() - 1; i++) {
        if (Vector2Equals(deque[i], element)) {
            return true;
        }
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
                offSet + (float)x * cellSize, 
                offSet + (float)y * cellSize, 
                cellSize, 
                cellSize
            };
            DrawRectangleRounded(segment, 0.5, 8, green);
        }
    }

    void eat() {
        body.push_back(Vector2Add(body[body.size() - 1], direction));
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
        Image image = LoadImage("graphics/food3.png");
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
            offSet + position.x * cellSize, 
            offSet + position.y * cellSize, 
            green
        );
    }

    Vector2 generateRandomPos() {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }

};


class Game {
public:
    Snake snake = Snake();
    Food food = Food();
    
    void draw() {
        food.draw();
        snake.draw();
    }

    void update() {
        snake.update();
        checkCollisionWithFood();
        checkCollisionWithEdges();
        checkCollisionWithTail();
    }

    void checkCollisionWithFood() {
        if (Vector2Equals(snake.body[0], food.position)) {
            food.position = food.generateRandomPos();
            snake.eat();
        }
    }

    void checkCollisionWithEdges() {
        if (snake.body[0].x == cellCount || snake.body[0].x == -1) {
            gameOver();
        }
        if (snake.body[0].y == cellCount || snake.body[0].y == -1) {
            gameOver();
        }
    }

    void checkCollisionWithTail() {
        std::deque<Vector2> bodyWithoutHead = snake.body;

        bodyWithoutHead.pop_front();

        if (elementInDeque(snake.body[0], bodyWithoutHead)) {
            std::cout << "GAME OVER!" << std::endl;
        }
        
    }

    void gameOver() {
        // snake.reset();
        std::cout << "GAME OVER!" << std::endl;
    }
};

int main() {
    std::cout << "Start!" << std::endl;
    InitWindow(
        2 * offSet + cellSize * cellCount, 
        2 * offSet + cellSize * cellCount, 
        "Snake Retro");
    SetTargetFPS(60);

    // Food food = Food();

    // Snake snake = Snake();

    Game game = Game();
    
    while (!WindowShouldClose()) { 
        // Update
        if (eventTriggered(0.2)) {
            game.update();
        }

        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
            game.snake.direction = {0, -1};
        }

        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
            game.snake.direction = {0, 1};
        }

        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
            game.snake.direction = {1, 0};
        }

        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
            game.snake.direction = {-1, 0};
        }

        // Draw
        BeginDrawing();
        ClearBackground(darkGreen);
        DrawRectangleLinesEx(
            Rectangle{
                offSet - 5, 
                offSet - 5, 
                cellSize * cellCount + 10,
                cellSize * cellCount + 10
            }, 
            5, 
            green);
        // food.draw();
        // snake.draw();
        game.draw();
        int fontSize = 40;
        const char *title = "SNAKE RETRO GAME";
        int textWidth = MeasureText(title, fontSize);
        // int a = MeasureTextEx(title);
        DrawText(title, (2*offSet + cellSize * cellCount - textWidth) / 2, 10, fontSize, green);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
