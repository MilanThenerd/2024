#ifndef MAP_H
#define MAP_H

#include <string>
#include "../Legions/Units/LegionUnit.h"
#include "../Legions/Units/LegionGroup.h"
#include "Coords.h"
#include <map>
#include <iostream>
#include <vector>
class Map
{

private:
    int width;
    int height;
    const int cellWidth = 13;
    const int cellPadding = 1;
    std::pair<Coords, LegionUnit *> *legionUnitMap;
    std::string *terrainMap;
    std::string getTerrain();

public:
    Map(int, int);
    void setLegionUnit(Coords &, LegionUnit *);
    LegionUnit *getLegionUnit(Coords &);
    std::string getTerrainString(Coords &);
    void display();
    std::string padString(std::string, int);
    std::vector<Coords> getFriendlyLegions(int playerNo);
    std::vector<Coords> getEnemyLegions(int playerNo);
    std::vector<Coords> getOpenCoords(int playerNo);
    bool validCoords(const Coords &) const;
    int getWidth();
};

#endif