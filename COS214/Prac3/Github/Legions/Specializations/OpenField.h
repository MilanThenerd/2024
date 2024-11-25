#ifndef OPENFIELD_H
#define OPENFIELD_H

#include <string>

#include "../Units/LegionUnit.h"

class OpenField : public LegionUnit
{
public:
  OpenField(const LegionUnit &unit);
  virtual void attack(LegionUnit *enemy)
  {
    std::cout << getName() << " Attacking!\n";
    enemy->receiveDamage(getDamage());
  }
};

#endif