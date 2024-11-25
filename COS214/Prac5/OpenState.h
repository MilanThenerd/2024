/**
 * @class OpenState
 * @brief This class represents the open (unlocked) state of a device.
 * 
 * The OpenState class inherits from DeviceState and is used to indicate that a device, 
 * such as a door or lock, is currently in an unlocked state. It defines the type and 
 * description associated with this state.
 */
#ifndef OPENSTATE_H
#define OPENSTATE_H

#include "DeviceState.h"

/**
 * @brief The OpenState class simulates the state of a device being open or unlocked.
 * 
 * This class is part of the state pattern and provides the specific state of a device 
 * when it is accessible. The type is set to "Lock" and the description is set to "Unlocked."
 */
class OpenState : public DeviceState
{
public:
    /**
     * @brief Constructs a new OpenState object.
     * 
     * Initializes the OpenState with the type "Lock" and the description "Unlocked" 
     * to represent that the device is in an open state.
     */
    OpenState()
    {
        this->type = "Lock";
        this->description = "Unlocked";
    };
};

#endif
