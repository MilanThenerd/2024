/**
 * @class DeviceState
 * @brief This class serves as the base for all states used by a Device.
 * 
 * This abstract class holds the type and description of a device state.
 * Derived classes will define specific behaviors for different states.
 */
#ifndef DEVICESTATE_H
#define DEVICESTATE_H

#include <string>

/**
 * @brief The DeviceState class holds information about the device state.
 * 
 * The class contains methods to retrieve the type and description of the state.
 */
class DeviceState
{
protected:
  std::string type;         ///< Type of the device state
  std::string description;  ///< Description of the device state

public:
  /**
   * @brief Retrieves the description of the device state.
   * 
   * This function returns a string that describes the current state of the device.
   * 
   * @return A string containing the description of the state.
   */
  std::string getDescription();

  /**
   * @brief Retrieves the type of the device state.
   * 
   * This function returns a string that represents the type of the current device state.
   * 
   * @return A string containing the type of the state.
   */
  std::string getType();
};

#endif