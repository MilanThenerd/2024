#ifndef SOLDIERS_H
#define SOLDIERS_H

#include <string>
#include "Memento.h"
using namespace std;

class Soldiers
{
private:
  int healthPerSoldier;
  int damagePerSoldier;
  int defencePerSoldier;
  int amountOfSoldiersPerUnit;
  int unitHealth;
  string unitName;
  string playerID;
  virtual void prepare() = 0;
  virtual void execute() = 0;
  virtual void retreat() = 0;
  virtual void rest() = 0;

public:
  virtual void engage();
  virtual void disengage();
  virtual Soldiers *clonis() = 0;
  Memento *militusMemento();
  void vivificaMemento(Memento *mem);
  void setPlayerID(string playerID);
  string getPlayerID();
  Soldiers(int health, int damage, int defence, int amount, string name);
  int getHealthPerSoldier();
  int getDamagePerSoldier();
  int getDefencePerSoldier();
  int getAmountOfSoldiers();
  string getUnitName();
  void damage(int damage);
  int getHealth();
  virtual ~Soldiers();

protected:
  int getNextUniqueNumber();
};
#endif