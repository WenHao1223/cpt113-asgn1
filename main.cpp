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
#include "Constant.h"
#include "Ingredient.h"
#include "BakeryItem.h"
#include "IngredientInventory.h"
#include "Cart.h"
#include "Supervisor.h"
#include "Baker.h"
#include "Cashier.h"
#include "Employee.h"

// global constant
const int MAX_EMPLOYEES = Constant::MAX_EMPLOYEES;

void accessMenuDetails(BakeryItem & item) {
  cout << item.name << endl;
  cout << item.description << endl;
  cout << "RM " << setprecision(2) << fixed << item.pricePerUnit << endl;
  cout << "Ingredients: " << endl;
  for (int i = 0; i < item.ingredientCount; i++) {
    // display ingredient details as 200g sugar, 1 egg, 1 cup flour
    if (item.ingredient[i].getCountable()) {
      cout << item.ingredient[i].getPiece() << "x " << item.ingredient[i].getName();
    } else {
      cout << item.ingredient[i].getWeight() << "g " << item.ingredient[i].getName();
    }
    if (i < item.ingredientCount - 1) {
      cout << ", ";
    }
  }
  cout << endl;
  if (item.disabled) {
    cout << "Sold out." << endl;
  } else {
    cout << "Available." << endl;
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
  // cout << endl;
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

  // Done: add new ingredient into inventory
  // employees[0].addNewInventoryIngredientWeight("Salt", 0.01, 500);
  // employees[0].addNewInventoryIngredientPiece("Egg", 0.5, 10);

  // Done: Get inventory ingredient list
  // employees[0].getAllInventoryIngredientName();

  // Done: create new bakery item
  // system will need to login and logout many times to create bakery items
  // @TjeEwe check if user input larger than MAX_BAKERY_ITEMS
  // before creating new bakery item
  // employees[0].accessMenuList();
  // employees[0].checkIngredientInventory();
  // employees[0].createBakeryItem();
  // after creating new bakery item
  // employees[0].accessMenuList();
  // employees[0].accessMenuItem(2);
  // cout << endl;

  // Done: withdraw bakery item
  // employees[0].withdrawBakeryItem(1);
  // cout << endl;
  // employees[0].accessMenuItem(1);

  // Done: enable bakery item
  // employees[0].enableBakeryItem(1);
  // cout << endl;
  // employees[0].accessMenuItem(1);

  // Done: change bakery item price
  // employees[0].accessMenuItem(1);
  // employees[0].changeBakeryItemPrice(1, 10.0);
  // employees[0].accessMenuItem(1);

  // Done: calculate cost of bakery item
  // employees[0].calculateBakeryItemCost(1);

  // Done: calculate profit of bakery item
  // employees[0].calculateBakeryItemProfit(1);

  // Done: compare cost vs profit of bakery item
  // employees[0].compareCostVsProfit(1);

  // Done: compare cost vs price of bakery item
  // employees[0].compareCostVsPrice(1);

  // Done: bake new bakery item
  // employees[1].bakeNewBakeryItem(0, 3);
  // cout << endl;
  // employees[1].bakeNewBakeryItem(0, 2);
  // cout << endl;
  // employees[1].bakeNewBakeryItem(1, 2);

  // Done: create new employee by supervisor
  // employees[0].createNewEmployee(employees, "S2", "Bob", "Baker");

  // Done: change employee role
  // Juin Ewe and Jennie are now Cashiers *^____^*
  // employees[0].changeEmployeeRole(employees, 1, "Cashier");
  // employees[0].changeEmployeeRole(employees, 0, "Baker");
  // employees[0].changeEmployeeRole(employees, 3, "Baker");

  // Done: delete employees
  // employees[0].deleteEmployee(employees, 3);

  // Done: display all employee details
  // employees[0].displayAllEmployeeDetails(employees);

  // Cart testCart = Cart();
  // IngredientInventory * ingredientInventory = new IngredientInventory[Constant::MAX_INGREDIENTS_INVENTORY];
  // ingredientInventory[0] = IngredientInventory("Ingredient 1", 0.0005, 100000.0);
  // ingredientInventory[1] = IngredientInventory("Ingredient 2", 20.0, 200);
  // ingredientInventory[2] = IngredientInventory("Ingredient 3", 30.0, 0.0);
  
  // BakeryItem bakeryItems[3] = {
  //   BakeryItem("Croissant", "A buttery, flaky, viennoiserie pastry of Austrian origin, named for its historical crescent shape.", 3.50, ingredientInventory, 3, "Mix ingredients, roll dough, fold dough, cut dough, shape dough, proof dough, bake dough."),
  //   BakeryItem("Pain au Chocolat", "A type of viennoiserie sweet roll consisting of a cuboid-shaped piece of yeast-leavened laminated dough, similar in texture to a puff pastry, with one or two pieces of dark chocolate in the centre.", 3.00, ingredientInventory, 3, "Mix ingredients, roll dough, fold dough, cut dough, shape dough, proof dough, bake dough."),
  //   BakeryItem("Palmier", "A pastry in the shape of a palm leaf or a butterfly.", 2.00, ingredientInventory, 3, "Mix ingredients, roll dough, fold dough, cut dough, shape dough, proof dough, bake dough.")
  // };
  // testCart.addBakeryItemToCart(bakeryItems[0], 2);
  // testCart.addBakeryItemToCart(bakeryItems[1], 3);
  // testCart.addBakeryItemToCart(bakeryItems[2], 4);
  // testCart.displayCartDetails();
  // testCart.calculateTotalCost();
  // testCart.calculateTotalProfit();
  // cout << "Total cost: RM " << setprecision(2) << fixed << testCart.getTotalCost() << endl;
  // cout << "Total profit: RM " << setprecision(2) << fixed << testCart.getTotalProfit() << endl;

  // testCart.compareCostVsPrice(1);
  // testCart.compareCostVsProfit(1);

  // cout << "Cart item count: " << testCart.getCartItemCount() << endl;

  // Done: add bakery item to cart
  // employees[1].addBakeryItemToCart(0, 2);
  // employees[2].addBakeryItemToCart(0, 2);
  // cout << endl;
  employees[1].bakeNewBakeryItem(0, 3);
  cout << endl;
  employees[2].addBakeryItemToCart(0, 2);
  employees[2].addBakeryItemToCart(0, 1);
  cout << endl;

  // display cart details
  employees[2].displayCartDetails();
  
  return 0;
}