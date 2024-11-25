#include "OnCommand.h"

OnCommand::OnCommand(Device *receiver, std::string target) : HomeCommand(receiver, target)
{
}

void OnCommand::execute()
{
    receiver->performAction(target + "* on");
}