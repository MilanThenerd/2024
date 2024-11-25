#include "MacroRoutine.h"

MacroRoutine::MacroRoutine(Device *receiver, std::string name, std::string target) : HomeCommand(receiver, target), macroName(name)
{
}

void MacroRoutine::execute()
{
    for (HomeCommand *command : commands)
    {
        command->execute();
    }
}

void MacroRoutine::addCommand(HomeCommand *command)
{
    commands.push_back(command);
}

void MacroRoutine::removeCommand(HomeCommand *command)
{
    auto it = find(commands.begin(), commands.end(),
                   command);

    if (it != commands.end())
    {
        commands.erase(it);
    }
}

std::string MacroRoutine::getName()
{
    return macroName;
}
