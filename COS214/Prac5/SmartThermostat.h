/**
 * @class SmartThermostat
 * @brief This class represents a smart thermostat device, inherited from Device.
 * 
 * The SmartThermostat class is used to simulate a smart thermostat that can adjust
 * its temperature and perform actions based on commands.
 */
#ifndef SMARTTHERMOSTAT_H
#define SMARTTHERMOSTAT_H

#include "Device.h"

/**
 * @brief The SmartThermostat class models a smart thermostat device.
 * 
 * This class allows for temperature adjustments and provides functionality to 
 * perform actions related to temperature control.
 */
class SmartThermostat : public Device
{
private:
    double temperature; ///< The current temperature setting of the thermostat.

public:
    /**
     * @brief Constructs a new SmartThermostat object with an initial temperature.
     * 
     * @param temp The initial temperature to set for the thermostat.
     */
    SmartThermostat(double temp);

    /**
     * @brief Performs an action on the smart thermostat based on the provided command.
     * 
     * @param action A string representing the action to be performed (e.g., increase, decrease).
     */
    virtual void performAction(std::string action);

    /**
     * @brief Gets the current temperature of the smart thermostat.
     * 
     * @return The current temperature setting.
     */
    virtual double getTemperature();

    /**
     * @brief Sets the temperature of the smart thermostat.
     * 
     * @param temp The new temperature to set for the thermostat.
     */
    virtual void setTemperature(double temp);

    /**
     * @brief Prints the current state of the smart thermostat as a string.
     * 
     * @return A string representation of the thermostat's state, including its temperature.
     */
    virtual std::string printState();
};

#endif
