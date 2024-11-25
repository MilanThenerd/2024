/**
 * @class SmartHomeSystem
 * @brief This class represents the smart home system, managing devices, rooms, and sections.
 * 
 * The SmartHomeSystem class serves as the main controller for a smart home, allowing 
 * users to manage devices, rooms, sections, and routines. It provides functionality 
 * to add and remove these entities and to run the system.
 */
#ifndef SMARTHOMESYSTEM_H
#define SMARTHOMESYSTEM_H

#include "includes.h"
#include <map>
#include <vector>

/**
 * @brief The SmartHomeSystem class manages the overall functionality of a smart home.
 * 
 * This class holds vectors and maps of devices, rooms, sections, and routines,
 * enabling the organization and control of a smart home environment.
 */
class SmartHomeSystem
{
private:
    std::vector<Device*> devices; ///< A vector of pointers to devices in the smart home.
    std::map<std::string, Room> rooms; ///< A map of rooms indexed by their names.
    std::map<std::string, Section> sections; ///< A map of sections indexed by their names.
    std::map<std::string, MacroRoutine> routines; ///< A map of macro routines indexed by their names.
    
    /**
     * @brief Clears the terminal screen.
     * 
     * This private function is used to clear the terminal output, improving user interface.
     */
    void clearTerminal();

public:
    /**
     * @brief Constructs a new SmartHomeSystem object.
     * 
     * Initializes the smart home system, setting up any necessary configurations.
     */
    SmartHomeSystem();

    /**
     * @brief Runs the smart home system.
     * 
     * This function starts the main loop of the smart home system, allowing 
     * users to interact with it and manage devices, rooms, and sections.
     */
    void run();

    /**
     * @brief Adds a new section to the smart home system.
     * 
     * This function creates a new section with the specified name and adds it 
     * to the smart home system.
     * 
     * @param name The name of the section to be added.
     */
    void addSection(std::string name);

    /**
     * @brief Removes a section from the smart home system.
     * 
     * This function removes the specified section from the system, along with 
     * any associated rooms and devices.
     * 
     * @param name The name of the section to be removed.
     */
    void removeSection(std::string name);

    /**
     * @brief Adds a new room to a specified section.
     * 
     * This function creates a new room within the specified section.
     * 
     * @param roomName The name of the room to be added.
     * @param sectionName The name of the section to which the room will be added.
     */
    void addRoom(std::string roomName, std::string sectionName);

    /**
     * @brief Removes a room from a specified section.
     * 
     * This function removes the specified room from the specified section.
     * 
     * @param roomName The name of the room to be removed.
     * @param sectionName The name of the section from which the room will be removed.
     */
    void removeRoom(std::string roomName, std::string sectionName);

    /**
     * @brief Adds a new device to a specified room.
     * 
     * This function creates a new device of the specified type and adds it 
     * to the specified room.
     * 
     * @param type The type of the device to be added (represented as an integer).
     * @param roomName The name of the room to which the device will be added.
     */
    void addDevice(int type, std::string roomName);

    /**
     * @brief Removes a device from the smart home system.
     * 
     * This function removes the specified device from the system using its ID.
     * 
     * @param deviceID The ID of the device to be removed.
     */
    void removeDevice(std::string deviceID);
};

#endif
