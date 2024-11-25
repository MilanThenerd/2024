#include "WarArchives.h"

void WarArchives::addTacticalMemento(TacticalMemento *memento, int playerNo)
{
    history[playerNo].push_back(memento);
}

void WarArchives::removeTacticalMemento(int playerNo)
{
    history.erase(playerNo);
}

TacticalMemento *WarArchives::getLast(int playerNo)
{
    return history[playerNo].back();
}

std::vector<TacticalMemento *> WarArchives::getAll(int playerNo)
{
    return history[playerNo];
}
