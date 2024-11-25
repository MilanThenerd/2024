#ifndef INFANTRY_H
#define INFANTRY_H

#include "LegionUnit.h"
#include <iostream>
#include <string>

class Infantry : public LegionUnit
{
public:
  Infantry(int playerNo);
  virtual void attack(LegionUnit *) {};
};
#endif