#ifndef CAVALRY_H
#define CAVALRY_H

#include "LegionUnit.h"

#include <string>

class Cavalry : public LegionUnit
{
public:
  Cavalry() : LegionUnit(200, 100, 200, 2, 1, "Cavalry") {};
  void attack() {};
  void move() {};
};
#endif