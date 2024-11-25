/**
 * @class NotifyCommand
 * @brief This class represents a command that triggers notifications based on specific conditions.
 * 
 * The NotifyCommand class inherits from HomeCommand and is designed to execute a command while 
 * applying a filter to determine whether to notify users or perform an action.
 */
#ifndef NOTIFYCOMMAND_H
#define NOTIFYCOMMAND_H

#include "HomeCommand.h"

/**
 * @brief The NotifyCommand class implements notification behavior for commands.
 * 
 * This class allows the execution of a HomeCommand while applying a filter, enabling specific actions 
 * to be taken based on the filter condition. It provides functionality to execute the command and 
 * execute it with a filter.
 */
class NotifyCommand : public HomeCommand
{
private:
    std::string filter;           ///< The filter condition for notifications
    HomeCommand *command;        ///< The command to be executed

public:
    /**
     * @brief Constructs a new NotifyCommand object.
     * 
     * Initializes the NotifyCommand with a receiver device, a command to execute, an optional filter, 
     * and an optional target.
     * 
     * @param receiver A pointer to the device that will receive the command.
     * @param command A pointer to the HomeCommand to be executed.
     * @param filter An optional filter condition (default is an empty string).
     * @param target An optional target entity, represented as a string (default is an empty string).
     */
    NotifyCommand(Device *receiver, HomeCommand *command, std::string filter = "", std::string target = "");

    /**
     * @brief Executes the command.
     * 
     * This function executes the command associated with this NotifyCommand. 
     * It triggers the command to perform its action, regardless of the filter.
     */
    void execute();

    /**
     * @brief Executes the command based on the filter condition.
     * 
     * This function checks the specified value against the filter and executes the command 
     * only if the condition is met. If the filter is not met, it does not execute the command.
     * 
     * @param value A string representing the value to check against the filter (default is an empty string).
     */
    void filterExecute(std::string value = "");
};

#endif
