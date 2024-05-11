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
#include "IngredientInventory.h"
#include "Supervisor.h"
#include "Baker.h"
#include "Cashier.h"
#include "Employee.h"

// global constant
const int MAX_EMPLOYEES = 10;
// const int MAX_BAKERY_ITEMS = 10;
const int MAX_INGREDIENTS_INVENTORY = 20;

void accessMenuDetails(BakeryItem & item) {
  cout << item.name << endl;
  cout << item.description << endl;
  cout << "RM " << setprecision(2) << fixed << item.pricePerUnit << endl;
  cout << "Ingredients: " << endl;
  for (int i = 0; i < item.ingredientCount; i++) {
    // display ingredient details as 200g sugar, 1 egg, 1 cup flour
    if (item.ingredient[i].getWeight() > 0) {
      cout << item.ingredient[i].getWeight() << "g " << item.ingredient[i].getName();
    }
    if (item.ingredient[i].getPiece() > 0) {
      cout << item.ingredient[i].getPiece() << " " << item.ingredient[i].getName();
    }
    if (i < item.ingredientCount - 1) {
      cout << ", ";
    }
  }
  cout << endl;
  if (item.disabled) {
    cout << "Out of stock." << endl;
  } else {
    cout << "In stock." << endl;
  }
  cout << endl;
}

int main () {
  // int numberOfIngredients;

  // Done: create employees
  Employee employees[MAX_EMPLOYEES] = {
    Employee("S1", "Adam", "Supervisor"),
    Employee("B1", "Juin Ewe", "Baker"),
    Employee("C1", "Jennie Ng", "Cashier")
  };

  cout << endl;

  // Done: display employee details
  // employees[0].displayEmployeeDetails();
  // employees[1].displayEmployeeDetails();
  // employees[2].displayEmployeeDetails();

  // Done: display bakery item details
  // bakeryItems[0].displayBakeryItemDetails();

  // Done: Access menu list
  // employees[0].accessMenuList();

  // Done: Access menu details
  // employees[0].accessMenuItem(1);

  // use only once per program
  // can be started by random employee
  // @TjeEwe inventory file shall be read in Employee::startBakery()
  employees[2].startBakery();
  cout << endl;

  // Done: display ingredient inventory list
  // employees[0].displayIngredientInventoryList();
  // employees[1].displayIngredientInventoryList();
  // employees[2].displayIngredientInventoryList();

  // Done: access ingredient inventory details
  // parameter is the exact ingredient index to be accessed
  // @TjeEwe need to print ingredient inventory list available
  // and let user choose which ingredient to access
  // employees[0].accessIngredientInventoryDetails(1);
  cout << endl;
  // employees[1].accessIngredientInventoryDetails(1);
  // cout << endl;
  // employees[2].accessIngredientInventoryDetails(1);
  // cout << endl;

  // Done: check all ingredients in ingredient inventory
  // employees[0].checkIngredientInventory();
  // cout << endl;
  // employees[1].checkIngredientInventory();
  // cout << endl;
  // employees[2].checkIngredientInventory();
  // cout << endl;

  // Done: restock ingredient
  // @TjeEwe need to print ingredient inventory list available
  // and let supervisor choose which ingredient to restock
  // then how many pieces or weight to restock
  // employees[0].restockIngredientInventory(0, 200.0);
  // employees[0].restockIngredientInventory(1, 300);
  // employees[2].restockIngredientInventory(1, 300);

  // Done: change ingredient cost
  // employees[0].changeIngredientCost(0, 20.0);
  // employees[1].changeIngredientCost(0, 20.0);
  // employees[2].changeIngredientCost(0, 20.0);
  // cout << endl;

  // create new bakery item
  // system will need to login and logout many times to create bakery items
  // @TjeEwe check if user input larger than MAX_BAKERY_ITEMS
  employees[0].createBakeryItem();
  employees[0].accessMenuList();
  employees[0].accessMenuItem(2);
  
  return 0;
}