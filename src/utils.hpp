#pragma once

#include "raylib.h"
#include <deque>

// constants
const Color SNAKE_GREEN = {32, 238, 0, 255};
const Color SNAKE_DARK_GREEN = {3, 25, 0, 255};
const float CELL_SIZE = 30;
const float CELL_COUNT = 25;
const float OFFSET = 75;

// utility functions
bool eventTriggered(double interval);
bool elementInDeque(Vector2 element, std::deque<Vector2> &deque);
bool colorsEqual(const Color& c1, const Color& c2);
