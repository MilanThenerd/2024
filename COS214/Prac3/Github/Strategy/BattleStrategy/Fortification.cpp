#include "Fortification.h"

Fortification::Fortification(Map *m, Coords c, int playerNo) : BattleStrategy(playerNo)
{
    this->player = playerNo;
    this->map = m;
    this->position = c;
}

void Fortification::engage()
{
    std::cout << "Fortified!" << std::endl;
    map->getLegionUnit(position)->setFortified(true);
}

double Fortification::getScore(const Coords &c)
{
    LegionUnit *lu = map->getLegionUnit(position);

    if (lu->getFortified())
        return 0.0;

    double combinedEnemyProwess = 0.0;

    for (auto &coord : c.getSurroundingCoords())
    {
        LegionUnit *troop = map->getLegionUnit(coord);

        if (troop == nullptr)
            continue;

        if (troop->getOwner() == player)
            continue;

        combinedEnemyProwess += troop->calculateProwess() * (troop->getFortified() ? 0 : 1);
    }
    double score = 5.0 + 10.0 * (combinedEnemyProwess - lu->calculateProwess()) / lu->calculateProwess();

    return std::max(score, 0.0);
}

std::string Fortification::getDescription()
{
    LegionUnit *lu = map->getLegionUnit(position);

    std::string result;
    result += lu->getName() + " at " + position.toString() + " will fortify.";
    return result;
}

std::string Fortification::getName()
{
    return "Fortification";
}
