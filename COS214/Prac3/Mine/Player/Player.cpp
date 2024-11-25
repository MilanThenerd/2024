#include "Player.h"

Player::Player(Map *map, int player)
{
    playerNo = player;
    gameMap = map;
    strategy = nullptr;
}

void Player::playRound()
{
    std::cout << "Player " << playerNo << " is playing a round!" << std::endl;
}

void Player::placeUnit(Coords &c, LegionUnit *u)
{
    gameMap->setLegionUnit(c, u);
}
