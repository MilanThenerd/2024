/**
 * @class MacroRoutine
 * @brief This class automates the execution of multiple commands as part of a macro routine.
 * 
 * The MacroRoutine class inherits from HomeCommand and allows multiple commands to be grouped together
 * and executed in sequence. This is useful for automating a series of actions on devices.
 */
#ifndef MACROROUTINE_H
#define MACROROUTINE_H

#include <string>
#include <vector>
#include <bits/stdc++.h>

#include "HomeCommand.h"

/**
 * @brief The MacroRoutine class represents a macro that can execute a sequence of commands.
 * 
 * This class allows users to group multiple HomeCommand objects and execute them in order, 
 * automating a series of tasks. It provides functionality for adding and removing commands from the macro.
 */
class MacroRoutine : public HomeCommand
{
private:
    std::string macroName;                   ///< Name of the macro routine
    std::vector<HomeCommand *> commands;     ///< List of commands that make up the macro

public:
    /**
     * @brief Constructs a new MacroRoutine object.
     * 
     * Initializes the MacroRoutine with a receiver device, a macro name, and an optional target.
     * 
     * @param receiver A pointer to the device that will receive the commands.
     * @param name The name of the macro routine.
     * @param target An optional target entity, represented as a string (default is an empty string).
     */
    MacroRoutine(Device *receiver, std::string name, std::string target = "");

    /**
     * @brief Executes all commands in the macro.
     * 
     * This function executes each HomeCommand in the macro's list of commands in the order they were added.
     */
    void execute();

    /**
     * @brief Adds a command to the macro routine.
     * 
     * This function adds a HomeCommand object to the list of commands in the macro.
     * 
     * @param command A pointer to the HomeCommand object to be added.
     */
    void addCommand(HomeCommand *command);

    /**
     * @brief Removes a command from the macro routine.
     * 
     * This function removes a HomeCommand object from the list of commands in the macro.
     * 
     * @param command A pointer to the HomeCommand object to be removed.
     */
    void removeCommand(HomeCommand *command);

    /**
     * @brief Retrieves the name of the macro routine.
     * 
     * This function returns the name of the macro routine.
     * 
     * @return A string representing the name of the macro.
     */
    std::string getName();
};

#endif
