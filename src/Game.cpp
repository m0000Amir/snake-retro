#include "Game.hpp"
#include "utils.hpp"
#include <iostream>

Game::Game()
{
    InitAudioDevice();
    eatSound = LoadSound("../assets/sounds/eat.wav");
    wallSound = LoadSound("../assets/sounds/wall.mp3");
    ostMusic = LoadMusicStream("../assets/sounds/ost.wav");
    PlayMusicStream(ostMusic);
}

Game::~Game()
{
    UnloadSound(eatSound);
    UnloadSound(wallSound);
    UnloadMusicStream(ostMusic);
    CloseAudioDevice();
}

void Game::draw()
{
    food.draw();
    snake.draw();
}

void Game::update()
{
    snake.update();
    checkCollisionWithFood();
    checkCollisionWithEdges();
    checkCollisionWithTail();
    UpdateMusicStream(ostMusic);
}

void Game::checkCollisionWithFood()
{
    if (Vector2Equals(snake.body.front(), food.position))
    {
        food.position = food.generateRandomPos();
        snake.eat();
        PlaySound(eatSound);
        score++;
    }
}

void Game::checkCollisionWithEdges()
{
    if (snake.body.front().x >= CELL_COUNT || snake.body.front().x < 0 ||
        snake.body.front().y >= CELL_COUNT || snake.body.front().y < 0)
    {
        gameOver();
    }
}

void Game::checkCollisionWithTail()
{
    std::deque<Vector2> bodyWithoutHead = snake.body;
    bodyWithoutHead.pop_front();

    if (elementInDeque(snake.body.front(), bodyWithoutHead))
    {
        gameOver();
    }
}

void Game::gameOver()
{
    std::cout << "GAME OVER!" << std::endl;
    PlaySound(wallSound);
    isRunning = false;
}
