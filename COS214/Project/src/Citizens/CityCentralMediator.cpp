#include "CityCentralMediator.h"
#include "../../colours.h"
#include <iostream>
#include "../Transport/TransportInclude.h"
#include <set>
#include <queue>
#include <unordered_map>
#include <limits>
#include <cmath>
#include "Bus.h"
#include "../Buildings/Residential.h"
#include "../Buildings/ServEducation.h"
#include "../Buildings/ServEntertainment.h"
#include "../Buildings/ServHospital.h"
#include "../Buildings/ServSecurity.h"
#include "../Government+Tax/TaxAndBudgetVisitor.h"
#include <memory>

static CityCentralMediator *instance = nullptr;

void CityCentralMediator::checkCitizenServiceSatisfaction()
{
	int education = 0;
	int entertainment = 0;
	int health = 0;
	int security = 0;

	for (auto b : buildings)
	{
		ServEducation *edu = dynamic_cast<ServEducation *>(b);
		if (edu != nullptr)
		{
			education += edu->getCitizenServed();
		}

		ServEntertainment *ent = dynamic_cast<ServEntertainment *>(b);
		if (ent != nullptr)
		{
			entertainment += ent->getCitizenServed();
		}

		ServHospital *hos = dynamic_cast<ServHospital *>(b);
		if (hos != nullptr)
		{
			health += hos->getCitizenServed();
		}

		ServSecurity *sec = dynamic_cast<ServSecurity *>(b);

		if (sec != nullptr)
		{
			security += sec->getCitizenServed();
		}
	}

	int citizenCount = Resources::getPopulation();

	if (education < citizenCount)
	{
		std::cout << RED << "Not enough education services for all citizens" << RESET << std::endl;
		notifyServicesChange(nullptr, "No_Education");
	}
	else
	{
		std::cout << GREEN << "Enough education services for all citizens" << RESET << std::endl;
	}

	if (entertainment < citizenCount)
	{
		std::cout << RED << "Not enough entertainment services for all citizens" << RESET << std::endl;
		notifyServicesChange(nullptr, "No_Entertainment");
	}
	else
	{
		std::cout << GREEN << "Enough entertainment services for all citizens" << RESET << std::endl;
	}

	if (health < citizenCount)
	{
		std::cout << RED << "Not enough health services for all citizens" << RESET << std::endl;
		notifyServicesChange(nullptr, "No_Health");
	}
	else
	{
		std::cout << GREEN << "Enough health services for all citizens" << RESET << std::endl;
	}

	if (security < citizenCount)
	{
		std::cout << RED << "Not enough security services for all citizens" << RESET << std::endl;
		notifyServicesChange(nullptr, "No_Security");
	}
	else
	{
		std::cout << GREEN << "Enough security services for all citizens" << RESET << std::endl;
	}
}

RoadComponent *CityCentralMediator::getClosestRoad(int x, int y)
{
	RoadIterator *seq = new RoadIteratorCon(&roads);
	seq->first();
	RoadComponent *closest = seq->currentRoad();
	float distance = INT32_MAX;

	while (!seq->isDone())
	{
		float dist = seq->currentRoad()->calculateDistance(x, y);
		if (dist < distance)
		{
			distance = dist;
			closest = seq->currentRoad();
		}
		seq->next();
	}

	delete seq;

	// Try cast to RoadsComposite
	RoadsComposite *composite = dynamic_cast<RoadsComposite *>(closest);
	if (composite != nullptr)
	{
		std::vector<RoadComponent *> components = composite->getComponents();
		for (auto c : components)
		{
			float dist = c->calculateDistance(x, y);
			if (dist <= distance)
			{
				distance = dist;
				closest = c;
			}
		}
	}

	return closest;
}

int CityCentralMediator::getBusCount()
{
	return busQueue.size();
}

