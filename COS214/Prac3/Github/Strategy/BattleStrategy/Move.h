#ifndef MOVE_H
#define MOVE_H

#include "BattleStrategy.h"
#include "../../Map/Map.h"

class Move : public BattleStrategy
{
private:
    Coords position;
    Coords best;
    Map *map;

public:
    Move(Map *, Coords, int);
    virtual void engage();
    virtual double getScore(const Coords &);
    Coords getBestCoords();
    virtual std::string getDescription();
    virtual std::string getName();
    virtual ~Move() {}
};

#endif