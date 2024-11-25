#include "SmartHomeSystem.h"
#include <iostream>

SmartHomeSystem::SmartHomeSystem()
{

}
#if TRUE
void SmartHomeSystem::clearTerminal() 
{
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}
void SmartHomeSystem::run()
{
    std::string command;
    std::cout << "Welcome to your own automated SmartHome!" << std::endl;

    while (true)
    {
        clearTerminal();

        std::cout << "What would you like to do? (AddSection, RemoveSection, AddRoom, RemoveRoom, AddDevice, RemoveDevice, ControlDevice, AddMacro, RemoveMacro, RunMacro , ListDevices ,Exit): ";
        std::cin >> command;

        if (command == "AddSection")
        {
            std::string sectionName;
            std::cout << "Enter the section name: ";
            std::cin >> sectionName;
            addSection(sectionName);
        }
        else if (command == "RemoveSection")
        {
            if (sections.empty())
            {
                std::cout << "No sections available to remove." << std::endl;
            }
            else
            {
                std::cout << "Available sections:" << std::endl;
                for (const auto& section : sections)
                {
                    std::cout << "- " << section.first << std::endl;
                }

                std::string sectionName;
                std::cout << "Enter the section name to remove: ";
                std::cin >> sectionName;
                removeSection(sectionName);
            }
        }
        else if(command == "ListDevices")
        {
          if(devices.size() < 1)
            {
              std::cout << "No devices registered." << std::endl;
              std::cout << "Press Enter to continue...";
              std::cin.ignore();
              std::cin.get();
              continue;
            }
            std::cout << "List of devices:" << std::endl;
            for (const auto& device : devices)
            {
                std::cout << "ID: " << device->getId() << ", Type: " << device->getDeviceType() << ", Status: " << device->getStatus() << std::endl;
            }
        }
        else if (command == "AddRoom")
        {
            std::string roomName, sectionName;
            std::cout << "Enter the room name: ";
            std::cin >> roomName;
            std::cout << "Enter the section name: ";
            std::cin >> sectionName;
            addRoom(roomName, sectionName);
        }
        else if (command == "RemoveRoom")
        {
            if (rooms.empty())
            {
                std::cout << "No rooms available to remove." << std::endl;
            }
            else
            {
                std::cout << "Available rooms:" << std::endl;
                for (const auto& room : rooms)
                {
                    std::cout << "- " << room.first << std::endl;
                }

                std::string sectionName;
                std::cout << "Enter the section from which the room must be removed: ";
                std::cin >> sectionName;

                std::string roomName;
                std::cout << "Enter the room name to remove: ";
                std::cin >> roomName;
                removeRoom(roomName, sectionName);
            }
        }
        else if (command == "AddDevice")
        {
            int type;
            std::cout << "What device type do you want to add: (1: Light, 2: Thermostat, 3: Doorlock, 4: MotionSensor, 5: TemperatureSensor , 6: LegacyThermostat): ";
            std::cin >> type;
            std::string roomName;
            std::cout << "Enter the room name to add a device to: ";
            std::cin >> roomName;
            addDevice(type, roomName);
        }
        else if (command == "RemoveDevice")
        {
            if(devices.size() < 1)
            {
              std::cout << "No devices registered." << std::endl;
              std::cout << "Press Enter to continue...";
              std::cin.ignore();
              std::cin.get();
              continue;
            }
            std::cout << "Available devices:" << std::endl;
            for (const auto& device : devices)
            {
                std::cout << "ID: " << device->getId() << ", Type: " << device->getDeviceType() << std::endl;
            }
            std::cout << "Enter ID for the device you want to remove: ";
            std::string deviceID;
            std::cin >> deviceID;
            removeDevice(deviceID);
        }
        else if(command == "RunMacro")
        {
          if(routines.size() < 1)
          {
            std::cout << "No Macro Routines exists." << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            continue;
          }
          std::cout << "Current Macros :" << std::endl;
          for(auto it = routines.begin(); it != routines.end() ; it++)
          {
            std::cout << "- " << it->second.getName() << std::endl;
          }
          std::cout << "Which Macro do you want to Run?: ";
          std::string macroName;
          std::cin >> macroName;
          routines.at(macroName).execute();
          std::cout << "Macro '" << macroName << "' succesfully ran." << std::endl;
        }
        else if(command == "RemoveMacro")
        {
          if(routines.size() < 1)
          {
            std::cout << "No Macro Routines exists." << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            continue;
          }
          std::cout << "Current Macros :" << std::endl;
          for(auto it = routines.begin(); it != routines.end() ; it++)
          {
            std::cout << "- " << it->second.getName() << std::endl;
          }
          std::cout << "Which Macro do you want to remove?: ";
          std::string macroName;
          std::cin >> macroName;
          routines.erase(macroName);
          std::cout << "Macro '" << macroName << "' succesfully removed." << std::endl;
        }
        else if(command == "AddMacro")
        {
          if(devices.size() < 1)
          {
            std::cout << "No devices registered. Can't add Macro" << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            continue;
          }
          std::cout << "Available devices:" << std::endl;
          for (const auto& device : devices)
          {
            std::cout << "ID: " << device->getId() << ", Type: " << device->getDeviceType() << std::endl;
          }
          std::cout << "Enter device ID to add Macro to: ";
          std::string deviceID;
          std::cin >> deviceID;

          auto it = std::find_if(devices.begin(), devices.end(), [&deviceID](Device* device)
          {
              return device->getId() == deviceID;
          });

          if (it == devices.end())
          {
              std::cout << "Device with ID '" << deviceID << "' not found." << std::endl;
              continue;
          }
          Device* device = *it;

          std::cout << "Enter name for the new Routine: ";
          std::string macroName;
          std::cin >> macroName;
          MacroRoutine* macro;
          auto foundMacro = routines.find(macroName);

          if (foundMacro != routines.end()) 
          {
            macro = &foundMacro->second;
          } 
          else 
          {
            macro = new MacroRoutine(device, macroName);
          }

          std::cout << "Enter type for routine (1:ToggleOn, 2:On , 3:Off , 4:Lock, 5:Unlock): ";
          int macroType = -1;
          std::cin >> macroType;

          if(macroType == 1)
          {
            auto toggle = new ToggleOnCommand(device , false);
            macro->addCommand(toggle);
          }
          else if(macroType == 2)
          {
            auto on = new OnCommand(device);
            macro->addCommand(on);
          }
          else if(macroType == 3)
          {
            auto off = new OffCommand(device);
            macro->addCommand(off);
          }
          else if(macroType == 4)
          {
            auto lock = new LockCommand(device);
            macro->addCommand(lock);
          }
          else if(macroType == 5)
          {
            auto unlock = new UnlockCommand(device);
            macro->addCommand(unlock);
          }
          else
          {
            std::cout << "Invalid Macro Code." << std::endl;
            continue;
          }
          if (foundMacro == routines.end()) 
          {
            std::cout << "Macro '" << macroName << "' added successfully!" << std::endl;
            routines.insert(std::make_pair(macroName, *macro));
          } 
          else 
          {
              std::cout << "Macro '" << macroName << "' successfully modified." << std::endl;
          }
        }
        else if (command == "ControlDevice")
        {
            if(devices.size() < 1)
            {
              std::cout << "No devices registered." << std::endl;
              std::cout << "Press Enter to continue...";
              std::cin.ignore();
              std::cin.get();
              continue;
            }
            std::cout << "Available devices:" << std::endl;
            for (const auto& device : devices)
            {
                std::cout << "ID: " << device->getId() << ", Type: " << device->getDeviceType() << std::endl;
            }

            std::string deviceID;
            std::cout << "Enter the device ID: ";
            std::cin >> deviceID;

            auto it = std::find_if(devices.begin(), devices.end(), [&deviceID](Device* device)
            {
                return device->getId() == deviceID;
            });

            if (it == devices.end())
            {
                std::cout << "Device not found!" << std::endl;
                continue;
            }

            Device* device = *it;
            std::string action;
            std::string deviceType = device->getDeviceType();

            if (deviceType == "Light" || deviceType == "Thermostat")
            {
                std::cout << "This device is :" << device->getStatus() << std::endl;
                std::cout << "What action do you want to perform? (On, Off ,Toggle): ";
                std::cin >> action;

                if (action == "On")
                {
                    device->setState(OnState());
                    std::cout << deviceID << " is now On." << std::endl;
                }
                else if (action == "Off")
                {
                    device->setState(OffState());
                    std::cout << deviceID << " is now Off." << std::endl;
                }
                else
                {
                    std::cout << "Invalid action!" << std::endl;
                }
            }
            else if (deviceType == "Doorlock")
            {
                std::cout << "What action do you want to perform? (Lock, Unlock): ";
                std::cin >> action;

                if (action == "Lock")
                {
                    device->setState(LockedState());
                    std::cout << deviceID << " is now Locked." << std::endl;
                }
                else if (action == "Unlock")
                {
                    device->setState(OpenState());
                    std::cout << deviceID << " is now Unlocked." << std::endl;
                }
                else
                {
                    std::cout << "Invalid action!" << std::endl;
                }
            }
            else
            {
                std::cout << "Unsupported device type!" << std::endl;
            }
        }
        else if (command == "Exit")
        {
            std::cout << "Exiting the Smart Home system. Goodbye!" << std::endl;
            break;
        }
        else
        {
            std::cout << "Invalid command! Please try again." << std::endl;
        }

        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }
}
#endif
void SmartHomeSystem::addSection(std::string name)
{
  if(sections.find(name) != sections.end())
  {
    std::cout << "Section '" << name << "' already exists." << std::endl;
  }
  else
  {
    Section newSection(name);
    sections[name] = newSection;
    std::cout << "Section '" << name << "' added successfully." << std::endl; 
  }
}

