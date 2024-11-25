#include "Infantry.h"
#include <iostream>
using namespace std;

void Infantry::prepare()
{
    cout << "Infantry are raising their weapons!" << endl;
}

void Infantry::execute()
{
    cout << "Infantry are charging!" << endl;
}

void Infantry::retreat()
{
    cout << "Infantry falling back!" << endl;
}

void Infantry::rest()
{
    cout << "Infantry are patching up." << endl;
}

void Infantry::engage()
{
    prepare();
    execute();
}

void Infantry::disengage()
{
    retreat();
    rest();
}

Soldiers *Infantry::clonis()
{
    Soldiers *newSoldier = new Infantry(
        this->getHealthPerSoldier(),
        this->getDamagePerSoldier(),
        this->getDefencePerSoldier(),
        this->getAmountOfSoldiers(),
        this->getUnitName());
    return newSoldier;
}
