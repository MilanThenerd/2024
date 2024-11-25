#include "TacticalPlanner.h"

TacticalMemento* TacticalPlanner::createMemento()
{
  TacticalMemento* memento = new TacticalMemento(this->currentStrategy);
  return memento;
}

void TacticalPlanner::restoreMemento(TacticalMemento memento)
{
  this->currentStrategy = memento.strategy;
}