void CityCentralMediator::removeBus()
{
	if (busQueue.size() > 0)
	{
		busQueue.erase(busQueue.begin());
		std::cout << GREEN << "Removed inactive bus!" << RESET << std::endl;
	}
	else
	{
		std::cout << GREEN << "No inactive buses to remove" << RESET << std::endl;
	}
}

CityCentralMediator *CityCentralMediator::getInstance()
{
	if (instance == nullptr)
	{
		instance = new CityCentralMediator("all good!");
	}
	return instance;
}

void CityCentralMediator::registerBuilding(Building *building)
{
	buildings.push_back(building);
}

void CityCentralMediator::registerUtility(UtilityManager *util)
{
	utilities.push_back(util);
}

void CityCentralMediator::registerCitizen(Citizen *citizen)
{
	for (auto c : citizens)
	{
		if (c->getName() == citizen->getName())
		{
			std::cout << "Citizen " << citizen->getName() << " already registered" << std::endl;
			return;
		}
	}
	citizens.push_back(citizen);
	std::cout << "Citizen " << citizen->getName() << " registered" << std::endl;
}

void CityCentralMediator::registerBus(Bus *bus)
{
	buses.push_back(bus);
	std::cout << "Bus registered" << std::endl;
}

void CityCentralMediator::registerRoad(RoadComponent *road)
{
	roads.push_back(road);
}

void CityCentralMediator::registerTrainStation(Trainstation *trainStation)
{
	trainStations.push_back(trainStation);
	std::cout << "Trainstation registered" << std::endl;
}

void CityCentralMediator::notifyBuildingChange(Building *building, std::string message = "")
{
	for (auto c : citizens)
	{
		c->notifyChange(message);
	}
}

void CityCentralMediator::notifyUtilityChange(UtilityManager *type, bool status, std::string message = "")
{
	for (auto c : citizens)
	{
		c->notifyChange(message);
	}
}

void CityCentralMediator::notifyServicesChange(Services *type, std::string message)
{
	for (auto c : citizens)
	{
		c->notifyChange(message);
	}
}

void CityCentralMediator::notifyRoadChange(RoadState *status, std::string message = "")
{
	for (auto c : citizens)
	{
		c->notifyChange(message);
	}
}

void CityCentralMediator::notifyPolicyChange(std::string message)
{
	for (auto c : citizens)
	{
		c->notifyChange(message);
	}
}

void CityCentralMediator::notifyBusReady(Bus *bus)
{
	// push bus to busQueue if not in queue already
	if (std::find(busQueue.begin(), busQueue.end(), bus) == busQueue.end())
	{
		busQueue.push_back(bus);
		std::cout << "Bus added to queue" << std::endl;
	}
}

Bus *CityCentralMediator::requestBus(Citizen *citizen, RoadComponent *location)
{
	if (busQueue.empty())
	{
		std::cout << "No buses available" << std::endl;
		return nullptr;
	}
	else
	{
		Bus *bus = busQueue.front();
		busQueue.erase(busQueue.begin());
		bus->addPassenger(nullptr, location);
		return bus;
	}
}

CityCentralMediator::CityCentralMediator(std::string param)
{
	if (param == "error")
	{
		std::cout << RED << "Error: CityCentralMediator is a singleton. Use CityCentralMediator::getInstance() instead." << RESET << std::endl;
	}
}

std::vector<RoadComponent *> CityCentralMediator::calculateRoute(int startX, int startY, int endX, int endY)
{
	if (!isReachableByRoad(startX, startY) || !isReachableByRoad(endX, endY))
	{
		std::cout << RED << "Error: Start or end point is not reachable by road." << RESET << std::endl;
		return std::vector<RoadComponent *>();
	}
	std::set<RoadComponent *> visited;
	std::vector<RoadComponent *> path;
	RoadComponent *current = getClosestRoad(startX, startY);
	RoadComponent *end = getClosestRoad(endX, endY);

	while (current != end)
	{
		path.push_back(current);
		visited.insert(current);
		std::vector<RoadComponent *> connections = current->getConnections();
		float distance = 999999;
		RoadComponent *next = nullptr;

		for (auto c : connections)
		{
			if (visited.find(c) == visited.end())
			{
				float dist = c->calculateDistance(endX, endY);
				if (dist < distance)
				{
					distance = dist;
					next = c;
				}
			}
		}

		if (next == nullptr)
		{
			std::cout << RED << "Error: No path found." << RESET << std::endl;
			return path;
		}

		current = next;
	}
	path.push_back(current);
	return path;
}

