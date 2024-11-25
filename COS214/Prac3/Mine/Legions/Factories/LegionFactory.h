#ifndef LEGIONFACTORY_H
#define LEGIONFACTORY_H

#include "../Units/LegionUnit.h"

class LegionFactory
{
public:
  virtual LegionUnit *createInfantry() = 0;
  virtual LegionUnit *createCavalry() = 0;
  virtual LegionUnit *createArtillery() = 0;
};

#endif