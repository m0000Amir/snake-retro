#pragma once

#include "Snake.hpp"
#include "Food.hpp"
#include "raylib.h"
#include <raymath.h>

enum class GameScreen; 

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

    GameScreen* screenState;

    Game(GameScreen* screenState);
    ~Game();

    void draw();
    void update();
    void reset();

private:
    void checkCollisionWithFood();
    void checkCollisionWithEdges();
    void checkCollisionWithTail();
    void gameOver();
};
