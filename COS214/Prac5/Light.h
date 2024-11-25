/**
 * @class Light
 * @brief This class represents a smart light in the smart home system.
 * 
 * The Light class provides functionality to control smart lights, inheriting from the Device class.
 * It allows the execution of actions like turning the light on or off, and it can display its current state.
 */
#ifndef LIGHT_H
#define LIGHT_H

#include "Device.h"

/**
 * @brief The Light class represents a smart light device in a smart home system.
 * 
 * This class provides implementations for performing actions like turning the light on or off
 * and printing the current state of the light. It inherits from the Device class.
 */
class Light : public Device
{
public:
    /**
     * @brief Constructs a new Light object.
     * 
     * Initializes the Light device with default parameters.
     */
    Light();

    /**
     * @brief Performs an action on the light.
     * 
     * This function allows the light to perform specific actions, such as turning on, turning off, or dimming.
     * 
     * @param action A string representing the action to be performed on the light (e.g., "on", "off", "dim").
     */
    void performAction(std::string action);

    /**
     * @brief Prints the current state of the light.
     * 
     * This function returns a string representation of the light's current state, such as whether it's on or off.
     * 
     * @return A string describing the current state of the light.
     */
    std::string printState();
};

#endif
