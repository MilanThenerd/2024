/**
 * @class LegacyThermostat
 * @brief This class represents a legacy or "dumb" thermostat device.
 * 
 * The LegacyThermostat class simulates the behavior of an old-fashioned thermostat that 
 * manually adjusts the temperature without any smart capabilities.
 */
#ifndef LEGACYTHERMOSTAT_H
#define LEGACYTHERMOSTAT_H

/**
 * @brief The LegacyThermostat class simulates a simple thermostat device.
 * 
 * This class allows you to manually control the temperature by increasing or decreasing it. 
 * It holds a temperature value that can be adjusted through its methods.
 */
class LegacyThermostat
{
private:
    double temperature;  ///< Current temperature setting of the thermostat

public:
    /**
     * @brief Constructs a new LegacyThermostat object with an initial temperature.
     * 
     * @param temp Initial temperature value for the thermostat.
     */
    LegacyThermostat(double temp);

    /**
     * @brief Retrieves the current temperature of the thermostat.
     * 
     * This function returns the current temperature setting of the thermostat.
     * 
     * @return The current temperature as a double.
     */
    double getTemperature();

    /**
     * @brief Increases the thermostat's temperature.
     * 
     * This function increases the current temperature setting of the thermostat.
     */
    void increaseTemperature();

    /**
     * @brief Decreases the thermostat's temperature.
     * 
     * This function decreases the current temperature setting of the thermostat.
     */
    void decreaseTemperature();
};

#endif
