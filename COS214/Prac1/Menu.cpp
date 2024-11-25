#include "Menu.h"

Menu::Menu()
{}

bool Menu::addCourse(Course* course)
{
  if(courses.find(course->getDescription()) != courses.end())
    return false;
  courses.insert({course->getDescription() , course});
  return true;
}

bool Menu::addMenuItem(string courseDescription , string description , float price , int stock)
{
  if(courses.find(courseDescription) == courses.end())
    return false;
  Course* active = courses.at(courseDescription);
  return active->addMenuItem(description,price,stock);
}

void Menu::printMenu()
{
  for(auto i : courses)
  {
    cout << i.second->getDescription() << endl;
    i.second->printMenuItems();
  }
}

void Menu::inventory()
{
  for(auto i : courses)
  {
    cout << i.second->getDescription() << endl;
    i.second->printInventory();
  }
}

float Menu::orderItem(string courseDescription, char item)
{
  auto course = courses.find(courseDescription);
  if(course == courses.end()) 
  {
    return 0;
  }
  Course* active = course->second;
  int index = item - 'a';
  MenuItem* menuItem = active->getMenuItem(index);
  if(menuItem == nullptr || menuItem->getStock() == 0)
  {
    return 0;
  }
  menuItem->reduceStock();
  return menuItem->getPrice();
}

bool Menu::isCoursesEmpty()
{
  int sum = 0;
  for(auto i : courses)
  {
    int Counter = 0;
    MenuItem* item = i.second->getMenuItem(Counter);
    while(item != nullptr)
    {
      item = i.second->getMenuItem(Counter++);
    }
    sum += Counter;
  }
  if(sum == 0)
  {
    return true;
  }
  return false;
}

void Menu::closeShop()
{
  cout << "Closing shop. Deleting all " << courses.size() << " courses" << endl;
  for(auto i : courses)
  {
    delete i.second;
  }
  courses.clear();
}

Menu::~Menu()
{
  cout << "Menu destructor called" << endl;
  closeShop();
}