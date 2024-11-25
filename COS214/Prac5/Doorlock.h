/**
 * @class Doorlock
 * @brief This class simulates a door lock and inherits from the Device class.
 * 
 * The Doorlock class provides specific functionality for a door lock device, including actions 
 * to manipulate its state (lock, unlock, etc.), and printing the current state.
 */
#ifndef DOORLOCK_H
#define DOORLOCK_H

#include "Device.h"

/**
 * @brief The Doorlock class represents a simulated door lock device.
 * 
 * This class provides concrete implementations for the performAction and printState methods 
 * from the base Device class, enabling the simulation of a door lock's behavior.
 */
class Doorlock : public Device
{
public:
    /**
     * @brief Constructs a new Doorlock object.
     * 
     * Initializes a Doorlock with default values.
     */
    Doorlock();

    /**
     * @brief Performs an action on the door lock.
     * 
     * This function allows the door lock to perform specific actions based on the input string.
     * Possible actions might include "lock", "unlock", etc.
     * 
     * @param action A string representing the action to be performed on the door lock.
     */
    void performAction(std::string action);

    /**
     * @brief Prints the current state of the door lock.
     * 
     * This function returns a string representation of the current state of the door lock.
     * 
     * @return A string describing the current state of the door lock.
     */
    std::string printState();
};

#endif
