/**
 * @class SmartThermostatIntegrator
 * @brief This class integrates a LegacyThermostat with SmartThermostat functionality.
 * 
 * The SmartThermostatIntegrator class enables interaction between a smart thermostat
 * and a legacy "dumb" thermostat, allowing the smart thermostat to control and
 * obtain temperature readings from the legacy device.
 */
#ifndef SMARTTHERMOSTATINTEGRATOR_H
#define SMARTTHERMOSTATINTEGRATOR_H

#include "SmartThermostat.h"
#include "LegacyThermostat.h"
#include "cmath"

/**
 * @brief The SmartThermostatIntegrator class bridges a smart thermostat with a legacy thermostat.
 * 
 * This class extends the SmartThermostat and adds capabilities to interact with a 
 * LegacyThermostat, enabling advanced features while maintaining compatibility with older devices.
 */
class SmartThermostatIntegrator : public SmartThermostat
{
private:
    LegacyThermostat *thermostat; ///< A pointer to the legacy thermostat being integrated.

public:
    /**
     * @brief Constructs a new SmartThermostatIntegrator object.
     * 
     * @param thermostat A pointer to the LegacyThermostat to be integrated.
     */
    SmartThermostatIntegrator(LegacyThermostat *thermostat);

    /**
     * @brief Initializes the SmartThermostatIntegrator.
     * 
     * This method sets up the integration with the legacy thermostat, preparing it for use.
     */
    void initialize();

    /**
     * @brief Gets the current temperature from the integrated legacy thermostat.
     * 
     * @return The current temperature reading from the legacy thermostat.
     */
    double getTemperature();

    /**
     * @brief Sets the temperature of the integrated legacy thermostat.
     * 
     * This method updates the temperature setting on the legacy thermostat.
     * 
     * @param temp The new temperature to set on the legacy thermostat.
     */
    void setTemperature(double temp);

    /**
     * @brief Prints the current state of the integrated smart thermostat.
     * 
     * @return A string representation of the state, including the temperature setting 
     * from the legacy thermostat.
     */
    std::string printState();
};

#endif
