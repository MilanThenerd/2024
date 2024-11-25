#ifndef AMBUSH_H
#define AMBUSH_H

#include "BattleStrategy.h"
#include "../../Map/Map.h"

class Ambush : public BattleStrategy
{
private:
    Coords position;
    Map *map;
    Coords best;

public:
    Ambush(Map *, Coords, int);
    virtual void engage();
    virtual double getScore(const Coords &);
    virtual std::string getDescription();
    virtual std::string getName();
    virtual ~Ambush() {}
};

#endif