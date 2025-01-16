// main.cpp
#include "raylib.h"
#include <iostream>
#include <deque>
#include <raymath.h>


// constants
const Color SNAKE_GREEN = {32, 238, 0, 255};
const Color SNAKE_DARK_GREEN = {3, 25, 0, 255};
const float CELL_SIZE = 30;
const float CELL_COUNT = 25;
const float OFFSET = 75;


// utility function
double lastUpdateTime = 0;
bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}


bool elementInDeque(Vector2 element, std::deque<Vector2> &deque)
{
    for (size_t i = 0; i < deque.size() - 1; i++)
    {
        if (Vector2Equals(deque[i], element)) return true;
    }
    return false;
}


class Snake
{
public:
    std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};

    void draw()
    {
        for (int i = 0; i < body.size(); i++)
        {
            int x = body[i].x;
            int y = body[i].y;
            Rectangle rect = Rectangle{
                OFFSET + (float)x * CELL_SIZE,
                OFFSET + (float)y * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE};
            DrawRectangleRounded(rect, 0.5, 8, SNAKE_GREEN);
        }
    }

    void eat()
    {
        body.push_back(Vector2Add(body.back(), direction));
    }

    void update()
    {
        body.pop_back();
        body.push_front(Vector2Add(body.front(), direction));
    }
};


class Food
{
public:
    Vector2 position;
    Texture2D texture;

    // Constructor
    Food() : position(generateRandomPos())
    {
        Image image = LoadImage("graphics/food3.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    // Destructor
    ~Food()
    {
        UnloadTexture(texture);
    }

    void draw()
    {
        DrawTexture(
            texture,
            OFFSET + position.x * CELL_SIZE,
            OFFSET + position.y * CELL_SIZE,
            SNAKE_GREEN
        );
    }

    Vector2 generateRandomPos()
    {
        float x = GetRandomValue(0, CELL_COUNT - 1);
        float y = GetRandomValue(0, CELL_COUNT - 1);
        return Vector2{x, y};
    }
};

class Game
{
public:
    int score = 0;
    bool isRunning = false;
    Snake snake;
    Food food;
    Sound eatSound;
    Sound wallSound;
    Music ostMusic;

    Game()
    {
        InitAudioDevice();
        eatSound = LoadSound("sounds/eat.wav");
        wallSound = LoadSound("sounds/wall.mp3");
        ostMusic = LoadMusicStream("sounds/ost.wav");
        PlayMusicStream(ostMusic);
    }

    ~Game()
    {
        UnloadSound(eatSound);
        UnloadSound(wallSound);
        UnloadMusicStream(ostMusic);
        CloseAudioDevice();
    }



    void draw()
    {
        food.draw();
        snake.draw();
    }

    void update()
    {
        snake.update();
        checkCollisionWithFood();
        checkCollisionWithEdges();
        checkCollisionWithTail();
        UpdateMusicStream(ostMusic);
    }

private:
    void checkCollisionWithFood()
    {
        if (Vector2Equals(snake.body.front(), food.position))
        {
            food.position = food.generateRandomPos();
            snake.eat();
            PlaySound(eatSound);
            score++;
        }
    }

    void checkCollisionWithEdges()
    {
        if (snake.body.front().x >= CELL_COUNT || snake.body.front().x < 0 ||
            snake.body.front().y >= CELL_COUNT || snake.body.front().y < 0)
        {
            gameOver();
        }
    }

    void checkCollisionWithTail()
    {
        std::deque<Vector2> bodyWithoutHead = snake.body;
        bodyWithoutHead.pop_front();

        if (elementInDeque(snake.body.front(), bodyWithoutHead))
        {
            gameOver();
        }
    }

    void gameOver()
    {
        std::cout << "GAME OVER!" << std::endl;
        PlaySound(wallSound);
        isRunning = false;
    }
};

bool colorsEqual(const Color& c1, const Color& c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}


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
    Rectangle playButton = {
        screenWidth / 2 - 100,
        screenHeight / 2 - 25, 200, 50};

    while (!WindowShouldClose())
    {
        // Draw
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

        // Update
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
            DrawText(
                "Play",
                playButton.x + 75,
                playButton.y + 10,
                20,
                buttonTextColor);
            
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
