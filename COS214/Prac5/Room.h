/**
 * @class Room
 * @brief This class represents a room in a smart home system.
 * 
 * The Room class inherits from Device and is used to manage multiple devices 
 * within a specific room. It provides functionality to add, remove, and 
 * perform actions on the devices contained within the room.
 */
#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <bits/stdc++.h>
#include "Device.h"

/**
 * @brief The Room class manages a collection of devices in a smart home environment.
 * 
 * This class allows users to interact with multiple devices in a specific room,
 * facilitating actions such as adding or removing devices and controlling their states.
 */
class Room : public Device
{
private:
    std::vector<Device *> devices; ///< A vector of pointers to devices in the room.
    std::string roomName; ///< The name of the room.

public:
    /**
     * @brief Constructs a new Room object with an optional name.
     * 
     * @param name The name of the room (default is an empty string).
     */
    Room(std::string name = "");

    /**
     * @brief Adds a device to the room.
     * 
     * This function takes a pointer to a Device object and adds it to the room's 
     * collection of devices.
     * 
     * @param device A pointer to the Device object to be added.
     */
    void addDevice(Device *device);

    /**
     * @brief Removes a device from the room.
     * 
     * This function takes a pointer to a Device object and removes it from the room's 
     * collection of devices if it exists.
     * 
     * @param device A pointer to the Device object to be removed.
     */
    void removeDevice(Device *device);

    /**
     * @brief Performs an action on all devices in the room.
     * 
     * This function sends the specified action to each device in the room.
     * 
     * @param action The action to be performed on the devices.
     */
    void performAction(std::string action);

    /**
     * @brief Prints the state of all devices in the room.
     * 
     * This function generates a string representation of the current state of 
     * all devices in the room.
     * 
     * @return A string representing the state of the devices.
     */
    std::string printState();
};

#endif
