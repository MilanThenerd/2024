/**
 * @class OnState
 * @brief This class represents the on state of a device.
 * 
 * The OnState class inherits from DeviceState and is used to indicate that a device 
 * is currently powered on. It defines the type and description associated with 
 * this state.
 */
#ifndef ONSTATE_H
#define ONSTATE_H

#include "DeviceState.h"

/**
 * @brief The OnState class simulates the state of a device being turned on.
 * 
 * This class is part of the state pattern and provides the specific state of a device 
 * when it is active. The type is set to "Power" and the description is set to "On."
 */
class OnState : public DeviceState
{
public:
    /**
     * @brief Constructs a new OnState object.
     * 
     * Initializes the OnState with the type "Power" and the description "On" 
     * to represent that the device is in an on state.
     */
    OnState()
    {
        this->type = "Power";
        this->description = "On";
    };
};

#endif
