#include "WarArchives.h"

void WarArchives::addTacticalMemento(TacticalMemento* memento , std::string label)
{
  Tactics[label] = std::move(memento);
}

void WarArchives::removeTacticalMemento(std::string label)
{
  auto it = Tactics.find(label);
  if(it != Tactics.end())
  {
    Tactics.erase(label);
  }
}

TacticalMemento* WarArchives::getTacticalMemento(std::string label)
{
  auto it = Tactics.find(label);
  if(it != Tactics.end())
  {
    return it->second;
  }
  return nullptr;
}