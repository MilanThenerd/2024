#ifndef STARTER_H
#define STARTER_H

#include "Course.h"
#include <iostream>
using namespace std;

class Starter : public Course
{
  public:
    Starter(int maxNumberOfItems);
    void recommendBeverage() override;
};

#endif