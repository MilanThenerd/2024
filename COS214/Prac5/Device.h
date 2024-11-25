/**
 * @class Device
 * @brief The Device class serves as the base class for all sensors.
 * 
 * This abstract class provides the common functionality for all devices, including state management, 
 * identification, and action execution. It works with various device states (OnState, OffState, LockedState, OpenState).
 */
#ifndef DEVICE_H
#define DEVICE_H

#include "DeviceState.h"
#include "OnState.h"
#include "OffState.h"
#include "LockedState.h"
#include "OpenState.h"
#include <sstream>
#include <iostream>

/**
 * @brief The Device class manages the state and identification of a sensor.
 * 
 * The class includes methods for performing actions, retrieving the device's status, and handling state changes.
 * It also works with different concrete states like OnState, OffState, LockedState, and OpenState.
 */
class Device
{
protected:
  DeviceState state;        ///< Current state of the device
  std::string type;         ///< Type of the device (e.g., sensor)
  std::string id;           ///< Unique identifier for the device

  /**
   * @brief Generates a unique identifier for the device.
   * 
   * This protected function is used to generate and assign a unique ID to the device.
   */
  void generateId();

public:
  /**
   * @brief Retrieves the unique ID of the device.
   * 
   * @return A string representing the unique ID of the device.
   */
  std::string getId();

  /**
   * @brief Retrieves the current status of the device.
   * 
   * This function returns a string representation of the device's current state.
   * 
   * @return A string describing the device's current status.
   */
  std::string getStatus();

  /**
   * @brief Executes an action on the device.
   * 
   * This pure virtual function must be implemented by derived classes to define specific actions the device can perform.
   * 
   * @param action The action to be performed by the device.
   */
  virtual void performAction(std::string action) = 0;

  /**
   * @brief Retrieves the type of the device.
   * 
   * @return A string representing the type of the device.
   */
  std::string getDeviceType();

  /**
   * @brief Notifies any observers of a change in the device's state.
   * 
   * This function is responsible for notifying listeners of changes in the device's state. 
   * It's currently not a pure virtual function but could be modified to be pure virtual based on requirements.
   */
  virtual void notify(); // TODO: check if we need to make this pure virtual

  /**
   * @brief Sets the current state of the device.
   * 
   * This function is used to change the current state of the device to the given state.
   * 
   * @param s The new state to be set for the device.
   */
  void setState(DeviceState s);

  /**
   * @brief Returns a string representation of the current state of the device.
   * 
   * This pure virtual function must be implemented by derived classes to provide a formatted representation 
   * of the current device state.
   * 
   * @return A string representing the current state of the device.
   */
  virtual std::string printState() = 0;
};

#endif
