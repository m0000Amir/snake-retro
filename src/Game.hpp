#pragma once

#include "Snake.hpp"
#include "Food.hpp"
#include "raylib.h"
#include <raymath.h>

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

    Game();
    ~Game();

    void draw();
    void update();

private:
    void checkCollisionWithFood();
    void checkCollisionWithEdges();
    void checkCollisionWithTail();
    void gameOver();
};
