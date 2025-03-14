#ifndef SERVSECURITY_H
#define SERVSECURITY_H

#include "Services.h"

/**
 * @class ServSecurity
 * @brief Class representing a Security Service in a building.
 * 
 * This class extends the Services class and provides functionality for managing
 * visitors, employees, and operational state specific to security services.
 */
class ServSecurity : public Services
{
public:
    /** 
     * @brief Default constructor for ServSecurity.
     */
    ServSecurity();

    /** 
     * @brief Destructor for ServSecurity.
     */
    ~ServSecurity();

    /** 
     * @brief Displays information about the building.
     * 
     * This method overrides the displayBuildingInfo method from the Services class.
     */
    void displayBuildingInfo() override;

    /** 
     * @brief Gets the current number of visitors.
     * @return The number of visitors currently in the building.
     */
    int getVisitors() override;

    /** 
     * @brief Sets the number of visitors.
     * @param visitors The number of visitors to set.
     */
    void setVisitors(int visitors) override;

    /** 
     * @brief Calls the Utilities service in the building.
     * 
     * This method interacts with the Utilities class to perform necessary actions.
     */
    void callUtilities();

    /** 
     * @brief Gets the operational state of the security service.
     * @return True if operational, false otherwise.
     */
    bool getState();

    /** 
     * @brief Sets the operational state of the security service.
     * @param state The state to set (true for operational, false for not).
     */
    void setState(bool state);

    /** 
     * @brief Gets the type of building.
     * @return The building type as a string.
     */
    std::string getBuildingType();

    /** 
     * @brief Adds an employee to the security service.
     * @param employee Pointer to the Citizen object representing the employee.
     * @return True if the employee was added successfully, false otherwise.
     */
    bool addEmployee(Citizen *employee);

    /** 
     * @brief Removes an employee from the security service.
     * @param employee Pointer to the Citizen object representing the employee.
     */
    void removeEmployee(Citizen *employee);

    /** 
     * @brief Notifies the service that an employee has left.
     * @param employee Pointer to the Citizen object representing the employee.
     */
    void notifyEmployeeLeft(Citizen *employee);

    /** 
     * @brief Checks if there are available job positions.
     * @return True if there is a job available, false otherwise.
     */
    bool hasJob();

private:
    int visitors; ///< Current number of visitors in the building.
    bool operational; ///< Operational state of the security service.
    std::string type = "Service Security"; ///< Type of the service.

    // Resources
    std::vector<Citizen *> employees; ///< List of employees in the security service.
    int cost = 1500; ///< Cost associated with the security service.

    // Resource costs
    int woodCost = 5; ///< Cost of wood.
    int steelCost = 10; ///< Cost of steel.
    int concreteCost = 15; ///< Cost of concrete.

    // Resource usage
    int electricityUsage = 10; ///< Electricity usage per cycle.
    int waterUsage = 15; ///< Water usage per cycle.

    // Service effects
    int happinessIncrease = 5; ///< Happiness increase provided by the service.
    int jobCapacity = 10; ///< Maximum number of employees that can be hired.
    int cityIncome = 50; ///< Income generated by the service.
};

#endif
