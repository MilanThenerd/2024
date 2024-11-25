#include "CareTaker.h"

#include <iostream>
void CareTaker::addGameState(vector<Memento> currentState, int turnNo)
{
    cout << "Game saved at turn '" << turnNo << "'." << endl;

    int i = turnNo;
    while(this->gameState.count(i)) {
        this->gameState.erase(i++);
    }

    this->gameState[turnNo] = currentState;
}

void CareTaker::removeGameState(int turnNo)
{
    if(!this->gameState.count(turnNo)) {
        cout << "Game '"<< turnNo <<"' not found!" << endl;
        return;
    }

    this->gameState.erase(turnNo);
    cout << "Game save with name '" << turnNo << "' removed." << endl;
}

void CareTaker::applyGameState(int turnNo)
{
    if(!this->gameState.count(turnNo)) {
        cout << "Game '"<< turnNo <<"' not found!" << endl;
        return;
    }

    cout << "Game save with name '" << turnNo << "' loaded." << endl;
    //TODO: Restore memento
}

vector<Memento> CareTaker::getGameState(int turnNo)
{
    return gameState[turnNo];
}
