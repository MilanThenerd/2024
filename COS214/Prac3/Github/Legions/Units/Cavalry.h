#ifndef CAVALRY_H
#define CAVALRY_H

#include "LegionUnit.h"

#include <string>

class Cavalry : public LegionUnit
{
public:
  Cavalry(int playerNo) : LegionUnit(200, 150, 200, 2, 1, "Cavalry", playerNo)
  {
    std::cout << "Created cavalry for player " << playerNo << std::endl;
  };
  virtual void attack(LegionUnit *enemy)
  {
  }
};
#endif