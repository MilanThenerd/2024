#include "NotifyCommand.h"

NotifyCommand::NotifyCommand(Device *receiver, HomeCommand *command, std::string filter, std::string target) : HomeCommand(receiver, target)
{
    this->filter = filter;
    this->command = command;
}

void NotifyCommand::execute()
{
    throw "NotifyCommand should use filterExecute instead of execute";
}

void NotifyCommand::filterExecute(std::string value)
{
    // filter can be empty or one of the following:
    // lt, gt, eq, ne, le, ge
    // we check if the value is within the filter and if it is, we execute the command

    std::cout << "Filtering value: " << value << " with target: " << target << " using filter: " << filter << std::endl;
    if (filter == "")
    {
        command->execute();
    }
    // else we need to convert the value and filter to double and compare
    // filter is in format "gt 50" for example
    // we do not use target
    else
    {
        double val = std::stod(value);
        double tar = std::stod(filter.substr(3));
        if (filter.substr(0, 2) == "gt" && val > tar)
        {
            command->execute();
        }
        else if (filter.substr(0, 2) == "lt" && val < tar)
        {
            command->execute();
        }
        else if (filter.substr(0, 2) == "eq" && val == tar)
        {
            command->execute();
        }
        else if (filter.substr(0, 2) == "ne" && val != tar)
        {
            command->execute();
        }
        else if (filter.substr(0, 2) == "ge" && val >= tar)
        {
            command->execute();
        }
        else if (filter.substr(0, 2) == "le" && val <= tar)
        {
            command->execute();
        }
    }
}
