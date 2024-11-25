#include "Menu.h"
#include "Starter.h"
#include "MainCourse.h"
#include "Dessert.h"
#include <iostream>

using namespace std;

int main()
{ 
  Menu* menu = new Menu();

  Starter* starter = new Starter(5);
  MainCourse* main = new MainCourse(5);
  Dessert* dessert = new Dessert(5);
  menu->addCourse(starter);
  menu->addCourse(main);
  menu->addCourse(dessert);
  menu->addMenuItem("Starter","Onion Soup", 35.99 , 6);
  menu->addMenuItem("Starter","Caesar Salad", 45.99 , 4);
  menu->addMenuItem("Main","Steak", 105.99 , 5);
  menu->addMenuItem("Main","Chicken", 95.99 , 2);
  menu->addMenuItem("Main","Fish", 85.99 , 3);
  menu->addMenuItem("Dessert","Ice Cream" , 65.99 , 7);
  // cout << menu->orderItem("Main", 'a') << endl;
  // cout << menu->orderItem("Main", 'a') << endl;
  // cout << menu->orderItem("Main", 'a') << endl;
  // cout << menu->orderItem("Main", 'a') << endl;
  // cout << menu->orderItem("Main", 'a') << endl;
  // cout << menu->orderItem("Main", 'a') << endl;
  // cout << menu->orderItem("Main", 'a') << endl;
  // cout << menu->orderItem("Main", 'a') << endl;
  // cout << menu->orderItem("Main", 'a') << endl;
  
  menu->inventory();

  delete menu;
  return 0;
}