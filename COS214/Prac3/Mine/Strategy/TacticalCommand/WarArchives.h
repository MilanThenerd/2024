#ifndef WARARCHIVES_H
#define WARARCHIVES_H

#include "TacticalMemento.h"

#include <vector>
#include <map>

class WarArchives
{
  private:
    std::map<std::string , TacticalMemento *> Tactics;
  public:
    void addTacticalMemento(TacticalMemento* memento, std::string label);
    void removeTacticalMemento(std::string label);
    TacticalMemento* getTacticalMemento(std::string label);
};

#endif