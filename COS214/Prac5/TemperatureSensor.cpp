#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor()
{
    this->type = "TemperatureSensor";
    this->state = OffState();
    generateId();
}

void TemperatureSensor::setTemperature(double t)
{
    temperature = t;
}

double TemperatureSensor::getTemperature()
{
    return temperature;
}

void TemperatureSensor::performAction(std::string action)
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

std::string TemperatureSensor::printState()
{
    // std::cout << "TemperatureSensor " << id << ":\t" << state.getDescription() << std::endl;
    // std::cout << "\tTemperature: " << temperature << std::endl;
    std::string message = "TemperatureSensor " + id + ":\t" + state.getDescription() + "\n";
    message += "\tTemperature: " + std::to_string(temperature);
    std::cout << message << std::endl;
    return message;
}

void TemperatureSensor::trigger()
{
    if (state.getDescription() == "Off")
    {
        std::cout << "Temperature sensor is off. Cannot trigger." << std::endl;
        return;
    }
    for (auto device : devices)
    {
        device->filterExecute(std::to_string(temperature));
    }
}
