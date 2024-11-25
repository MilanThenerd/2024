#ifndef ATTACK_H
#define ATTACK_H

#include "BattleStrategy.h"
#include "../../Map/Map.h"

class Attack : public BattleStrategy
{
private:
    Coords position;
    Map *map;
    Coords best;

public:
    Attack(Map *, Coords, int);
    virtual void engage();
    virtual double getScore(const Coords &);
    virtual std::string getDescription();
    virtual std::string getName();
    virtual ~Attack() {}
};

#endif