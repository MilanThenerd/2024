#include <iostream>
#include "Map/Map.h"
#include "Player/Player.h"
#include "Legions/Units/Infantry.h"

int main()
{
    Map *m = new Map(3, 3);

    Player p1 = Player(m, 1);
    p1.playRound();

    Infantry *inf = new Infantry();

    Coords c = Coords(0, 0);

    p1.placeUnit(c, inf);

    m->display();

    delete inf;
    delete m;

    return 0;
}