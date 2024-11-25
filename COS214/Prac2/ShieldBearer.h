#ifndef SHIELDBEARER_H
#define SHIELDBEARER_H

#include "Soldiers.h"

#include <string>
using namespace std;

class ShieldBearer : public Soldiers
{
  private:
    void prepare();
    void execute();
    void retreat();
    void rest();
  public:
    ShieldBearer(int health , int damage , int defence , int amount , string name) : Soldiers(health , damage , defence, amount , name){};
    Soldiers* clonis();
};
#endif