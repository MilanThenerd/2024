/**
 * @class TemperatureSensor
 * @brief This class simulates a temperature sensor that inherits from Sensor.
 * 
 * The TemperatureSensor class is used to read and set temperature values, 
 * as well as trigger actions based on temperature changes.
 */
#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "Sensor.h"

/**
 * @brief The TemperatureSensor class models a temperature sensor device.
 * 
 * This class provides functionality to set and get temperature values, 
 * perform actions based on those values, and trigger notifications to 
 * other devices or commands in the system.
 */
class TemperatureSensor : public Sensor
{
private:
    double temperature; ///< The current temperature reading of the sensor.

public:
    /**
     * @brief Constructs a new TemperatureSensor object with an initial temperature.
     * 
     * This constructor initializes the temperature sensor to a default value.
     */
    TemperatureSensor();

    /**
     * @brief Sets the temperature reading of the sensor.
     * 
     * @param t The temperature value to set for the sensor.
     */
    void setTemperature(double t);

    /**
     * @brief Gets the current temperature reading from the sensor.
     * 
     * @return The current temperature value of the sensor.
     */
    double getTemperature();

    /**
     * @brief Performs an action based on the provided command for the sensor.
     * 
     * @param action A string representing the action to perform (e.g., read, update).
     */
    void performAction(std::string action);

    /**
     * @brief Prints the current state of the temperature sensor.
     * 
     * @return A string representation of the sensor's state, including its current temperature.
     */
    std::string printState();

    /**
     * @brief Triggers an event or notification based on the current temperature reading.
     * 
     * This method can be used to notify other devices or commands when 
     * the temperature exceeds a certain threshold or changes significantly.
     */
    void trigger();
};

#endif
