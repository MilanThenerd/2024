#ifndef CITIZEN_H
#define CITIZEN_H

#include "CitizenStates/CitizenStatesIncludes.h"
#include "CityBlock.h"
#include "CityMediator.h"
#include "../Policy.h"
#include <string>
#include <vector>

class Bus;
class RoadComponent;
/**
 * @class Citizen
 * @brief Represents a citizen in the city simulation.
 *
 * The Citizen class extends CityBlock and encapsulates the properties and
 * behaviors of a citizen, including their state, location, workplace,
 * and activities.
 */
class Citizen : CityBlock
{

protected:
	CitizenState *state;
	std::string name;
	Building *workplace;
	Building *home;
	Building *currentLocation;
	RoadComponent *currentRoad;
	std::vector<RoadComponent *> route;
	CityMediator *mediator = nullptr;
	Bus *myBus;
	bool ownsCar;
	bool scheduledForDeletion = false;
	int waitTimer = 0;
	enum Activity
	{
		Rest,
		Work,
		TryBusWork,
		InTransitWork,
		AwaitTransitWork,
		TryBusHome,
		InTransitHome,
		AwaitTransitHome,
		Nothing
	};

	Activity activity;
    /**
     * @brief Changes the happiness level of the citizen.
     * @param change The amount to change happiness by (positive or negative).
     */
	void changeHappiness(int change);

public:
    /**
     * @brief Constructs a Citizen and optionally registers them automatically.
     * @param autoRegister Indicates whether the citizen should be auto-registered.
     */
    Citizen(bool autoRegister = true);

    /**
     * @brief Sets the state of the citizen.
     * @param newState A pointer to the new CitizenState to be assigned.
     */
    void setState(CitizenState *newState);

    /**
     * @brief Gets the current state of the citizen.
     * @return A pointer to the current CitizenState.
     */
    CitizenState *getState();

    /**
     * @brief Notifies the citizen of a change in the environment or situation.
     * @param message A string containing information about the change.
     */
    void notifyChange(std::string message);

    /**
     * @brief Accepts a visitor for tax and budget operations.
     * @param visitor A pointer to the TaxAndBudgetVisitor.
     */
    void accept(TaxAndBudgetVisitor *visitor);

    /**
     * @brief Gets the name of the citizen.
     * @return The name of the citizen as a string.
     */
    std::string getName();

    /**
     * @brief Sets the citizen's workplace.
     * @param workplace A pointer to the Building representing the workplace.
     */
    void setWorkplace(Building *workplace);

    /**
     * @brief Gets the citizen's workplace.
     * @return A pointer to the Building representing the workplace.
     */
    Building *getWorkplace();

    /**
     * @brief Handles the event of the citizen being fired from their job.
     */
    void fired();

    /**
     * @brief Sets the citizen's home.
     * @param home A pointer to the Building representing the home.
     */
    void setHome(Building *home);

    /**
     * @brief Gets the citizen's home.
     * @return A pointer to the Building representing the home.
     */
    Building *getHome();

    /**
     * @brief Handles the event of the citizen being evicted.
     */
    void evicted();

    /**
     * @brief Gives a car to the citizen.
     */
    void giveCar();

    /**
     * @brief Performs the citizen's actions for the current iteration.
     */
    virtual void doSomething();

    /**
     * @brief Gets the current building where the citizen is located.
     * @return A pointer to the Building where the citizen currently is.
     */
    Building *getCurrentBuilding();

    /**
     * @brief Gets the happiness level of the citizen.
     * @return The happiness level as an integer.
     */
    int getHappiness();

    /**
     * @brief Gets the tax obligations of the citizen.
     * @return The tax amount as a double.
     */
    double getTax();

    /**
     * @brief Destructor for the Citizen class.
     */
    ~Citizen();
};

#endif // CITIZEN_H