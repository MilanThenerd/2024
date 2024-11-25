#include "ShieldBearer.h"

#include <iostream>
using namespace std;

void ShieldBearer::prepare(){
    cout << "Shieldbearers are raising their shields!" << endl;
}

void ShieldBearer::execute(){
    cout << "Shieldbearers are attacking!" << endl;
}

void ShieldBearer::retreat(){
    cout << "Shieldbearers lowering their shields!" << endl;
}

void ShieldBearer::rest(){
    cout << "Shieldbearers are resting." << endl;
}

Soldiers* ShieldBearer::clonis() {
    Soldiers* newSoldier = new ShieldBearer(
        this->getHealthPerSoldier(),
        this->getDamagePerSoldier(),
        this->getDefencePerSoldier(),
        this->getAmountOfSoldiers(),
        this->getUnitName()
    );
    return newSoldier;
}