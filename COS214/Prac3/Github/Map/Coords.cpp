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

int Coords::getX() const
{
    return x;
}

int Coords::getY() const
{
    return y;
}

Coords Coords::left() const
{
    return Coords(x - 1, y);
}

Coords Coords::right() const
{
    return Coords(x + 1, y);
}

Coords Coords::top() const
{
    return Coords(x, y - 1);
}

Coords Coords::bottom() const
{
    return Coords(x, y + 1);
}

float Coords::distance(const Coords &other) const
{
    int dx = abs(x - other.x);
    int dy = abs(y - other.y);
    return dx + dy;
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

bool Coords::operator==(const Coords &other)
{
    return (x == other.x && y == other.y);
}

std::vector<Coords> Coords::getSurroundingCoords() const
{
    std::vector<Coords> result;

    result.push_back(top().left());
    result.push_back(top());
    result.push_back(top().right());

    result.push_back(right());

    result.push_back(bottom().left());
    result.push_back(bottom());
    result.push_back(bottom().right());

    result.push_back(left());

    return result;
}
