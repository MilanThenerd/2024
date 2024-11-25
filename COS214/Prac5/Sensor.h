/**
 * @class Sensor
 * @brief This class represents a generic sensor in a smart home system.
 * 
 * The Sensor class inherits from Device and provides an interface for 
 * sensors that can trigger notifications and perform actions. It manages a 
 * collection of NotifyCommand objects associated with the sensor.
 */
#ifndef SENSOR_H
#define SENSOR_H

#include "Device.h"
#include "NotifyCommand.h"
#include <vector>
#include <bits/stdc++.h>

/**
 * @brief The Sensor class serves as a base for all sensor types in the system.
 * 
 * This class allows for the addition and removal of notification commands 
 * and provides pure virtual methods for performing actions and triggering 
 * events specific to the type of sensor.
 */
class Sensor : public Device
{
protected:
    std::vector<NotifyCommand *> devices; ///< A vector of pointers to notification commands associated with the sensor.

public:
    /**
     * @brief Performs an action associated with the sensor.
     * 
     * This method is pure virtual and must be implemented by derived classes 
     * to specify the action to be performed when triggered.
     * 
     * @param action The action to be performed by the sensor.
     */
    virtual void performAction(std::string action) = 0;

    /**
     * @brief Triggers the sensor, causing it to perform its designated action.
     * 
     * This method is pure virtual and must be implemented by derived classes 
     * to define the behavior of the sensor when it is triggered.
     */
    virtual void trigger() = 0;

    /**
     * @brief Adds a notification command to the sensor.
     * 
     * This function takes a pointer to a NotifyCommand object and adds it to 
     * the sensor's collection of devices.
     * 
     * @param com A pointer to the NotifyCommand object to be added.
     */
    void addDevice(NotifyCommand *com);

    /**
     * @brief Removes a notification command from the sensor.
     * 
     * This function takes a pointer to a NotifyCommand object and removes it 
     * from the sensor's collection of devices if it exists.
     * 
     * @param com A pointer to the NotifyCommand object to be removed.
     */
    void removeDevice(NotifyCommand *com);
};

#endif
