#include "Map.h"
#include "Coords.h"
#include <cstdlib>
#include "../Helpers/Colours.h"

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
    if (u == nullptr)
    {
        legionUnitMap[c.getY() * width + c.getX()].second = u;
        return;
    }

    LegionUnit *lu = legionUnitMap[c.getY() * width + c.getX()].second;

    if (lu != nullptr)
    {
        std::cout << "Merging with " << u->getName() << " of player " << u->getOwner() << std::endl;
        if (lu->getSpecialization() == "Group")
        {
            dynamic_cast<LegionGroup *>(lu)->addUnit(u);
        }
        else
        {
            LegionGroup *lg = new LegionGroup(lu->getOwner());
            lg->addUnit(u);
            lg->addUnit(lu);
            legionUnitMap[c.getY() * width + c.getX()].second = lg;
        }
    }
    else
    {
        legionUnitMap[c.getY() * width + c.getX()].second = u;
    }
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
    std::string colours[] = {"\x1B[46m", "\x1B[45m"};
    std::cout << SetBackBLU << SetForeRED << std::endl;
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
            Coords c(x, y);
            LegionUnit *unit = getLegionUnit(c);

            if (unit != nullptr)
            {
                std::cout << SetBackRED;
                double health = static_cast<float>(unit->getHealth()) / static_cast<float>(unit->getTotalHealth()) * (cellWidth + 2.0);

                int i = 0;
                for (i = 0; i < health; i++)
                {
                    std::cout << " ";
                }
                std::cout << RESETTEXT << SetBackBLU;
                for (; i < cellWidth + 2; i++)
                {
                    std::cout << " ";
                }
                std::cout << "|";
            }
            else
            {
                std::string result = padString("", cellWidth + 2 * cellPadding);
                std::cout << result << "|";
            }
        }

        std::cout << std::endl;

        std::cout << "|";

        for (int x = 0; x < width; x++)
        {
            Coords c(x, y);
            LegionUnit *unit = getLegionUnit(c);

            std::string name = (unit == nullptr) ? "" : unit->getName();

            if (unit != nullptr)
            {
                std::cout << colours[unit->getOwner()];
                if (unit->getFortified())
                {
                    std::cout << SetBOLD;
                }
            }

            std::string result = padString(name, cellWidth + 2 * cellPadding);

            std::cout << result;

            std::cout << RESETTEXT << SetBackBLU << "|";
        }

        std::cout << std::endl;

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

            std::string result = padString(getTerrainString(c), cellWidth + 2 * cellPadding);

            if (getTerrainString(c) == "OpenField")
            {
                std::cout << SetBackYEL;
            }

            if (getTerrainString(c) == "Riverbank")
            {
                std::cout << SetBackWHT;
            }

            if (getTerrainString(c) == "Woodland")
            {
                std::cout << SetBackGRN;
            }

            std::cout << result;

            std::cout << RESETTEXT << SetBackBLU << "|";
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

    std::cout << RESETTEXT << std::endl;
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

std::vector<Coords> Map::getFriendlyLegions(int playerNo)
{
    std::vector<Coords> result;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Coords c = Coords(x, y);
            LegionUnit *lu = getLegionUnit(c);

            if (lu == nullptr)
                continue;

            if (lu->getOwner() == playerNo)
            {
                result.push_back(c);
            }
        }
    }

    return result;
}

std::vector<Coords> Map::getEnemyLegions(int playerNo)
{
    std::vector<Coords> result;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Coords c = Coords(x, y);
            LegionUnit *lu = getLegionUnit(c);

            if (lu == nullptr)
                continue;

            if (lu->getOwner() != playerNo)
            {
                result.push_back(c);
            }
        }
    }

    return result;
}

std::vector<Coords> Map::getOpenCoords(int playerNo)
{
    std::vector<Coords> result;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Coords c = Coords(x, y);
            LegionUnit *lu = getLegionUnit(c);

            if (lu == nullptr)
            {
                result.push_back(c);
            }
            else if (lu->getOwner() == playerNo)
            {
                result.push_back(c);
            }
        }
    }

    return result;
}

bool Map::validCoords(const Coords &c) const
{
    return !(c.getX() < 0 || c.getY() < 0 || c.getX() >= width || c.getY() >= height);
}

int Map::getWidth()
{
    return width;
}
