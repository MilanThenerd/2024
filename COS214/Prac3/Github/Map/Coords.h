#ifndef COORDS_H
#define COORDS_H
#include <string>
#include <vector>

class Coords
{
private:
    int x, y;

public:
    Coords();
    Coords(int x, int y);
    int getX() const;
    int getY() const;
    Coords left() const;
    Coords right() const;
    Coords top() const;
    Coords bottom() const;
    float distance(const Coords &other) const;
    std::string toString();
    bool operator==(const Coords &other);
    std::vector<Coords> getSurroundingCoords() const;
};

#endif