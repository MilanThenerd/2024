#include "TacticalMemento.h"

TacticalMemento::TacticalMemento()
{
    strategy = nullptr;
}

void TacticalMemento::storeStrategy(BattleStrategy *strat)
{

    strategy = strat;
}