#ifndef BATTLESTRATEGY_H
#define BATTLESTRATEGY_H

#include "../../Map/Coords.h"
class BattleStrategy
{
protected:
  int player;

public:
  BattleStrategy(int p);
  virtual void engage() = 0;
  virtual double getScore(const Coords &c) = 0;
  virtual std::string getDescription() = 0;
  virtual std::string getName() = 0;
  virtual ~BattleStrategy() {};
};

#endif