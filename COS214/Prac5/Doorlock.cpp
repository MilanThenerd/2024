#include "Doorlock.h"

Doorlock::Doorlock()
{
    this->type = "Doorlock";
    this->state = LockedState();
    generateId();
}

void Doorlock::performAction(std::string action)
{
    // action is comprised of 2 parts: device id (int) and the action
    // check if the device id is the same as this device before performing the action
    // id of 0 means apply action for all devices

    // get id from action
    std::string id = action.substr(0, action.find(" "));
    // get action from action
    std::string act = action.substr(action.find(" ") + 1);

    if (id == "*" || id == type + "*" || id == this->id)
    {
        std::cout << "The doorlock is performing the action: " << act << std::endl;
        if (act == "lock")
        {
            setState(LockedState());
        }
        else if (act == "unlock")
        {
            setState(OpenState());
        }
    }
}

std::string Doorlock::printState()
{
    std::string message = "Doorlock " + id + ":\t" + state.getDescription();
    std::cout << message << std::endl;
    return message;
}
