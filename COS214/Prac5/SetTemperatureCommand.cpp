#include "SetTemperatureCommand.h"

SetTemperatureCommand::SetTemperatureCommand(Device *receiver, double temperature, std::string target) : HomeCommand(receiver, target)
{
    this->target = target;
    this->temperature = temperature;
}

void SetTemperatureCommand::execute()
{
    receiver->performAction(target + "* setTemperature " + std::to_string(temperature));
}
