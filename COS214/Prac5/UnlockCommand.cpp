#include "UnlockCommand.h"

UnlockCommand::UnlockCommand(Device *receiver, std::string target) : HomeCommand(receiver, target)
{
    this->target = target;
}

void UnlockCommand::execute()
{
    receiver->performAction(target + "* unlock");
}
