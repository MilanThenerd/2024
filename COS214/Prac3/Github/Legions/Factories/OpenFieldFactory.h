#ifndef OPENFIELDFACTORY_H
#define OPENFIELDFACTORY_H

#include "LegionFactory.h"
#include "../Units/Infantry.h"
#include "../Units/Cavalry.h"
#include "../Units/Artillery.h"
#include "../Specializations/OpenField.h"

class OpenFieldFactory : public LegionFactory
{
public:
  OpenFieldFactory(int playerNo) : LegionFactory(playerNo) {};
  LegionUnit *createInfantry();
  LegionUnit *createCavalry();
  LegionUnit *createArtillery();
  void deployArtillery();
};

#endif