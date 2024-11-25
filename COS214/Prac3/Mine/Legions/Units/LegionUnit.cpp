#include "LegionUnit.h"

LegionUnit::LegionUnit(int health, int defense, int damage, int speed, int range, std::string name)
{
  this->health = health;
  this->defense = defense;
  this->damage = damage;
  this->speed = speed;
  this->range = range;
  this->name = name;
}

LegionUnit::LegionUnit(const LegionUnit &unit)
{
  this->health = unit.health;
  this->damage = unit.damage;
  this->defense = unit.defense;
  this->speed = unit.speed;
  this->range = unit.range;
  this->name = unit.name;
}