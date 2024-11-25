#include "HomeCommand.h"

HomeCommand::HomeCommand(Device *receiver, std::string target)
{
    this->receiver = receiver;
    this->target = target;
}

HomeCommand::~HomeCommand()
{
}
