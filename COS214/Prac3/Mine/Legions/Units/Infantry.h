#ifndef INFANTRY_H
#define INFANTRY_H

#include "LegionUnit.h"

#include <string>

class Infantry : public LegionUnit
{
public:
  Infantry();
  void attack() {};
  void move() {};
};
#endif