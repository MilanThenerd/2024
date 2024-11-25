#include "Infantry.h"

Infantry::Infantry(int playerNo) : LegionUnit(250, 100, 150, 1, 1, "Infantry", playerNo)
{
    std::cout << "Created infantry for player " << playerNo << std::endl;
}
