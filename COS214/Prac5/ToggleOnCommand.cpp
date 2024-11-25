#include "ToggleOnCommand.h"

ToggleOnCommand::ToggleOnCommand(Device *receiver, bool isOn, std::string target) : HomeCommand(receiver, target)
{
    this->isOn = isOn;
    onCommand = new OnCommand(receiver);
    offCommand = new OffCommand(receiver);
}

ToggleOnCommand::~ToggleOnCommand()
{
    delete onCommand;
    delete offCommand;
}

void ToggleOnCommand::execute()
{
    if (isOn)
    {
        offCommand->execute();
    }
    else
    {
        onCommand->execute();
    }
    isOn = !isOn;
}
