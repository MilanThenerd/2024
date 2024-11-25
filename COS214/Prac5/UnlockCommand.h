/**
 * @class UnlockCommand
 * @brief This class represents a command to unlock a device.
 * 
 * The UnlockCommand class is used to issue an unlock command to a device, allowing
 * the device to transition from a locked state to an unlocked state.
 */
#ifndef UNLOCKCOMMAND_H
#define UNLOCKCOMMAND_H

#include "HomeCommand.h"

/**
 * @brief The UnlockCommand class is a concrete command for unlocking devices.
 * 
 * This command is part of the command pattern and interacts with a specified
 * device to change its state from locked to unlocked.
 */
class UnlockCommand : public HomeCommand
{
public:
    /**
     * @brief Constructs a new UnlockCommand object.
     * 
     * @param receiver A pointer to the device that will be unlocked.
     * @param target A string representing the target of the command (default is an empty string).
     */
    UnlockCommand(Device *receiver, std::string target = "");

    /**
     * @brief Executes the unlock command.
     * 
     * This method invokes the necessary actions to unlock the associated device.
     */
    void execute();
};

#endif
