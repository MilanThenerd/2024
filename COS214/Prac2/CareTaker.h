#ifndef CARETAKER_U
#define CARETAKER_U

#include <vector>
#include <map>
#include "Memento.h"
#include "Soldiers.h"

class CareTaker
{
private:
    map<int, map<string, vector<Memento *>>> gameState;
    map<int, map<string, int>> currencyState;

public:
    void addGameState(map<string, vector<Soldiers *>> currentState, map<string, int> currencyState, int round);
    void removeGameState(int turnNo);
    void applyGameState(map<string, vector<Soldiers *>> &playerSoldiers, map<string, int> &currency, int turnNo);
    map<string, vector<Memento *>> getGameState(int turnNo);
    map<string, int> getCurrencyState(int turnNo);
    ~CareTaker();
};

#endif