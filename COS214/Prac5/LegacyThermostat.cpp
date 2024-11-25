#include "LegacyThermostat.h"

LegacyThermostat::LegacyThermostat(double temp)
{
    temperature = temp;
}

double LegacyThermostat::getTemperature()
{
    return temperature;
}

void LegacyThermostat::increaseTemperature()
{
    temperature += 0.1;
}

void LegacyThermostat::decreaseTemperature()
{
    temperature -= 0.1;
}
