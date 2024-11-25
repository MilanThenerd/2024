#ifndef TACTICALCOMMAND_H
#define TACTICALCOMMAND_H

#include "../BattleStrategy/Flanking.h"
#include "../BattleStrategy/Fortification.h"
#include "../BattleStrategy/Ambush.h"
#include "../BattleStrategy/Move.h"
#include "iostream"
#include "WarArchives.h"
#include <vector>

class TacticalCommand
{
private:
  BattleStrategy *strategy;
  Map *map;
  int player;
  WarArchives archives;

public:
  TacticalCommand(Map *map, int playerNo);
  void setStrategy(BattleStrategy *s);
  void executeStrategy();
  BattleStrategy *chooseBestStrategy();
};

#endif