void SmartHomeSystem::removeSection(std::string name)
{
    if (sections.find(name) == sections.end())
    {
        std::cout << "Section '" << name << "' does not exist." << std::endl;
    }
    else
    {
        sections.erase(name);
        std::cout << "Section '" << name << "' removed successfully." << std::endl;
    }
}

void SmartHomeSystem::addRoom(std::string roomName, std::string sectionName)
{
    if (sections.find(sectionName) == sections.end())
    {
        std::cout << "Section '" << sectionName << "' does not exist." << std::endl;
    }
    else
    {
        if (rooms.find(roomName) != rooms.end())
        {
            std::cout << "Room '" << roomName << "' already exists." << std::endl;
        }
        else
        {
            Room newRoom(roomName);
            rooms[roomName] = newRoom;
            sections[sectionName].addRoom(&rooms[roomName]);
            std::cout << "Room '" << roomName << "' added successfully to Section '" << sectionName << "'." << std::endl;
        }
    }
}

void SmartHomeSystem::removeRoom(std::string roomName , std::string sectionName)
{
    if (rooms.find(roomName) == rooms.end())
    {
        std::cout << "Room '" << roomName << "' does not exist." << std::endl;
    }
    else
    {
        if (sections.find(sectionName) == sections.end())
        {
            std::cout << "Section '" << sectionName << "' does not exist." << std::endl;
        }
        else
        {
            sections[sectionName].removeRoom(&rooms[roomName]);
            rooms.erase(roomName);
            std::cout << "Room '" << roomName << "' removed successfully from Section '" << sectionName << "'." << std::endl;
        }
    }
}

