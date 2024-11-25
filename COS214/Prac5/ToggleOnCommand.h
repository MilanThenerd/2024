/**
 * @class ToggleOnCommand
 * @brief This class toggles the state of a device to "On" using OnCommand and OffCommand.
 * 
 * The ToggleOnCommand class allows a device to switch between on and off states, 
 * managing the state through OnCommand and OffCommand instances.
 */
#ifndef TOGGLEONCOMMAND_H
#define TOGGLEONCOMMAND_H

#include "HomeCommand.h"
#include "OnCommand.h"
#include "OffCommand.h"

/**
 * @brief The ToggleOnCommand class is responsible for toggling the on state of a device.
 * 
 * This command uses both OnCommand and OffCommand to manage the device's power state, 
 * allowing it to be turned on or off based on the current state.
 */
class ToggleOnCommand : public HomeCommand
{
private:
    bool isOn; ///< Flag indicating whether the device is currently on.
    OnCommand *onCommand; ///< Command to turn the device on.
    OffCommand *offCommand; ///< Command to turn the device off.

public:
    /**
     * @brief Constructs a new ToggleOnCommand object.
     * 
     * @param receiver A pointer to the device that will be controlled.
     * @param isOn A boolean indicating the initial state of the device (true for on, false for off).
     * @param target A string representing the target of the command (default is an empty string).
     */
    ToggleOnCommand(Device *receiver, bool isOn, std::string target = "");

    /**
     * @brief Destroys the ToggleOnCommand object.
     * 
     * This destructor cleans up any allocated resources for the command.
     */
    ~ToggleOnCommand();

    /**
     * @brief Executes the command to toggle the device state.
     * 
     * This method checks the current state and executes either the on or off command 
     * to toggle the device's power state accordingly.
     */
    void execute();
};

#endif
