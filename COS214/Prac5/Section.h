/**
 * @class Section
 * @brief This class represents a section in a smart home system.
 * 
 * The Section class inherits from Device and is used to manage multiple rooms 
 * within a specific section of a building. It provides functionality to add, 
 * remove, and perform actions on the rooms contained within the section.
 */
#ifndef SECTION_H
#define SECTION_H

#include <vector>
#include <string>
#include "Room.h"
#include "Device.h"

/**
 * @brief The Section class manages a collection of rooms in a smart home environment.
 * 
 * This class allows users to interact with multiple rooms in a specific section,
 * facilitating actions such as adding or removing rooms and controlling their states.
 */
class Section : public Device
{
private:
    std::vector<Room *> rooms; ///< A vector of pointers to rooms in the section.
    std::string sectionName; ///< The name of the section.

public:
    /**
     * @brief Constructs a new Section object with an optional name.
     * 
     * @param name The name of the section (default is an empty string).
     */
    Section(std::string name = "");

    /**
     * @brief Adds a room to the section.
     * 
     * This function takes a pointer to a Room object and adds it to the section's 
     * collection of rooms.
     * 
     * @param room A pointer to the Room object to be added.
     */
    void addRoom(Room *room);

    /**
     * @brief Removes a room from the section.
     * 
     * This function takes a pointer to a Room object and removes it from the section's 
     * collection of rooms if it exists.
     * 
     * @param room A pointer to the Room object to be removed.
     */
    void removeRoom(Room *room);

    /**
     * @brief Performs an action on all rooms in the section.
     * 
     * This function sends the specified action to each room in the section.
     * 
     * @param action The action to be performed on the rooms.
     */
    void performAction(std::string action);

    /**
     * @brief Prints the state of all rooms in the section.
     * 
     * This function generates a string representation of the current state of 
     * all rooms in the section.
     * 
     * @return A string representing the state of the rooms.
     */
    std::string printState();
};

#endif
