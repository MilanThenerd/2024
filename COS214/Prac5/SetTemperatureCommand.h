/**
 * @class SetTemperatureCommand
 * @brief This class represents a command to set the temperature of a device.
 * 
 * The SetTemperatureCommand class inherits from HomeCommand and is used to 
 * change the temperature of a specified device to a desired value.
 */
#ifndef SETTEMPERATURECOMMAND_H
#define SETTEMPERATURECOMMAND_H

#include "HomeCommand.h"

/**
 * @brief The SetTemperatureCommand class is used to set the temperature on a device.
 * 
 * This command takes a receiver device and a temperature value to apply the 
 * specified temperature setting when executed.
 */
class SetTemperatureCommand : public HomeCommand
{
private:
    int temperature; ///< The target temperature to set on the device.

public:
    /**
     * @brief Constructs a new SetTemperatureCommand object.
     * 
     * @param receiver A pointer to the Device object that will receive the command.
     * @param temperature The temperature value to set on the device.
     * @param target An optional target identifier (default is an empty string).
     */
    SetTemperatureCommand(Device *receiver, double temperature, std::string target = "");

    /**
     * @brief Executes the command to set the temperature on the receiver device.
     * 
     * This function applies the specified temperature to the device 
     * associated with this command.
     */
    void execute();
};

#endif
