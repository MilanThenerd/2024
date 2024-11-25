#include "LegionUnit.h"

LegionUnit::LegionUnit(int health, int defense, int damage, int speed, int range, std::string name, int owner)
{
  static int unitNo = 0;
  this->totalHealth = health;
  this->health = health;
  this->defense = defense;
  this->damage = damage;
  this->speed = speed;
  this->range = range;
  this->name = name;
  this->owner = owner;
  this->fortified = false;
  this->unitNumber = unitNo++;
}

LegionUnit::LegionUnit(const LegionUnit &unit)
{
  static int unitNo = 1000;
  this->totalHealth = unit.totalHealth;
  this->health = unit.health;
  this->damage = unit.damage;
  this->defense = unit.defense;
  this->speed = unit.speed;
  this->range = unit.range;
  this->name = unit.name;
  this->fortified = unit.fortified;
  this->unitNumber = unitNo++;
}

std::string LegionUnit::getName()
{
  std::string result = specilization[0] + name;
  if (fortified)
  {
    result = "x";
    result += specilization[0] + name + "x";
  }
  return result;
}

std::string LegionUnit::getSpecialization() const
{
  return specilization;
}

int LegionUnit::getOwner() const
{
  return owner;
}

int LegionUnit::getRange() const
{
  return range;
}

int LegionUnit::getDamage() const
{
  return damage * (fortified ? 0.5 : 1);
}

int LegionUnit::getSpeed() const
{
  return speed;
}

int LegionUnit::getHealth() const
{
  return health;
}

int LegionUnit::getTotalHealth() const
{
  return totalHealth;
}

int LegionUnit::getDefence() const
{
  return defense * (fortified ? 2 : 1);
}

double LegionUnit::calculateProwess()
{
  return getHealth() + getDefence() + getDamage();
}

bool LegionUnit::getFortified() const
{
  return fortified;
}

void LegionUnit::setFortified(bool f)
{
  fortified = f;
}

void LegionUnit::receiveDamage(int damage)
{
  int relativeDamage = damage * std::max((1000.0 - getDefence()) / 1000.0, 0.5);
  health -= relativeDamage;
  // std::cout << getName() << " has " << health << "hp" << std::endl;
}

void LegionUnit::setOwner(int o)
{
  owner = o;
}

void LegionUnit::resetMove()
{
  moveLeft = speed;
}

void LegionUnit::move()
{
  moveLeft--;
}

bool LegionUnit::canMove()
{
  return moveLeft > 0;
}
