#ifndef SHIELDBEARERFACTORY_H
#define SHIELDBEARERFACTORY_H

#include "SoldierFactory.h"
#include "ShieldBearer.h"

using namespace std;

class ShieldBearerFactory : public SoldierFactory
{
  private:
    Soldiers* soldiers;
  public:
    Soldiers* createUnit();
    int calculateTotalHealthPerUnit();
    int calculateTotalDamagePerUnit();
    int calculateTotalDefencePerUnit();
};
#endif