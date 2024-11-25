#include "Ambush.h"

Ambush::Ambush(Map *m, Coords c, int playerNo) : BattleStrategy(playerNo)
{
    position = c;
    map = m;
    best = c;
}

void Ambush::engage()
{
    if (best == position)
    {
        return;
    }
    LegionUnit *playerUnit = map->getLegionUnit(position);
    LegionUnit *enemy = map->getLegionUnit(best);
    std::cout << "Calling attack\n";
    playerUnit->attack(enemy);

    if (enemy->getHealth() <= 0)
    {
        map->setLegionUnit(best, nullptr);
        // TODO delete enemy
        // delete enemy;
    }
}

double Ambush::getScore(const Coords &)
{
    LegionUnit *playerUnit = map->getLegionUnit(position);

    double unitModifier = ((playerUnit->getSpecialization() == "Woodland") ? 1.5 : 1.25);

    int range = playerUnit->getRange();
    int leastHealth = __INT_MAX__;

    std::vector<Coords> enemies = map->getEnemyLegions(player);

    for (auto &enemy : enemies)
    {
        if (map->getTerrainString(enemy) != "Woodland")
            continue;

        LegionUnit *lu = map->getLegionUnit(enemy);

        if (lu == nullptr)
            continue;

        if (position.distance(enemy) <= range)
        {
            if (lu->getHealth() < leastHealth)
            {
                best = enemy;
                leastHealth = lu->getHealth();
            }
        }
    }

    LegionUnit *lu = map->getLegionUnit(best);

    double score = 0.0;

    if (!(best == position))
    {
        int strength = (lu->getHealth() * (1.0 + static_cast<float>(lu->getDefence()) / 1000.0));
        score = 10 * unitModifier - 5 * (strength - playerUnit->getDamage()) / strength;
    }

    return std::max(score, 0.0);
}

std::string Ambush::getDescription()
{
    std::string result = "Ambush unit on " + best.toString();
    return result;
}

std::string Ambush::getName()
{
    return "Ambush";
}
