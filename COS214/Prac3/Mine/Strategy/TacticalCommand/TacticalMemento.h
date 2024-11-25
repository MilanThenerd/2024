#ifndef TACTICALMEMENTO_H
#define TACTICALMEMENTO_H

#include "../BattleStrategy/BattleStrategy.h"

class TacticalPlanner;

class TacticalMemento
{
  private:
    BattleStrategy* strategy;
  public:
    TacticalMemento(BattleStrategy* strategy);
    friend class TacticalPlanner;
};
#endif