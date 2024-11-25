#ifndef LEGIONGROUP_H
#define LEGIONGROUP_H

#include "LegionUnit.h"
#include <iostream>
#include <string>
#include <vector>

class LegionGroup : public LegionUnit
{
private:
    std::vector<LegionUnit *> units;

public:
    LegionGroup(int playerNo);
    void addUnit(LegionUnit *);
    void removeUnit(LegionUnit *);
    void attack(LegionUnit *);
    void receiveDamage(int damage);
    virtual int getRange() const;
    virtual int getDamage() const;
    virtual int getSpeed() const;
    virtual int getHealth() const;
    virtual int getTotalHealth() const;
    virtual int getDefence() const;
};
#endif