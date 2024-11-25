#ifndef FORTIFICATION_H
#define FORTIFICATION_H

#include "BattleStrategy.h"
#include "../../Map/Map.h"

class Fortification : public BattleStrategy
{
private:
    Coords position;
    Map *map;

public:
    Fortification(Map *, Coords, int);
    virtual void engage();
    virtual double getScore(const Coords &);
    virtual std::string getDescription();
    virtual std::string getName();
    virtual ~Fortification() {}
};

#endif