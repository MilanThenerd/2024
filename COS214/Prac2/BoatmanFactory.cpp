#include "BoatmanFactory.h"

Soldiers *BoatmanFactory::createUnit()
{
  // health damage defense amount
  Soldiers *boatman = new Boatman(40, 20, 10, 5, "Boatman");
  return boatman;
}

int BoatmanFactory::calculateTotalHealthPerUnit()
{
  int sum = 40 * 5;
  return sum;
}

int BoatmanFactory::calculateTotalDamagePerUnit()
{
  int sum = 40 * 5;
  return sum;
}

int BoatmanFactory::calculateTotalDefencePerUnit()
{
  int sum = 10 * 5;
  return sum;
}