#ifndef BATTLESTRATEGY_H
#define BATTLESTRATEGY_H

#include "../../Map/Coords.h"
class BattleStrategy
{
private:
  int player;

public:
  BattleStrategy(int p);
  virtual void engage() = 0;
  virtual double getScore(const Coords &c) = 0;
};

#endif