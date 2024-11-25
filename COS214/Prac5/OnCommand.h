/**
 * @class OnCommand
 * @brief This class represents a command to turn on a device.
 * 
 * The OnCommand class inherits from HomeCommand and is used to execute the action of 
 * turning on a device, such as a light or appliance, in a smart home system.
 */
#ifndef ONCOMMAND_H
#define ONCOMMAND_H

#include "HomeCommand.h"

/**
 * @brief The OnCommand class implements the command to switch on a device.
 * 
 * This class provides the functionality to execute the action of turning on a device.
 * It sends the appropriate command to the receiver device when executed.
 */
class OnCommand : public HomeCommand
{
public:
    /**
     * @brief Constructs a new OnCommand object.
     * 
     * Initializes the OnCommand with a receiver device and an optional target.
     * 
     * @param receiver A pointer to the device that will be turned on.
     * @param target An optional target entity, represented as a string (default is an empty string).
     */
    OnCommand(Device *receiver, std::string target = "");

    /**
     * @brief Executes the on command on the device.
     * 
     * This function triggers the action to turn on the associated device. 
     * It communicates with the receiver device to change its state to on.
     */
    void execute();
};

#endif