void SmartHomeSystem::removeDevice(std::string deviceID)
{
  auto it = std::find_if(devices.begin(), devices.end(), [&deviceID](Device* device)
  {
      return device->getId() == deviceID;
  });

  if (it == devices.end())
  {
      std::cout << "Device with ID '" << deviceID << "' not found." << std::endl;
      return;
  }
  Device* device = *it;
  for (auto& roomPair : rooms)
  {
      Room& room = roomPair.second;
      room.removeDevice(device);
  }
  devices.erase(it);
  std::cout << "Device with ID '" << deviceID << "' removed succesfully." << std::endl;
}

void SmartHomeSystem::addDevice(int type, std::string roomName)
{
    if (rooms.find(roomName) == rooms.end())
    {
        std::cout << "Room '" << roomName << "' does not exist." << std::endl;
        return;
    }
    std::string deviceType = "";
    Device* newDevice = nullptr;

    switch (type)
    {
        case 1:
            newDevice = new Light();
            deviceType = "Light";
            break;
        case 2:
            newDevice = new SmartThermostat(30);
            deviceType = "SmartThermostat";
            break;
        case 3:
            newDevice = new Doorlock();
            deviceType = "Doorlock";
            break;
        case 4:
            newDevice = new MotionSensor();
            deviceType = "MotionSensor";
            break;
        case 5:
            newDevice = new TemperatureSensor();
            deviceType = "TemperatureSensor";
            break;
        case 6:
        {
            LegacyThermostat thermo = LegacyThermostat(30);
            newDevice = new SmartThermostatIntegrator(&thermo);
            deviceType = "LegacyThermostat";
            break;
        }
        default:
            std::cout << "Invalid device type!" << std::endl;
            return;
    }

    devices.push_back(newDevice);
    rooms[roomName].addDevice(newDevice);
    std::cout << "Device of type " << deviceType << " added to room '" << roomName << "'." << std::endl;
}