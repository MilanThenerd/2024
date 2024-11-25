#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include "MenuItem.h"
#include <iostream>
using namespace std;

class Course
{
  protected:
    string description;
    int maxNumberOfItems;
    vector<MenuItem*> menuItems;
  public:
    Course(string description , int maxNumberOfItems);
    string getDescription();
    bool addMenuItem(string description , float price , int stock);
    void printMenuItems();
    void printInventory();
    MenuItem* getMenuItem(int index);
    virtual void recommendBeverage() = 0;
    virtual ~Course();
};

#endif