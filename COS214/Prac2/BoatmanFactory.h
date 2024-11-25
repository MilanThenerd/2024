#ifndef BOATMANFACTORY_H
#define BOATMANFACTORY_H

#include "SoldierFactory.h"
#include "Boatman.h"

using namespace std;

class BoatmanFactory : public SoldierFactory
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