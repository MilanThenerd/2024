#include "Course.h"

Course::Course(string description , int maxNumberOfItems)
{
  this->description = description;
  this->maxNumberOfItems = maxNumberOfItems;
}

string Course::getDescription()
{
  return description;
}
bool Course::addMenuItem(string description , float price , int stock)
{
  if(menuItems.size() >= static_cast<size_t>(maxNumberOfItems))
  {
    return false;
  }
  MenuItem* newItem = new MenuItem(description,price,stock);
  for(MenuItem* item : menuItems)
  {
    if(item->getDescription() == newItem->getDescription())
    {
      delete newItem;
      return false;
    }
  }
  menuItems.push_back(newItem);
  return true;
}

void Course::printMenuItems()
{
  char index = 'a';
  for(MenuItem* item : menuItems)
  {
    cout << "\t" << index << ".\t" << item->getDescription() << endl;
    index++;
  }
}

void Course::printInventory()
{
  char index = 'a';
  for(MenuItem* item : menuItems)
  {
    std::cout << "\t" << index << ".\t" << item->getDescription() << "\t" << item->getPrice() << "\t" << item->getStock() << std::endl;
    index++;
  }
}

MenuItem* Course::getMenuItem(int index)
{
  if (index >= 0 && static_cast<size_t>(index) < menuItems.size()) 
  {
    return menuItems[index];
  }
  return nullptr;
}

Course::~Course()
{
  for(MenuItem* item : menuItems)
  {
    delete item;
  }
}

