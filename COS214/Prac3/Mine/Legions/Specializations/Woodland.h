#ifndef WOODLAND_H
#define WOODLAND_H

#include <string>

#include "../Units/LegionUnit.h"

class Woodland : public LegionUnit
{
private:
  std::string specilisation = "Woodland";

public:
  Woodland(const LegionUnit &Unit);
  void move();
  void attack();
};

#endif