#include "SmartThermostatIntegrator.h"

SmartThermostatIntegrator::SmartThermostatIntegrator(LegacyThermostat *thermostat) : SmartThermostat(0)
{
    this->thermostat = thermostat;
    generateId();
}

void SmartThermostatIntegrator::initialize()
{
    setTemperature(thermostat->getTemperature());
}

double SmartThermostatIntegrator::getTemperature()
{
    if (state.getDescription() == "Off")
    {
        std::cout << "SmartThermostat is off. Cannot get temperature." << std::endl;
        return -1;
    }
    return thermostat->getTemperature();
}

void SmartThermostatIntegrator::setTemperature(double target)
{
    if (state.getDescription() == "Off")
    {
        std::cout << "SmartThermostat is off. Cannot set temperature." << std::endl;
        return;
    }
    double temp = thermostat->getTemperature();

    // round target to 1 decimal place
    target = round(target * 10) / 10;

    const double tolerance = 0.01;

    while (fabs(temp - target) > tolerance)
    {
        if (temp < target)
        {
            thermostat->increaseTemperature();
        }
        else
        {
            thermostat->decreaseTemperature();
        }
        temp = thermostat->getTemperature();
    }
}

std::string SmartThermostatIntegrator::printState()
{
    // std::cout << "SmartThermostatIntegrator " << id << ":\t" << state.getDescription();
    // std::cout << "\tTemperature: " << thermostat->getTemperature() << std::endl;
    std::string message = "SmartThermostatIntegrator " + id + ":\t" + state.getDescription() + "\n";
    message += "\tTemperature: " + std::to_string(thermostat->getTemperature());
    std::cout << message << std::endl;
    return message;
}
