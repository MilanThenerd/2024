#ifndef RIVERBANKFACTORY_H
#define RIVERBANKFACTORY_H

#include "LegionFactory.h"
#include "../Units/Infantry.h"
#include "../Units/Cavalry.h"
#include "../Units/Artillery.h"
#include "../Specializations/Riverbank.h"

class RiverbankFactory : public LegionFactory
{
public:
  LegionUnit *createInfantry();
  LegionUnit *createCavalry();
  LegionUnit *createArtillery();
  void deployArtillery();
};

#endif