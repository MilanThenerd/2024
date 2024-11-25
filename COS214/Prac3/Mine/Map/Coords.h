#ifndef COORDS_H
#define COORDS_H
#include <string>

class Coords
{
private:
    int x, y;

public:
    Coords();
    Coords(int x, int y);
    int getX();
    int getY();
    Coords left();
    Coords right();
    Coords top();
    Coords bottom();
    float distance(const Coords &other);
    std::string toString();
    std::string toString(int targetLength);
    bool operator<(const Coords &other);
};

#endif