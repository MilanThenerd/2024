#ifndef LEGIONUNIT_H
#define LEGIONUNIT_H

#include <string>
#include "../../Map/Coords.h"
#include <iostream>

class LegionUnit
{
private:
  int totalHealth;
  int health;
  int defense;
  int damage;
  int speed;
  int range;
  std::string name;
  int owner;
  int unitNumber;
  int moveLeft = 0;

protected:
  std::string specilization = "None";
  bool fortified;

public:
  LegionUnit(int health, int defense, int damage, int speed, int range, std::string name, int owner);
  LegionUnit(const LegionUnit &unit);
  virtual ~LegionUnit() {};
  virtual void attack(LegionUnit *) = 0;
  std::string getName();
  std::string getSpecialization() const;
  int getOwner() const;
  virtual int getRange() const;
  virtual int getDamage() const;
  virtual int getSpeed() const;
  virtual int getHealth() const;
  virtual int getTotalHealth() const;
  virtual int getDefence() const;
  double calculateProwess();
  bool getFortified() const;
  void setFortified(bool);
  virtual void receiveDamage(int damage);
  void setOwner(int);
  void resetMove();
  void move();
  bool canMove();
};

#endif