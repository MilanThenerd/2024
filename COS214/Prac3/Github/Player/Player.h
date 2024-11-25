#ifndef PLAYER_H
#define PLAYER_H

#include "../Map/Map.h"
#include "../Strategy/TacticalCommand/TacticalCommand.h"
#include "iostream"
#include "../Legions/Units/LegionUnit.h"
#include <cstdlib>
#include "../Legions/Factories/OpenFieldFactory.h"
#include "../Legions/Factories/RiverbankFactory.h"
#include "../Legions/Factories/WoodlandFactory.h"

class Player
{
private:
    int playerNo;
    Map *gameMap;
    TacticalCommand command;
    OpenFieldFactory ofFactory;
    RiverbankFactory rbFactory;
    WoodlandFactory wlFactory;

public:
    Player(Map *, int);
    bool playRound();
    void reinforce();
    void resetMove();
};

#endif