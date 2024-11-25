#ifndef MEMENTO_H
#define MEMENTO_H

#include <string>
class Soldiers;
using namespace std;

class Memento
{
private:
    int healthPerSoldier;
    int damagePerSoldier;
    int amountOfSoldiersPerUnit;
    int defencePerSoldier;
    int currentHealth;
    string unitName;
    string playerID;
    Memento(int healthPerSoldier, int damagePerSoldier, int defencePerSoldier, int amountOfSoldiersPerUnit, string unitName, string playerID, int currentHealth);
    friend class Soldiers;
};

#endif