#include "Move.h"

Move::Move(Map *m, Coords startPos, int playerNo) : BattleStrategy(playerNo)
{
    position = startPos;
    best = startPos;
    map = m;
}

void Move::engage()
{
    if (position == best)
    {
        std::cout << "Tried to move but startPos==endPos" << std::endl;
        return;
    }
    LegionUnit *u = map->getLegionUnit(position);
    u->setFortified(false);
    map->setLegionUnit(position, nullptr);
    map->setLegionUnit(best, u);
    u->move();
}

double Move::getScore(const Coords &)
{
    if (!map->getLegionUnit(position)->canMove())
    {
        return 0.0;
    }

    double leastDistance = __FLT_MAX__;

    std::vector<Coords> enemies = map->getEnemyLegions(player);

    for (auto &c : position.getSurroundingCoords())
    {
        for (auto &enemy : enemies)
        {
            LegionUnit *lu = map->getLegionUnit(c);

            if (lu != nullptr)
            {
                if (!map->validCoords(c))
                    continue;
                if (lu->getOwner() != player)
                    continue;
            }

            if (c.distance(enemy) < leastDistance)
            {
                leastDistance = c.distance(enemy);
                best = c;
            }
        }
    }

    return std::max(5.0 - leastDistance, 0.0);
}

Coords Move::getBestCoords()
{
    return best;
}

std::string Move::getDescription()
{
    LegionUnit *lu = map->getLegionUnit(position);
    std::string result;
    result += lu->getName() + " at " + position.toString() + " will move to " + best.toString();
    return result;
}

std::string Move::getName()
{
    return "Move";
}
