#include "Memento.h"

Memento::Memento(int healthPerSoldier, int damagePerSoldier, int defencePerSoldier, int amountOfSoldiersPerUnit, string unitName, string playerID, int currentHealth)
{
    this->healthPerSoldier = healthPerSoldier;
    this->damagePerSoldier = damagePerSoldier;
    this->defencePerSoldier = defencePerSoldier;
    this->amountOfSoldiersPerUnit = amountOfSoldiersPerUnit;
    this->unitName = unitName;
    this->playerID = playerID;
    this->currentHealth = currentHealth;
}
