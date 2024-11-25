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
  RiverbankFactory(int playerNo) : LegionFactory(playerNo) {};
  LegionUnit *createInfantry();
  LegionUnit *createCavalry();
  LegionUnit *createArtillery();
  void deployArtillery();
};

#endif