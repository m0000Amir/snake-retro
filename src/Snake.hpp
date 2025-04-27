#pragma once

#include <deque>
#include "raylib.h"
#include "utils.hpp"
#include <raymath.h>

class Snake
{
public:
    std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};

    void draw();
    void eat();
    void update();
};
