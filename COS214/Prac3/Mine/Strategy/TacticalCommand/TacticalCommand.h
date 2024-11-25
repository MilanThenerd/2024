#ifndef TACTICALCOMMAND_H
#define TACTICALCOMMAND_H

#include "../BattleStrategy/Flanking.h"
#include "../BattleStrategy/Fortification.h"
#include "../BattleStrategy/Ambush.h"

class TacticalCommand
{
private:
  BattleStrategy *strategy;

public:
  void setStrategy(BattleStrategy *s);
  void executeStrategy();
  void chooseBestStrategy();
};

#endif