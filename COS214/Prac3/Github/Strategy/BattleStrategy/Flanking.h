#ifndef FLANKING_H
#define FLANKING_H

#include "BattleStrategy.h"
#include "../../Map/Map.h"

class Flanking : public BattleStrategy
{
private:
    Coords position;
    Map *map;
    Coords best;

public:
    Flanking(Map *, Coords, int);
    virtual void engage();
    virtual double getScore(const Coords &);
    virtual std::string getDescription();
    virtual std::string getName();
    virtual ~Flanking() {}
};
#endif