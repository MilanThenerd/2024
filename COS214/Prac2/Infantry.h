#ifndef INFANTRY_H
#define INFANTRY_H

#include "Soldiers.h"

#include <string>
using namespace std;

class Infantry : public Soldiers
{
private:
  void prepare();
  void execute();
  void retreat();
  void rest();

public:
  Infantry(int health, int damage, int defence, int amount, string name) : Soldiers(health, damage, defence, amount, name) {};
  Soldiers *clonis();
  void engage();
  void disengage();
};
#endif