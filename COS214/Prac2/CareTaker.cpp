#include "CareTaker.h"
#include <limits>
#include <iostream>
void CareTaker::addGameState(map<string, vector<Soldiers *>> currentState, map<string, int> currency, int turnNo)
{
    int i = turnNo;
    while (this->gameState.count(i))
    {
        this->gameState.erase(i++);
    }

    i = turnNo;
    while (this->currencyState.count(i))
    {
        this->currencyState.erase(i++);
    }

    map<string, vector<Memento *>> mementos;

    for (auto &player : currentState)
    {
        string name = player.first;
        vector<Memento *> vec;
        for (Soldiers *soldier : currentState[name])
        {
            vec.push_back(soldier->militusMemento());
        }
        mementos[name] = vec;
    }

    this->gameState[turnNo] = mementos;
    this->currencyState[turnNo] = currency;
}

void CareTaker::removeGameState(int turnNo)
{
    if (!this->gameState.count(turnNo))
    {
        cout << "Game '" << turnNo << "' not found!" << endl;
        return;
    }

    this->gameState.erase(turnNo);
}

void CareTaker::applyGameState(map<string, vector<Soldiers *>> &playerSoldiers, map<string, int> &currency, int turnNo)
{
    if (!this->gameState.count(turnNo))
    {
        cout << "Game '" << turnNo << "' not found!" << endl;
        cout << "Press enter to continue." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        cin.get();
        return;
    }

    // Process:
    // All troops get 0 health
    for (auto &player : playerSoldiers)
    {
        string name = player.first;
        for (Soldiers *soldier : playerSoldiers[name])
        {
            soldier->damage(2147483647);
        }
    }

    // Set apply memento
    for (auto &player : gameState[turnNo])
    {
        string name = player.first;
        int counter = 0;
        for (Memento *mem : gameState[turnNo][name])
        {
            playerSoldiers[name][counter++]->vivificaMemento(mem);
        }
    }

    currency.clear();
    currency = currencyState[turnNo];
}

map<string, vector<Memento *>> CareTaker::getGameState(int turnNo)
{
    return gameState[turnNo];
}

map<string, int> CareTaker::getCurrencyState(int turnNo)
{
    return currencyState[turnNo];
}

CareTaker::~CareTaker()
{
    for (auto &round : gameState)
    {
        for (auto &player : gameState[round.first])
        {
            for (auto &soldier : player.second)
            {
                delete soldier;
            }
        }
    }
}
