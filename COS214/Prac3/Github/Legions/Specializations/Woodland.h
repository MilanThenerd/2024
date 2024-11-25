#ifndef WOODLAND_H
#define WOODLAND_H

#include <string>

#include "../Units/LegionUnit.h"

class Woodland : public LegionUnit
{
public:
  Woodland(const LegionUnit &Unit);
  virtual void attack(LegionUnit *enemy)
  {
    std::cout << getName() << " Attacking!\n";
    enemy->receiveDamage(getDamage());
  }
};

#endif