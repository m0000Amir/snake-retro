#include "Food.hpp"

Food::Food(): position(generateRandomPos())
{
    Image image = LoadImage("../assets/graphics/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

Food::~Food()
{
    UnloadTexture(texture);
}

void Food::draw()
{
    DrawTexture(
        texture,
        OFFSET + position.x * CELL_SIZE,
        OFFSET + position.y * CELL_SIZE,
        SNAKE_GREEN
    );
}

Vector2 Food::generateRandomPos()
{
    float x = GetRandomValue(0, CELL_COUNT - 1);
    float y = GetRandomValue(0, CELL_COUNT - 1);
    return Vector2{x, y};
}

void Food::reset()
{
    UnloadTexture(texture);   // free old texture
    position = generateRandomPos(); // random new position
    Image image = LoadImage("../assets/graphics/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}