#ifndef RIVERBANK_H
#define RIVERBANK_H

#include <string>

#include "../Units/LegionUnit.h"

class Riverbank : public LegionUnit
{
public:
  Riverbank(const LegionUnit &Unit);
  virtual void attack(LegionUnit *enemy)
  {
    std::cout << getName() << " Attacking!\n";
    enemy->receiveDamage(getDamage());
  }
};

#endif