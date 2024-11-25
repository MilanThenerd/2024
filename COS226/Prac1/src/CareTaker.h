#ifndef CARETAKER_U
#define CARETAKER_U

#include <vector>
#include <map>
#include "Memento.h"

class CareTaker {
    private:
        map<int, vector<Memento>> gameState;
    public:
        void addGameState(vector<Memento> currentState, int round); 
        void removeGameState(int turnNo);
        void applyGameState(int turnNo);
        vector<Memento> getGameState(int turnNo);
};

#endif