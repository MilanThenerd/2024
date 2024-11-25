#include "LegionGroup.h"

LegionGroup::LegionGroup(int playerNo) : LegionUnit(0, 0, 0, 1, 0, "Unit", playerNo)
{
    specilization = "Group";
}

void LegionGroup::addUnit(LegionUnit *u)
{
    units.push_back(u);
}

void LegionGroup::removeUnit(LegionUnit *u)
{
    for (auto it = units.begin(); it != units.end(); ++it)
    {
        if (*it == u)
        {
            units.erase(it);
            return;
        }
    }
}

void LegionGroup::attack(LegionUnit *enemy)
{
    std::cout << "Legion group attacking! " << std::endl;
    enemy->receiveDamage(getDamage());
}

void LegionGroup::receiveDamage(int damage)
{
    int relativeDamage = damage * std::max((1000.0 - getDefence()) / 1000.0, 0.5);

    int damagePU = relativeDamage / units.size();

    // std::cout << "Our defence: " << getDefence() << std::endl;

    std::vector<LegionUnit *> toRemove;

    for (auto &u : units)
    {
        u->receiveDamage(damagePU);
        if (u->getHealth() <= 0)
        {
            toRemove.push_back(u);
        }
    }

    while (toRemove.size() > 0)
    {
        removeUnit(toRemove.at(0));
        toRemove.erase(toRemove.begin());
    }
}

int LegionGroup::getRange() const
{
    return 1;
}

int LegionGroup::getDamage() const
{
    double totalDamage = 0.0;

    for (auto &u : units)
    {
        totalDamage += u->getDamage();
    }

    return totalDamage / units.size();
}

int LegionGroup::getSpeed() const
{
    return 1;
}

int LegionGroup::getHealth() const
{
    double totalHealth = 0.0;

    for (auto &u : units)
    {
        if (u == nullptr)
            continue;

        totalHealth += u->getHealth();
    }

    return totalHealth;
}

int LegionGroup::getTotalHealth() const
{
    double totalHealth = 0.0;

    for (auto &u : units)
    {
        totalHealth += u->getTotalHealth();
    }

    return totalHealth;
}

int LegionGroup::getDefence() const
{
    double totalDefence = 0.0;

    for (auto &u : units)
    {
        totalDefence += u->getDefence();
    }

    return totalDefence / units.size() * (fortified ? 2 : 1);
}
