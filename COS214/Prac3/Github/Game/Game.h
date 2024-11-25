#ifndef GAME_H
#define GAME_H

#include "../Map/Map.h"
#include "../Strategy/BattleStrategy/BattleStrategy.h"
#include "../Legions/Units/Infantry.h"
#include "../Legions/Units/Cavalry.h"
#include "iostream"
#include "../Player/Player.h"
#include <unistd.h>
#include <vector>

class Game
{
private:
    Map *map;
    int roundNo;
    int speedup = 10;
    int reinforceReccurence = 3;
    bool running = true;
    void clearScreen();
    void waitSeconds(int);
    void handlePlayers();
    std::vector<Player> players;
    void waitInput();
    void checkWinners();

public:
    Game(int pc, int rec, int x, int y);
    void run();
    void setSpeedup(int);
    ~Game();
};

#endif