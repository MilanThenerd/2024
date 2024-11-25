#include "Dessert.h"

Dessert::Dessert(int maxNumberOfItems) : Course("Dessert", maxNumberOfItems)
{
}

void Dessert::recommendBeverage()
{
  cout << "Coffee" << endl;
}