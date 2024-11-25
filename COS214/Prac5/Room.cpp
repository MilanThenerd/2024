#include "Room.h"

Room::Room(std::string name)
{
    this->roomName = name;
    this->type = "Room";
    generateId();
}

void Room::addDevice(Device *device)
{
    devices.push_back(device);
}

void Room::removeDevice(Device *device)
{
    auto it = find(devices.begin(), devices.end(),
                   device);

    if (it != devices.end())
    {
        devices.erase(it);
    }
}

void Room::performAction(std::string action)
{
    for (auto device : devices)
    {
        device->performAction(action);
    }
}

std::string Room::printState()
{
    // std::cout << "Room " << (roomName == "" ? id : roomName) << ":" << std::endl;
    // for (auto device : devices)
    // {
    //     device->printState();
    // }
    std::string message;
    message += "Room " + (roomName == "" ? id : roomName) + ":\n";
    for (auto device : devices)
    {
        message += device->printState() + "\n";
    }
    std::cout << message;
    return message;
}