#ifndef LEGIONUNIT_H
#define LEGIONUNIT_H

#include <string>

class LegionUnit
{
private:
  double health;
  double defense;
  double damage;
  double speed;
  double range;
  std::string name;

public:
  LegionUnit(int health, int defense, int damage, int speed, int range, std::string name);
  LegionUnit(const LegionUnit &unit);
  virtual ~LegionUnit() {};
  virtual void move() = 0;
  virtual void attack() = 0;
};

#endif