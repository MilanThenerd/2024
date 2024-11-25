#ifndef WARARCHIVES_H
#define WARARCHIVES_H

#include "../BattleStrategy/BattleStrategy.h"
#include "TacticalMemento.h"
#include "iostream"
#include <vector>
#include <map>

class WarArchives
{
private:
    std::map<int, std::vector<TacticalMemento *>> history;

public:
    WarArchives() {}
    void addTacticalMemento(TacticalMemento *memento, int playerNo);
    void removeTacticalMemento(int playerNo);
    TacticalMemento *getLast(int playerNo);
    std::vector<TacticalMemento *> getAll(int playerNo);
};

#endif