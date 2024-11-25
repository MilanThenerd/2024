#include "MotionSensor.h"

MotionSensor::MotionSensor()
{
    this->type = "MotionSensor";
    this->state = OffState();
    generateId();
}

void MotionSensor::performAction(std::string action)
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

std::string MotionSensor::printState()
{
    std::string message = "MotionSensor " + id + ":\t" + state.getDescription();
    std::cout << message << std::endl;
    return message;
}

void MotionSensor::trigger()
{
    if (state.getDescription() == "Off")
    {
        std::cout << "Motion sensor is off. Cannot trigger." << std::endl;
        return;
    }
    for (auto device : devices)
    {
        device->filterExecute();
    }
}