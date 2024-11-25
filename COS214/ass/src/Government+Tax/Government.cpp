#include "Government.h"
#include "CitizenTaxAB.h"
#include "../resources.h"
#include <iostream>

void Government::processTaxes(CityStructure &city)
{
    auto visitor = std::make_unique<CitizenTaxAB>();
    city.accept(visitor.get());

    double income = city.getIncome();
    double totalTax = 0;

    for (const auto &[category, rate] : taxRates)
    {
        double taxforCategory = income * rate;
        totalTax += taxforCategory;
    }

    if (taxRates.empty())
    {
        totalTax = city.getIncome();
    }

    cityTaxes[city.getName()] += totalTax;
    Resources::addMoney(totalTax);
}

void Government::applyBudget(CityStructure &city)
{
    if (budgetPolicy)
    {
        budgetPolicy->applyBudget(city, cityTaxes[city.getName()]);
    }
    else
    {
        double budget = cityTaxes[city.getName()];
        double budgetHealth = budget * 0.33;
        double budgetEducation = budget * 0.33;
        double budgetInfrastructure = budget * 0.33;

        city.allocateBudget("Health", budgetHealth);
        city.allocateBudget("Education", budgetEducation);
        city.allocateBudget("Infrastructure", budgetInfrastructure);
    }
}

void Government::setBudgetPolicy(std::unique_ptr<BudgetPolicy> policy)
{
    budgetPolicy = std::move(policy);
}

void Government::setTaxRate(std::string category, double rate)
{
    taxRates[category] = rate;
}

void Government::collectTaxes()
{
    for (const auto &cityPtr : cities)
    {
        processTaxes(*cityPtr);
    }
}

void Government::addCity(std::unique_ptr<CityStructure> city)
{
    cities.push_back(std::move(city));
}

void Government::allocateTaxes(std::string department, double amount)
{
    taxRates[department] = amount;
}
