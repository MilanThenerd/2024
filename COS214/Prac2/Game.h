#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>

#include "CareTaker.h"
#include "InfantryFactory.h"
#include "BoatmanFactory.h"
#include "ShieldBearerFactory.h"

using namespace std;

class Game
{
private:
  map<string, vector<Soldiers *>> playerSoldiers;
  CareTaker *careTaker;
  map<string, int> currency;
  unordered_set<std::string> defeatedPlayers;
  const int playerAmount;
  const int currencyPerTurn;
  int activePlayer = 1;
  bool running = true;
  int turnNumber = 1;
  int maxTurnNumber = 1;
  int prevTurn = 0;
  const int infantryPrice = 50;
  const int shieldBearerPrice = 40;
  const int boatmanPrice = 75;
  const int timeout = 000000;
  InfantryFactory *infantryFactory;
  ShieldBearerFactory *shieldBearerFactory;
  BoatmanFactory *boatmanFactory;

private:
  void lowerCase(string &word);
  void Menu();
  void attack();
  void buy();
  void list();
  void save();
  void undo();
  void redo();
  void load(int turn);
  void clear();
  void checkWinCondition();

public:
  Game(int player_amount, int currencyPerTurn);
  void run();
  ~Game();
};

#endif