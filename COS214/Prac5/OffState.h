/**
 * @class OffState
 * @brief This class represents the off state of a device.
 * 
 * The OffState class inherits from DeviceState and is used to represent a device 
 * that is currently turned off. It defines the type and description associated with 
 * this state.
 */
#ifndef OFFSTATE_H
#define OFFSTATE_H

#include "DeviceState.h"

/**
 * @brief The OffState class simulates the state of a device being turned off.
 * 
 * This class is part of the state pattern and provides the specific state of a device 
 * when it is not powered on. The type is set to "Power" and the description is set to "Off."
 */
class OffState : public DeviceState
{
public:
    /**
     * @brief Constructs a new OffState object.
     * 
     * Initializes the OffState with the type "Power" and the description "Off" 
     * to represent that the device is in an off state.
     */
    OffState()
    {
        this->type = "Power";
        this->description = "Off";
    };
};

#endif
