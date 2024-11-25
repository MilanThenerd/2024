#include "Player.h"

Player::Player(Map *map, int player) : command(map, player), ofFactory(player), rbFactory(player), wlFactory(player)
{
    std::cout << "Player " << player << " created." << std::endl;
    playerNo = player;
    gameMap = map;
}

bool Player::playRound()
{
    std::cout << "Player " << playerNo << " is playing a round!" << std::endl;
    BattleStrategy *strat = command.chooseBestStrategy();

    if (strat == nullptr)
    {
        std::cout << "We have decided: skip round" << std::endl;
        return true;
    }

    std::cout << "We have decided: " + strat->getDescription() << std::endl;
    command.setStrategy(strat);
    command.executeStrategy();

    return strat->getName() != "Move";
}

void Player::reinforce()
{
    std::cout << "Player " << playerNo << ": We have reinforced our armies!" << std::endl;

    std::vector<Coords> options = std::vector<Coords>(); // = gameMap->getFriendlyLegions(playerNo);

    Coords w;
    if (playerNo == 0)
    {
        w = Coords(0, 0);
    }
    else
    {
        w = Coords(gameMap->getWidth() - 1, 0);
    }

    while (gameMap->validCoords(w))
    {
        options.push_back(w);
        w = w.bottom();
    }

    int rando = rand() % options.size();
    Coords c = options.at(rando);

    LegionUnit *u;

    rando = rand() % 3;

    std::string terrain = gameMap->getTerrainString(c);

    switch (rando)
    {
    case 0:
        if (terrain == "Woodland")
            u = wlFactory.createInfantry();
        if (terrain == "Riverbank")
            u = rbFactory.createInfantry();
        if (terrain == "OpenField")
            u = ofFactory.createInfantry();
        break;
    case 1:
        if (terrain == "Woodland")
            u = wlFactory.createArtillery();
        if (terrain == "Riverbank")
            u = rbFactory.createArtillery();
        if (terrain == "OpenField")
            u = ofFactory.createArtillery();
        break;
    case 2:
        if (terrain == "Woodland")
            u = wlFactory.createCavalry();
        if (terrain == "Riverbank")
            u = rbFactory.createCavalry();
        if (terrain == "OpenField")
            u = ofFactory.createCavalry();
        break;

    default:
        break;
    }

    u->setOwner(playerNo);
    std::cout << "Reinforced at " << c.toString() << " with " << u->getName() << " - " << u->getOwner() << std::endl;

    gameMap->setLegionUnit(c, u);
}

void Player::resetMove()
{
    std::vector<Coords> units = gameMap->getFriendlyLegions(playerNo);

    for (auto &unit : units)
    {
        gameMap->getLegionUnit(unit)->resetMove();
    }
}
