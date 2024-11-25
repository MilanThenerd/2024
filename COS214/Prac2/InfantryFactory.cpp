#include "InfantryFactory.h"

Soldiers *InfantryFactory::createUnit()
{
  // health damage defense amount
  Soldiers *infantry = new Infantry(40, 10, 20, 10, "Infantry");
  return infantry;
}

int InfantryFactory::calculateTotalHealthPerUnit()
{
  int sum = 40 * 10;
  return sum;
}

int InfantryFactory::calculateTotalDamagePerUnit()
{
  int sum = 30 * 10;
  return sum;
}

int InfantryFactory::calculateTotalDefencePerUnit()
{
  int sum = 20 * 10;
  return sum;
}