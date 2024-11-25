#ifndef ARTILLERY_H
#define ARTILLERY_H

#include "LegionUnit.h"

#include <string>

class Artillery : public LegionUnit
{
public:
  Artillery(int playerNo) : LegionUnit(500, 150, 250, 1, 2, "Artillery", playerNo)
  {
    std::cout << "Created artillery for player " << playerNo << std::endl;
  };
  virtual void attack(LegionUnit *enemy) {}
};
#endif