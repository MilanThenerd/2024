/**
 * @file Government.h
 * @brief Header file for the Government class, which manages tax collection and budget allocation for cities.
 * @details This file defines the Government class, responsible for collecting taxes from various city structures,
 * managing budget policies, and allocating funds to different departments within each city.
 * The class allows setting specific tax rates for categories and applying budget policies for optimal resource distribution.
 * @author WORKONMYMACHINE TEAM
 */
#ifndef GOVERNMENT_H
#define GOVERNMENT_H

#include "CityStructure.h"
#include "BudgetPolicy.h"
#include <string>
#include <map>
#include <vector>
#include <memory>

class CitezenTaxAB;
class Policy;
/**
 * @class Government
 * @brief Represents a government entity responsible for managing taxes and budgets for cities.
 */
class Government
{
public:
    void processTaxes(CityStructure &city);
    void applyBudget(CityStructure &city);
    void setTaxRate(std::string category, double rate);
    void collectTaxes();
    void allocateTaxes(std::string department, double amount);

    /**
     * @brief Adds a city to the government’s management. 
     * Takes ownership using unique_ptr.
     */
    void addCity(std::unique_ptr<CityStructure> city);

    /**
     * @brief Sets the current budget policy.
     * Takes ownership using unique_ptr.
     */
    void setBudgetPolicy(std::unique_ptr<BudgetPolicy> policy);

    ~Government() = default; // unique_ptr handles cleanup
private:
    std::map<std::string, double> taxRates;
    std::map<std::string, double> cityTaxes;
    std::vector<std::unique_ptr<CityStructure>> cities;
    std::unique_ptr<BudgetPolicy> budgetPolicy = nullptr;
};
#endif
