#ifndef INFANTRYFACTORY_H
#define INFANTRYFACTORY_H

#include "SoldierFactory.h"
#include "Infantry.h"

using namespace std;

class InfantryFactory : public SoldierFactory
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