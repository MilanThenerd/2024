#ifndef BOATMAN_H
#define BOATMAN_H

#include "Soldiers.h"

#include <string>
using namespace std;

class Boatman : public Soldiers
{
  private:
    void prepare();
    void execute();
    void retreat();
    void rest();
  public:
    Boatman(int health , int damage , int defence , int amount , string name) : Soldiers(health , damage , defence , amount , name){};
    Soldiers* clonis();

};
#endif