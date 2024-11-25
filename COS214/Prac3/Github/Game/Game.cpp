#include "Game.h"

void Game::clearScreen()
{
    std::cout << "\x1B[2J\x1B[H";
}

void Game::waitSeconds(int seconds)
{
    unsigned int microsecond = 1000000;
    usleep(seconds * microsecond / speedup);
}

void Game::handlePlayers()
{
    for (auto &player : players)
    {
        player.resetMove();
        clearScreen();
        map->display();
        if (reinforceReccurence > 0)
        {
            if (roundNo % reinforceReccurence == 0)
            {
                player.reinforce();
            }
        }

        while (!player.playRound())
        {
            waitSeconds(1);
            clearScreen();
            map->display();
        }
        waitSeconds(1);
        // waitInput();
        // clearScreen();
        // map->display();
        // waitInput();
        checkWinners();
    }
}

void Game::waitInput()
{
    std::cout << "Press Enter to continue...";
    std::cin.get();
}

void Game::checkWinners()
{
    if (roundNo == 0)
        return;

    if (map->getFriendlyLegions(0).size() == 0)
    {
        running = false;
        clearScreen();
        map->display();
        std::cout << "Player 1 wins!\n";
    }
    else if (map->getFriendlyLegions(1).size() == 0)
    {
        running = false;
        clearScreen();
        map->display();
        std::cout << "Player 0 wins!\n";
    }
}

Game::Game(int playerCount, int recurrence, int x, int y)
{
    this->reinforceReccurence = recurrence;
    this->roundNo = 0;
    map = new Map(x, y);
    players.push_back(Player(map, 0));
    players.push_back(Player(map, 1));
}

void Game::run()
{
    running = true;
    int maxTurns = 1000;
    while (running)
    {
        handlePlayers();
        roundNo++;
        if (roundNo > maxTurns)
        {
            running = false;
        }
    }

    std::cout << "Game has ended!" << std::endl;
}

void Game::setSpeedup(int su)
{
    speedup = su;
}

Game::~Game()
{
    delete map;
}
