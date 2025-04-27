#include "Snake.hpp"
#include "raylib.h"

void Snake::draw()
{
    for (size_t  i = 0; i < body.size(); i++)
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

void Snake::eat()
{
    body.push_back(Vector2Add(body.back(), direction));
}

void Snake::update()
{
    body.pop_back();
    body.push_front(Vector2Add(body.front(), direction));
}
