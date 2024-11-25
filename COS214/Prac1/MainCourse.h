#ifndef MAINCOURSE_H
#define MAINCOURSE_H

#include "Course.h"
#include <iostream>
using namespace std;

class MainCourse : public Course
{
  public:
    MainCourse(int maxNumberOfItems);
    void recommendBeverage() override;
};

#endif