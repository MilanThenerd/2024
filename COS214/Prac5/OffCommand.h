/**
 * @class OffCommand
 * @brief This class represents a command to turn off a device.
 * 
 * The OffCommand class inherits from HomeCommand and is used to execute the action of 
 * turning off a device, such as a light or appliance, in a smart home system.
 */
#ifndef OFFCOMMAND_H
#define OFFCOMMAND_H

#include "HomeCommand.h"

/**
 * @brief The OffCommand class implements the command to switch off a device.
 * 
 * This class provides the functionality to execute the action of turning off a device.
 * It sends the appropriate command to the receiver device when executed.
 */
class OffCommand : public HomeCommand
{
public:
    /**
     * @brief Constructs a new OffCommand object.
     * 
     * Initializes the OffCommand with a receiver device and an optional target.
     * 
     * @param receiver A pointer to the device that will be turned off.
     * @param target An optional target entity, represented as a string (default is an empty string).
     */
    OffCommand(Device *receiver, std::string target = "");

    /**
     * @brief Executes the off command on the device.
     * 
     * This function triggers the action to turn off the associated device. 
     * It communicates with the receiver device to change its state to off.
     */
    void execute();
};

#endif
