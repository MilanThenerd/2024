#ifndef RIVERBANK_H
#define RIVERBANK_H

#include <string>

#include "../Units/LegionUnit.h"

class Riverbank : public LegionUnit
{
private:
  std::string specilisation = "Riverbank";

public:
  Riverbank(const LegionUnit &Unit);
  void move() override;
  void attack() override;
};

#endif