#include "LockCommand.h"

LockCommand::LockCommand(Device *receiver, std::string target) : HomeCommand(receiver, target)
{
}

void LockCommand::execute()
{
    receiver->performAction(target + "* lock");
}
