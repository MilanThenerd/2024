#include "SmartThermostat.h"

SmartThermostat::SmartThermostat(double temp)
{
    type = "SmartThermostat";
    temperature = temp;
    state = OffState();
    generateId();
}

void SmartThermostat::performAction(std::string action)
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
        else if (act.substr(0, 14) == "setTemperature")
        {
            double temp;
            std::stringstream ss;
            std::string tempStr = act.substr(15);
            ss << tempStr;
            ss >> temp;
            setTemperature(temp);
        }
    }
}

double SmartThermostat::getTemperature()
{
    if (state.getDescription() == "Off")
    {
        std::cout << "SmartThermostat is off. Cannot get temperature." << std::endl;
        return -1;
    }
    return temperature;
}

void SmartThermostat::setTemperature(double temp)
{
    if (state.getDescription() == "Off")
    {
        std::cout << "SmartThermostat is off. Cannot set temperature." << std::endl;
        return;
    }
    temperature = temp;
}

std::string SmartThermostat::printState()
{
    // std::cout << "SmartThermostat " << id << ":\t" << state.getDescription() << std::endl;
    // std::cout << "\tTemperature: " << temperature << std::endl;
    std::string message = "SmartThermostat " + id + ":\t" + state.getDescription() + "\n";
    message += "\tTemperature: " + std::to_string(temperature);
    std::cout << message << std::endl;
    return message;
}
