#include <iostream>
#include <sstream>
#include "Game.h"
#include <limits>

using namespace std;
void simulateCin(const string &input)
{
    // Save the original cin buffer
    streambuf *original_cin_buf = cin.rdbuf();

    try
    {
        // Redirect cin to read from the input string
        istringstream input_stream(input);
        cin.rdbuf(input_stream.rdbuf());

        // Your game logic here, e.g., creating and running the game
        Game *game = new Game(2, 10);
        game->run();
        delete game;
    }
    catch (...)
    {
        // Ensure the original buffer is restored even if an exception occurs
        cin.rdbuf(original_cin_buf);
        throw; // Re-throw to maintain exception safety
    }

    // Restore the original cin buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.rdbuf(original_cin_buf);
}

void simulateGames()
{
    simulateCin("redo\nundo\nbuy\ninfantry\n\nbuy\nshieldbearer\n\nundo\nredo\nattack\ninfantry-0\n2\nshieldbearer-1\nyes\nyes\nyes\nyes\nyes\nyes\nyes\nyes\n\nattack\nattack\nshieldbearer-1\n1\n");
    simulateCin("skip\nskip\nskip\nskip\nskip\nskip\nbuy\nboatman\n\nskip\nattack\nboatman-2\n2\n");
    simulateCin("skip\nskip\nskip\nskip\nskip\nskip\nbuy\nboatman\n\nbuy\ninfantry\n\nattack\nboatman-3\n2\ninfantry-4\nno\n\nattack\ninfantry-4\n1\nboatman-3\nno\n\nundo\nundo\nredo\nredo\n\nskip\n\n\nattack\ninfantry-4\n1\nboatman-3\nyes\nyes\nyes\nyes\nyes\nyes\nskip\nattack\ninfantry-4\n1\n");
    simulateCin("attack\nbuy\nback\nbuy\ninfantries\ninfantry\nundo\nundo\nundo\nredo\nredo\nlist\nattack\ninfatry-0\n2\nyes\nyes\nno\nstop\n");
    simulateCin("attack\nbuy\nback\nskip\nskip\nskip\nskip\nskip\nskip\nskip\nbuy\ninfantries\nBoatMan\nundo\nundo\nundo\nredo\nredo\nList\n");
}

int main()
{
    simulateGames();
    return 0;
}