#include "Light.h"

Light::Light()
{
    this->type = "Light";
    this->state = OffState();
    generateId();
}

void Light::performAction(std::string action)
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
        if (act == "on")
        {
            setState(OnState());
        }
        else if (act == "off")
        {
            setState(OffState());
        }
    }
}

std::string Light::printState()
{
    std::string message = "Light " + id + ":\t" + state.getDescription();
    std::cout << message << std::endl;
    return message;
}