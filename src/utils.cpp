#include "utils.hpp"
#include "raymath.h"

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

bool colorsEqual(const Color& c1, const Color& c2)
{
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}
