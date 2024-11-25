#include "Soldiers.h"

#include <iostream>
using namespace std;

Memento *Soldiers::militusMemento()
{
    return new Memento(
        this->healthPerSoldier,
        this->damagePerSoldier,
        this->defencePerSoldier,
        this->amountOfSoldiersPerUnit,
        this->unitName,
        this->playerID,
        this->unitHealth);
}

void Soldiers::vivificaMemento(Memento *mem)
{
    this->healthPerSoldier = mem->healthPerSoldier;
    this->damagePerSoldier = mem->damagePerSoldier;
    this->defencePerSoldier = mem->defencePerSoldier;
    this->amountOfSoldiersPerUnit = mem->amountOfSoldiersPerUnit;
    this->unitName = mem->unitName;
    this->playerID = mem->playerID;
    this->unitHealth = mem->currentHealth;
}

Soldiers::Soldiers(int health, int damage, int defence, int amount, string name)
{
    this->healthPerSoldier = health;
    this->damagePerSoldier = damage;
    this->defencePerSoldier = defence;
    this->amountOfSoldiersPerUnit = amount;
    this->unitName = name + "-" + to_string(getNextUniqueNumber());
    unitHealth = healthPerSoldier * amountOfSoldiersPerUnit;
}

void Soldiers::setPlayerID(string playerID)
{
    this->playerID = playerID;
}

string Soldiers::getPlayerID()
{
    return this->playerID;
}

void Soldiers::engage()
{
    cout << "'Soldiers' are to engage in combat." << endl;
}

void Soldiers::disengage()
{
    cout << "'Soldiers' are to disengage." << endl;
}

int Soldiers::getHealthPerSoldier()
{
    return healthPerSoldier;
}

int Soldiers::getDamagePerSoldier()
{
    return damagePerSoldier;
}

int Soldiers::getDefencePerSoldier()
{
    return defencePerSoldier;
}

int Soldiers::getAmountOfSoldiers()
{
    return amountOfSoldiersPerUnit;
}

string Soldiers::getUnitName()
{
    return unitName;
}

void Soldiers::damage(int damage)
{
    unitHealth -= (damage * (100.0 - defencePerSoldier) / 100.0);
    if (unitHealth < 0)
        unitHealth = 0;
}

int Soldiers::getHealth()
{
    return unitHealth;
}

Soldiers::~Soldiers()
{
}

int Soldiers::getNextUniqueNumber()
{
    static int num = 0;
    return num++;
}