std::vector<RoadComponent *> CityCentralMediator::calculateRoute(RoadComponent *start, RoadComponent *end)
{
	// Priority queue to store the nodes to be explored, prioritized by their current shortest distance
	std::priority_queue<std::pair<float, RoadComponent *>, std::vector<std::pair<float, RoadComponent *>>, std::greater<std::pair<float, RoadComponent *>>> pq;

	// Map to store the shortest distance to each node
	std::unordered_map<RoadComponent *, float> distances;

	// Map to store the previous node in the shortest path
	std::unordered_map<RoadComponent *, RoadComponent *> previous;

	// Initialize distances to infinity, except the start node
	for (auto road : roads)
	{
		RoadsComposite *composite = dynamic_cast<RoadsComposite *>(road);
		if (composite != nullptr)
		{
			for (auto c : composite->getComponents())
			{
				distances[c] = std::numeric_limits<float>::infinity();
			}
		}
		else
		{
			distances[road] = std::numeric_limits<float>::infinity();
		}
	}
	distances[start] = 0.0f;

	// Add the start node to the priority queue
	pq.push({0.0f, start});

	while (!pq.empty())
	{
		// Extract the node with the smallest distance
		RoadComponent *current = pq.top().second;
		pq.pop();

		// If this node is the destination, reconstruct the path and return it
		if (current == end)
		{
			std::vector<RoadComponent *> path;
			while (current != nullptr)
			{
				path.push_back(current);
				current = previous[current];
			}
			std::reverse(path.begin(), path.end());
			return path;
		}

		// For each neighbor of the current node
		for (auto neighbor : current->getConnections())
		{
			// Assume a uniform distance of 1 between connected nodes
			float newDist = distances[current] + 1;

			// If this distance is shorter than the previously known distance
			if (newDist < distances[neighbor])
			{
				// Update the distance and add the neighbor to the priority queue
				distances[neighbor] = newDist;
				previous[neighbor] = current;
				pq.push({newDist, neighbor});
			}
		}
	}

	// If the destination is not reachable, return an empty path
	std::cout << RED << "Error: No path found." << RESET << std::endl;
	return std::vector<RoadComponent *>();
}

bool CityCentralMediator::isReachableByRoad(int x, int y)
{
	RoadComponent *road = getClosestRoad(x, y);
	if (road->calculateDistance(x, y) < BUILDING_ROAD_DISTANCE)
	{
		return true;
	}
	return false;
}

Trainstation *CityCentralMediator::trainstationInRange(int x, int y)
{
	Trainstation *closest = nullptr;
	if (trainStations.empty())
	{
		return closest;
	}
	for (auto t : trainStations)
	{
		if (t->pointInRange(x, y))
		{
			closest = t;
			break;
		}
	}

	return closest;
}

Building *CityCentralMediator::requestJob()
{
	for (auto b : buildings)
	{
		if (b->hasJob())
		{
			return b;
		}
	}
	return nullptr;
}

void CityCentralMediator::updateBuses()
{
	if (buses.size() < 1)
	{
		return;
	}
	for (auto b : buses)
	{
		b->doSomething();
	}
}

void CityCentralMediator::citizensDoSomething()
{
	if (citizens.size() < 1)
	{
		return;
	}
	for (auto c : citizens)
	{
		if (c != NULL && c != nullptr)
		{
			c->doSomething();
		}
	}
}

void CityCentralMediator::citizensStartWork()
{
	for (auto c : citizens)
	{
		c->notifyChange("Go_Work");
	}
}

