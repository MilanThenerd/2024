#ifndef COMOFFICE_H
#define COMOFFICE_H

#include "Commercial.h"

/**
 * @class ComOffice
 * @brief Represents a commercial office building.
 *
 * The ComOffice class is a concrete implementation of the Commercial class,
 * providing specific functionality and resources related to an office.
 */
class ComOffice : public Commercial {
public:
    /**
     * @brief Default constructor for ComOffice.
     */
    ComOffice();

    /**
     * @brief Destructor for ComOffice.
     */
    ~ComOffice();

    /**
     * @brief Displays information about the building.
     */
    void displayBuildingInfo() override;

    /**
     * @brief Gets the job capacity of the office.
     * @return The number of jobs the office can accommodate.
     */
    int getJobCapacity() override;

    /**
     * @brief Sets the job capacity of the office.
     * @param capacity The new job capacity to set.
     */
    void setJobCapacity(int capacity) override;

    // Observer methods

    /**
     * @brief Calls utilities for the office.
     */
    void callUtilities(); // call Utilities in Buildings

    /**
     * @brief Gets the operational state of the office.
     * @return True if the office is operational, false otherwise.
     */
    bool getState();

    /**
     * @brief Sets the operational state of the office.
     * @param state The new state to set.
     */
    void setState(bool state);

    /**
     * @brief Gets the type of the building.
     * @return A string representing the building type.
     */
    string getBuildingType() override;

    /**
     * @brief Adds an employee to the office.
     * @param employee A pointer to the Citizen representing the employee.
     * @return True if the employee was added successfully, false otherwise.
     */
    bool addEmployee(Citizen* employee);

    /**
     * @brief Removes an employee from the office.
     * @param employee A pointer to the Citizen representing the employee.
     */
    void removeEmployee(Citizen* employee);

    /**
     * @brief Notifies that an employee has left the office.
     * @param employee A pointer to the Citizen representing the employee.
     */
    void notifyEmployeeLeft(Citizen* employee);

    /**
     * @brief Checks if the office has a job available.
     * @return True if there is a job available, false otherwise.
     */
    bool hasJob();

private:
    vector<Citizen*> employees; ///< List of employees in the office.

    // Resources
    int cost = 1500;            ///< Cost of the office.
    int jobCapacity = 20;       ///< Maximum job capacity.
    int woodCost = 5;           ///< Cost of wood for construction.
    int concreteCost = 10;      ///< Cost of concrete for construction.
    int steelCost = 5;          ///< Cost of steel for construction.
    int electricityUsage = 10;  ///< Electricity usage per time unit.
    int waterUsage = 10;        ///< Water usage per time unit.
    int income = 200;           ///< Income generated by the office.

    string type = "Commercial Office"; ///< Type of the building.
    bool operational;            ///< Operational state of the office.
};

#endif // COMOFFICE_H
