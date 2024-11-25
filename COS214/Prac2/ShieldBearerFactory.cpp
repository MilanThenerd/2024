#include "ShieldBearerFactory.h"

Soldiers *ShieldBearerFactory::createUnit()
{
  // health damage defense amount
  Soldiers *shieldBearer = new ShieldBearer(80, 7, 40, 10, "ShieldBearer");
  return shieldBearer;
}

int ShieldBearerFactory::calculateTotalHealthPerUnit()
{
  int sum = 80 * 10;
  return sum;
}

int ShieldBearerFactory::calculateTotalDamagePerUnit()
{
  int sum = 10 * 10;
  return sum;
}

int ShieldBearerFactory::calculateTotalDefencePerUnit()
{
  int sum = 40 * 10;
  return sum;
}