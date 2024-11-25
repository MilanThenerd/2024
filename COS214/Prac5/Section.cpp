#include "Section.h"

Section::Section(std::string name)
{
    this->sectionName = name;
    this->type = "Section";
    generateId();
}

void Section::addRoom(Room *room)
{
    rooms.push_back(room);
}

void Section::removeRoom(Room *room)
{
    auto it = find(rooms.begin(), rooms.end(),
                   room);

    if (it != rooms.end())
    {
        rooms.erase(it);
    }
}

void Section::performAction(std::string action)
{
    for (auto room : rooms)
    {
        room->performAction(action);
    }
}

std::string Section::printState()
{
    // std::cout << "Section " << (sectionName == "" ? id : sectionName) << ":" << std::endl;
    // for (auto room : rooms)
    // {
    //     room->printState();
    // }
    std::string message;
    message += "Section " + (sectionName == "" ? id : sectionName) + ":\n";
    for (auto room : rooms)
    {
        message += room->printState() + "\n";
    }
    std::cout << message;
    return message;
}