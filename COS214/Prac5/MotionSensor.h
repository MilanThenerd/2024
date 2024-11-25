/**
 * @class MotionSensor
 * @brief This class represents a motion sensor that can trigger other devices.
 * 
 * The MotionSensor class inherits from the Sensor class and simulates a motion sensor
 * that detects motion and can trigger associated devices to perform actions.
 */
#ifndef MOTIONSENSOR_H
#define MOTIONSENSOR_H

#include "Sensor.h"

/**
 * @brief The MotionSensor class simulates a motion sensor in a smart home system.
 * 
 * This class allows for the detection of motion and can trigger specific actions in other devices
 * when motion is detected. It provides methods to perform actions and print its state.
 */
class MotionSensor : public Sensor
{
public:
    /**
     * @brief Constructs a new MotionSensor object.
     * 
     * Initializes the MotionSensor with default parameters.
     */
    MotionSensor();

    /**
     * @brief Performs an action based on the specified command.
     * 
     * This function allows the motion sensor to perform specific actions, such as turning on lights 
     * or sending alerts, depending on the action specified.
     * 
     * @param action A string representing the action to be performed (e.g., "on", "off").
     */
    void performAction(std::string action);

    /**
     * @brief Prints the current state of the motion sensor.
     * 
     * This function returns a string representation of the motion sensor's current state, 
     * such as whether motion is detected or not.
     * 
     * @return A string describing the current state of the motion sensor.
     */
    std::string printState();

    /**
     * @brief Triggers the motion sensor.
     * 
     * This function simulates the detection of motion and performs any associated actions, 
     * such as activating other devices.
     */
    void trigger();
};

#endif
