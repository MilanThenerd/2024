#include <iostream>
#include "Map/Map.h"
#include "Player/Player.h"
#include "Legions/Units/Infantry.h"
#include "Game/Game.h"

void testBigGame()
{
    for (int i = 0; i < 2; i++)
    {
        Game g(2, i + 1, 6, 4);

        g.setSpeedup(4);
        g.run();
    }
}

void testSmallGame()
{
    for (int i = 0; i < 10; i++)
    {
        Game g(2, 1 + i % 2, 3, 3);

        g.setSpeedup(10000);
        g.run();
    }
}

int main(int argc, const char *argv[])
{
    if (argc > 1)
    {
        if (argv[1] == "demo")
        {
            Game g(2, 2, 6, 4);
            g.run();
        }
    }
    else
    {
        testBigGame();
        testSmallGame();
    }

    return 0;
}