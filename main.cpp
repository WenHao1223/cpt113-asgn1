// run this file by typing the following command in the terminal
// g++ *.cpp -o main.exe && ./main

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

// forward declaration
class Employee;

// class declaration
#include "Ingredient.h"
#include "BakeryItem.h"
#include "Supervisor.h"
#include "Baker.h"
#include "Cashier.h"
#include "Employee.h"

const int MAX_BAKERY_ITEMS = 10;

void accessMenuList(BakeryItem items []) {
  for (int i = 0; i < items->bakeryItemCount; i++) {
    // cout << "Item address: " << &items[i] << endl;
    cout << i+1 << ". " << items[i].name << endl;
  }
  cout << endl;
}

void accessMenuDetails(BakeryItem & item) {
  cout << item.name << endl;
  cout << item.description << endl;
  cout << "RM" << setprecision(2) << fixed << item.pricePerUnit << endl;
  if (item.disabled) {
    cout << "Out of stock." << endl;
  } else {
    cout << "In stock." << endl;
  }
  cout << endl;
}

int main () {
  // Done: create employees
  Employee supervisor1("S1", "Supervisor 1", "Supervisor");
  // Employee baker1("B1", "Baker 1", "Baker");
  // Employee cashier1("C1", "Cashier 1", "Cashier");

  cout << endl;

  // Done: display employee details
  // supervisor1.displayEmployeeDetails();
  // baker1.displayEmployeeDetails();
  // cashier1.displayEmployeeDetails();

  // WIP: create bakery items, to be added into Baker class
  // but now for testing Bakery Item -related function
  // @TjeEwe @AeroRin this section will not include in the final project
  // employees will create bakery items
  // system will need to login and logout many times to create bakery items
  const int INGREDIENT1_COUNT = 1;
  const int INGREDIENT2_COUNT = 3;
  Ingredient ingredient1[INGREDIENT1_COUNT] = {
    Ingredient("Ingredient 1 of Item 1", 10.0, 100.0)
  };
  Ingredient ingredient2[INGREDIENT2_COUNT] = {
    Ingredient("Ingredient 1 of Item 1", 20.0, 200.0),
    Ingredient("Ingredient 2 of Item 2", 30.0, 300.0),
    Ingredient("Ingredient 3 of Item 3", 40.0, 400.0)
  };

  BakeryItem * bakeryItems = new BakeryItem[MAX_BAKERY_ITEMS];
  // @TjeEwe check if user input larger than MAX_BAKERY_ITEMS
  bakeryItems[0] = BakeryItem("Item 1", "Description 1", 10.0, ingredient1, INGREDIENT1_COUNT, "Recipe 1");
  bakeryItems[1] = BakeryItem("Item 2", "Description 2", 20.0, ingredient2, INGREDIENT2_COUNT, "Recipe 2");

  cout << endl;

  // Done: display bakery item details
  // item1.displayBakeryItemDetails();
  // item2.displayBakeryItemDetails();

  // Done: Access menu list
  // cout << "Bakery Item Address: " << &bakeryItems << endl;
  accessMenuList(bakeryItems);

  // Done: Access menu details
  accessMenuDetails(bakeryItems[0]);

  // 

  delete [] bakeryItems;
  
  return 0;
}