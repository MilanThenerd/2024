#ifndef PLAYER_H
#define PLAYER_H

#include "../Map/Map.h"
#include "../Strategy/BattleStrategy/BattleStrategy.h"
#include "iostream"
#include "../Legions/Units/LegionUnit.h"

class Player
{
private:
    int playerNo;
    Map *gameMap;
    BattleStrategy *strategy;

public:
    Player(Map *, int);
    void playRound();
    void placeUnit(Coords &, LegionUnit *);
};

#endif