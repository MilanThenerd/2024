#include "MainCourse.h"

MainCourse::MainCourse(int maxNumberOfItems) : Course("Main", maxNumberOfItems)
{
}

void MainCourse::recommendBeverage()
{
  cout << "Coke" << endl;
}