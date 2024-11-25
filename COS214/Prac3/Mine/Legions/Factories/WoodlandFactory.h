#ifndef WOODLANDFACTORY_H
#define WOODLANDFACTORY_H

#include "LegionFactory.h"
#include "../Units/Infantry.h"
#include "../Units/Cavalry.h"
#include "../Units/Artillery.h"
#include "../Specializations/Woodland.h"

class WoodlandFactory : public LegionFactory
{
public:
  LegionUnit *createInfantry();
  LegionUnit *createCavalry();
  LegionUnit *createArtillery();
  void deployArtillery();
};

#endif