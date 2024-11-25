#include <math.h>
#include <string>
#include "Coords.h"

Coords::Coords()
{
    this->x = -1;
    this->y = -1;
}

Coords::Coords(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Coords::getX()
{
    return x;
}

int Coords::getY()
{
    return y;
}

Coords Coords::left()
{
    return Coords(x - 1, y);
}

Coords Coords::right()
{
    return Coords(x + 1, y);
}

Coords Coords::top()
{
    return Coords(x, y - 1);
}

Coords Coords::bottom()
{
    return Coords(x, y + 1);
}

float Coords::distance(const Coords &other)
{
    float dx = x - other.x;
    float dy = y - other.y;
    return sqrt(dx * dx + dy * dy);
}

std::string Coords::toString()
{
    std::string result = "(";
    result += std::to_string(x);
    result += ",";
    result += std::to_string(y);
    result += ")";
    return result;
}

std::string Coords::toString(int targetLength)
{
    std::string content = toString();

    if (static_cast<int>(content.length()) > targetLength)
    {
        throw "Coords.cpp: Coords does not fit in targetLength!";
    }

    if (targetLength % 2 == 0)
    {
        throw "Coords.cpp: targetLength is even, must be odd!";
    }

    int counter = 0;
    while (static_cast<int>(content.length()) < targetLength)
    {
        if (counter % 2 == 0)
        {
            content = ' ' + content;
        }
        else
        {
            content += ' ';
        }
        counter++;
    }

    return content;
}

bool Coords::operator<(const Coords &other)
{
    return (y * 1000 + x) < (other.y * 1000 + other.x);
}
