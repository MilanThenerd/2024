#ifndef OPENFIELD_H
#define OPENFIELD_H

#include <string>

#include "../Units/LegionUnit.h"

class OpenField : public LegionUnit
{
private:
  std::string specilisation = "OpenField";

public:
  OpenField(const LegionUnit &unit);
  void move() override;
  void attack() override;
};

#endif