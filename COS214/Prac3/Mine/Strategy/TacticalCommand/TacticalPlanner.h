#ifndef TACTICALPLANNER_H
#define TACTICALPLANNER_H

#include "../BattleStrategy/BattleStrategy.h"
#include "TacticalMemento.h"

class TacticalPlanner
{
  private:
    BattleStrategy* currentStrategy;
  public:
    TacticalMemento* createMemento();
    void restoreMemento(TacticalMemento memento);
};

#endif