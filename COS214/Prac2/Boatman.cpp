#include "Boatman.h"
#include <iostream>
using namespace std;
void Boatman::prepare(){
    cout << "Boatmen are raising their flags!" << endl;
}

void Boatman::execute(){
    cout << "Boatmen are attacking!" << endl;
}

void Boatman::retreat(){
    cout << "Boatmen lowering their flags!" << endl;
}

void Boatman::rest(){
    cout << "Boatmen are anchored." << endl;
}

Soldiers* Boatman::clonis() {
    Soldiers* newSoldier = new Boatman(
        this->getHealthPerSoldier(),
        this->getDamagePerSoldier(),
        this->getDefencePerSoldier(),
        this->getAmountOfSoldiers(),
        this->getUnitName()
    );
    return newSoldier;
}