void CityCentralMediator::updateJobs()
{
	for (auto c : citizens)
	{
		c->notifyChange("Update_Job");
	}
}

void CityCentralMediator::citizensEndWork()
{
	for (auto c : citizens)
	{
		c->notifyChange("Go_Home");
	}
}

CityCentralMediator::~CityCentralMediator()
{
	std::cout << RED << "DELETE ROADS" << RESET << std::endl;
	// Clean up roads
	for (auto road : roads)
	{
		delete road;
	}
	roads.clear();

	std::cout << RED << "DELETE TRAINSTATIONS" << RESET << std::endl;
	// Clean up buildings
	for (auto building : buildings)
	{
		delete building;
	}
	buildings.clear();

	std::cout << RED << "DELETE TRAINSTATIONS" << RESET << std::endl;
	// Clean up utilities
	for (auto utility : utilities)
	{
		delete utility;
	}
	utilities.clear();

	std::cout << RED << "DELETE CITIZENS" << RESET << std::endl;
	// Clean up citizens
	for (auto citizen : citizens)
	{
		delete citizen;
	}
	citizens.clear();

	std::cout << RED << "DELETE BUSES" << RESET << std::endl;
	// Clean up buses and bus queue
	for (auto bus : buses)
	{
		delete bus;
	}
	buses.clear();

	busQueue.clear(); // Since busQueue does not own the buses, just clear the list

	// Clean up road state if dynamically allocated
    // delete roadState;

	// Reset the singleton instance pointer to ensure only one instance can be created again
	instance = nullptr;
}

void CityCentralMediator::handlePopulationGrowth()
{
	int happiness = Resources::getHappiness();

	std::cout << "Happiness: " << happiness << std::endl;

	happiness = clamp(happiness, 0, 100);

	int maxPop = Resources::getMaxPopulation();
	int curPop = Resources::getPopulation();

	float happinessRatio = 1.0 + happiness / 100.0;

	std::cout << "Happiness ratio: " << happinessRatio << std::endl;

	std::cout << "Max population: " << maxPop << std::endl;

	int popDelta = maxPop - curPop;

	int newPop = ceil(popDelta * 0.1 * happinessRatio);

	std::cout << "New population: " << newPop << std::endl;

	for (int i = 0; i < newPop; i++)
	{
		std::cout << BLUE << "Creating a new citizen!" << RESET << std::endl;
		Citizen *c = new Citizen(true);

		for (auto b : buildings)
		{
			Residential *house = dynamic_cast<Residential *>(b);
			if (house != nullptr)
			{
				if (house->moveIn(c))
				{
					std::cout << "Citizen " << c->getName() << " moved in!" << std::endl;
					c->setHome(house);
					break;
				}
			}
		}
	}

	std::cout << "Total population: " << Resources::getPopulation() << std::endl;
}

void CityCentralMediator::handleUtilityFailure()
{
	// TODO - implement CityCentralMediator::handleUtilityFailure
	throw "Not yet implemented";
}

void CityCentralMediator::updateCitizenSatisfaction()
{
	checkCitizenServiceSatisfaction();
}

void CityCentralMediator::handleCitizenEmigration(Citizen *citizen)
{
	if (citizen != nullptr)
	{
		std::cout << "Citizen " << citizen->getName() << " is leaving due to being upset!" << std::endl;
		// remove from citizens array
		auto it = std::find(citizens.begin(), citizens.end(), citizen);
		if (it != citizens.end())
		{
			std::cout << YELLOW << "Citizen " << citizen->getName() << " removed from city" << RESET << std::endl;
			citizens.erase(it);
		}
		delete citizen;
	}
}

double CityCentralMediator::accept(TaxAndBudgetVisitor *visitor)
{
	if (visitor == nullptr)
	{
		return 0;
	}
	double total = 0;
	for (Building *building : buildings)
	{
		total += visitor->visit(building);
	}
	for (Citizen *citizen : citizens)
	{
		total += visitor->visit(citizen);
	}
	return total;
}
