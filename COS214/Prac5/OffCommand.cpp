#include "OffCommand.h"

OffCommand::OffCommand(Device *receiver, std::string target) : HomeCommand(receiver, target)
{
}

void OffCommand::execute()
{
    receiver->performAction(target + "* off");
}
