#include "Map.h"
#include "Coords.h"
#include <cstdlib>

std::string Map::getTerrain()
{
    std::string array[] = {"Woodland", "Riverbank", "OpenField"};
    int N = 3;

    return array[rand() % N];
}

Map::Map(int w, int h)
{
    srand(time(nullptr));
    width = w;
    height = h;
    legionUnitMap = new std::pair<Coords, LegionUnit *>[width * height];
    terrainMap = new std::string[width * height];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Coords c = Coords(x, y);
            setLegionUnit(c, nullptr);
            terrainMap[y * width + x] = getTerrain();
        }
    }
}

void Map::setLegionUnit(Coords &c, LegionUnit *u)
{
    legionUnitMap[c.getY() * width + c.getX()].second = u;
}

LegionUnit *Map::getLegionUnit(Coords &c)
{
    if (c.getX() < 0 || c.getX() >= width || c.getY() < 0 || c.getY() >= height)
    {
        return nullptr;
    }
    return legionUnitMap[c.getY() * width + c.getX()].second;
}

std::string Map::getTerrainString(Coords &c)
{
    if (c.getX() < 0 || c.getX() >= width || c.getY() < 0 || c.getY() >= height)
    {
        return "NULL";
    }
    return terrainMap[c.getY() * width + c.getX()];
}

void Map::display()
{
    for (int i = 0; i < (width) * (cellWidth + 2 * cellPadding + 1) + 1; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;

    for (int y = 0; y < height; y++)
    {
        std::cout << "|";

        for (int x = 0; x < width; x++)
        {
            std::string result = padString("", cellWidth + 2 * cellPadding);

            std::cout << result << "|";
        }

        std::cout << std::endl;

        std::cout << "|";

        for (int x = 0; x < width; x++)
        {
            Coords c = Coords(x, y);

            std::string result = c.toString(cellWidth + 2 * cellPadding);

            std::cout << result << "|";
        }

        std::cout << std::endl;

        std::cout << "|";

        for (int x = 0; x < width; x++)
        {
            std::string result = padString("NULL", cellWidth + 2 * cellPadding);

            std::cout << result << "|";
        }

        std::cout << std::endl;

        std::cout << "|";

        for (int x = 0; x < width; x++)
        {
            Coords c = Coords(x, y);
            std::string result = padString(getTerrainString(c), cellWidth + 2 * cellPadding);

            std::cout << result << "|";
        }

        std::cout << std::endl;

        std::cout << "|";

        for (int x = 0; x < width; x++)
        {
            std::string result = padString("", cellWidth + 2 * cellPadding);

            std::cout << result << "|";
        }

        std::cout << std::endl;

        for (int i = 0; i < (width) * (cellWidth + 2 * cellPadding + 1) + 1; i++)
        {
            std::cout << "-";
        }

        std::cout << std::endl;
    }
}

std::string Map::padString(std::string content, int targetLength)
{
    if (static_cast<int>(content.length()) > targetLength)
    {
        throw "Coords.cpp: Coords does not fit in targetLength!";
    }

    if (targetLength % 2 == 0)
    {
        throw "Coords.cpp: targetLength is even, must be odd!";
    }

    int counter = 0;
    while (static_cast<int>(content.length()) < targetLength)
    {
        if (counter % 2 == 0)
        {
            content = ' ' + content;
        }
        else
        {
            content += ' ';
        }
        counter++;
    }

    return content;
}