#include "Sensor.h"

void Sensor::addDevice(NotifyCommand *com)
{
    devices.push_back(com);
}

void Sensor::removeDevice(NotifyCommand *com)
{
    auto it = find(devices.begin(), devices.end(),
                   com);

    if (it != devices.end())
    {
        devices.erase(it);
    }
}
