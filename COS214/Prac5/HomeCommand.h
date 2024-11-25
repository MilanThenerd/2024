/**
 * @class HomeCommand
 * @brief The HomeCommand class is the base class for all command objects and acts as an interface.
 * 
 * This class provides the foundation for command design pattern implementations. 
 * It holds a reference to a receiver (a Device) and a target, which represents the entity 
 * upon which the command will act. Derived classes will implement specific commands.
 */
#ifndef HOMECOMMAND_H
#define HOMECOMMAND_H

#include "Device.h"

/**
 * @brief The HomeCommand class serves as the base class for all command objects in the system.
 * 
 * This abstract class defines the interface for executing commands on devices. 
 * It uses the Command design pattern, where commands are encapsulated and executed on a receiver (a device).
 */
class HomeCommand
{
protected:
  Device *receiver;       ///< A pointer to the device that will execute the command
  std::string target;     ///< The target on which the command will act

public:
  /**
   * @brief Constructs a HomeCommand object.
   * 
   * Initializes the command with a receiver device and a target.
   * 
   * @param receiver A pointer to the Device that will execute the command.
   * @param target The target entity for the command, represented as a string.
   */
  HomeCommand(Device *receiver, std::string target);

  /**
   * @brief Executes the command.
   * 
   * This pure virtual function must be implemented by derived classes to define 
   * the specific behavior of the command.
   */
  virtual void execute() = 0;

  /**
   * @brief Destroys the HomeCommand object.
   * 
   * The destructor cleans up resources used by the command.
   */
  virtual ~HomeCommand();
};

#endif
