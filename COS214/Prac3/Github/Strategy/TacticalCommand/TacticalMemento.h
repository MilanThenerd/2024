#ifndef TACTICALMEMENTO_H
#define TACTICALMEMENTO_H

// #include "../BattleStrategy/Flanking.h"
// #include "../BattleStrategy/Fortification.h"
// #include "../BattleStrategy/Ambush.h"
// #include "../BattleStrategy/Move.h"
#include "../BattleStrategy/BattleStrategy.h"
#include "iostream"
#include <vector>

class TacticalCommand;

class TacticalMemento
{
private:
    BattleStrategy *strategy;

public:
    TacticalMemento();
    void storeStrategy(BattleStrategy *strategy);

    friend TacticalCommand;
};

#endif