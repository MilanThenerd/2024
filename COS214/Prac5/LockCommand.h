/**
 * @class LockCommand
 * @brief This class represents the LockCommand, used to simulate locking devices such as the Doorlock.
 * 
 * The LockCommand class inherits from the HomeCommand class and provides the functionality 
 * to lock a device by sending the appropriate command to the receiver (e.g., a Doorlock).
 */
#ifndef LOCKCOMMAND_H
#define LOCKCOMMAND_H

#include "HomeCommand.h"

/**
 * @brief The LockCommand class implements the command to lock a device.
 * 
 * This class is part of the command pattern implementation, sending a locking command 
 * to the device (receiver) to change its state to locked.
 */
class LockCommand : public HomeCommand
{
public:
    /**
     * @brief Constructs a new LockCommand object.
     * 
     * Initializes the LockCommand with a receiver device and an optional target.
     * 
     * @param receiver A pointer to the device (e.g., Doorlock) that will receive the lock command.
     * @param target The target entity, represented as a string (optional, default is an empty string).
     */
    LockCommand(Device *receiver, std::string target = "");

    /**
     * @brief Executes the lock command on the device.
     * 
     * This function sends the lock command to the receiver device, instructing it to change its state to locked.
     */
    void execute();
};

#endif
