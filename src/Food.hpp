#pragma once

#include "raylib.h"
#include "utils.hpp"

class Food
{
public:
    Vector2 position;
    Texture2D texture;

    Food();
    ~Food();

    void draw();
    Vector2 generateRandomPos();
    void reset();
};
