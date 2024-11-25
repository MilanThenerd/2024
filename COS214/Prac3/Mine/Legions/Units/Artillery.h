#ifndef ARTILLERY_H
#define ARTILLERY_H

#include "LegionUnit.h"

#include <string>

class Artillery : public LegionUnit
{
public:
  Artillery() : LegionUnit(500, 150, 250, 1, 2, "Artillery") {};
  void attack() {};
  void move() {};
};
#endif