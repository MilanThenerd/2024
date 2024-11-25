/**
 * @class LockedState
 * @brief This class represents the locked state of a device.
 * 
 * The LockedState class inherits from DeviceState and is used to simulate a device being in the locked state.
 * When a device is in this state, its type is set to "Lock" and its description is "Locked."
 */
#ifndef LOCKEDSTATE_H
#define LOCKEDSTATE_H

#include "DeviceState.h"

/**
 * @brief The LockedState class simulates the state of a device being locked.
 * 
 * This class is part of the state pattern and provides the specific state of a device when it is locked.
 * It sets the type and description to represent the locked condition of the device.
 */
class LockedState : public DeviceState
{
public:
    /**
     * @brief Constructs a new LockedState object.
     * 
     * Initializes the LockedState with the type "Lock" and the description "Locked" 
     * to represent that the device is in a locked state.
     */
    LockedState()
    {
        this->type = "Lock";
        this->description = "Locked";
    };
};

#endif
