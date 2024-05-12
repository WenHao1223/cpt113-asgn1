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
#include "Discount.h"
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
  cout << item.quantity << " units available." << endl;
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

  // cout << "employees address: " << &employees << endl;
  // for (int i = 0; i < MAX_EMPLOYEES; i++) {
  //   cout << "employees[" << i << "] address: " << &employees[i] << endl;
  // }

  // Done: show employee role
  // @TjeEwe useful for showing different menu options based on role
  // Supervisor, Baker, Cashier
  // cout << "Role: " << employees[0].getRole() << endl;

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

  // WIP: create new employee by supervisor
  // employees[0].createNewEmployee(employees, "C2", "Bob", "Supervisor");
  // cout << "now working fine" << endl;

  // Done: change employee role
  // Juin Ewe and Jennie are now Cashiers *^____^*
  // employees[0].changeEmployeeRole(employees, 1, "Cashier");
  // employees[0].changeEmployeeRole(employees, 0, "Baker");
  // employees[0].changeEmployeeRole(employees, 3, "Baker");

  // Done: delete employees
  // employees[0].deleteEmployee(employees, 3);

  // Done: display all employee details
  // employees[0].displayAllEmployeeDetails(employees);

  // Done: add bakery item to cart
  // employees[1].addBakeryItemToCart(0, 2);
  // employees[2].addBakeryItemToCart(0, 2);
  // cout << endl;
  employees[1].bakeNewBakeryItem(0, 3);
  employees[1].bakeNewBakeryItem(2, 3);
  // cout << endl;
  employees[2].addBakeryItemToCart(0, 2);
  employees[2].addBakeryItemToCart(0, 3);
  employees[2].addBakeryItemToCart(2, 1);
  // cout << endl;

  // Done: display cart details
  employees[2].displayCartDetails();
  // employees[3].displayCartDetails();

  // Done: calculate total cost of cart
  // employees[2].calculateCartTotalCost();

  // Done: calculate total price of cart
  // employees[2].calculateCartTotalPrice();

  // Done: calculate total profit of cart
  // employees[2].calculateCartTotalProfit();

  // Done: calculate cart item count
  // employees[2].getCartItemCount();

  // Done: remove bakery item from cart
  // employees[2].removeBakeryItemFromCart(0);
  // employees[2].displayCartDetails();

  // Done: update bakery item quantity in cart
  // employees[2].updateBakeryItemQuantityInCart(0, 3);
  // employees[2].displayCartDetails();

  // Done: clear whole cart
  // employees[2].clearCart();
  // employees[2].displayCartDetails();

  // Done: access discount list
  // employees[0].accessDiscountList();

  // Done: display discount details
  // employees[0].accessDiscountDetails(1);

  // Done: add new discount
  // employees[0].addNewDiscount();
  // employees[0].accessDiscountList();
  // employees[0].accessDiscountDetails(2);

  // Done: edit discount name
  // employees[0].editDiscountName(1, "New Discount");
  // employees[0].accessDiscountDetails(1);

  // Done: edit discount percentage
  // employees[0].editDiscountPercentage(1, 20.0);
  // employees[0].accessDiscountDetails(1);

  // Done: edit discount description
  // employees[0].editDiscountDescription(1, "New Description");
  // employees[0].accessDiscountDetails(1);

  // Done: disable discount
  // employees[0].disableDiscount(1);
  // employees[0].accessDiscountDetails(1);

  // Done: enable discount
  // employees[0].enableDiscount(1);
  // employees[0].accessDiscountDetails(1);

  // Done: show available discount based on cart total price
  // extra option as it is used in checkout()
  // employees[2].showDiscountBasedOnCartTotalPrice();
  // cout << endl;

  // Done: calculate cart total price after discount
  // extra option as it is used in checkout()
  // employees[2].calculateDiscountedTotalPrice();
  // cout << endl;
  // @TjeEwe only show line below to store discounted price
  // double discountedPrice = employees[2].calculateDiscountedTotalPrice();

  // Done: checkout
  // employees[2].accessMenuItem(0);
  employees[2].checkout();
  employees[2].accessMenuItem(0);

  // Done: calculate price after discount
  // not using this since it is used in checkout()
  // discount choice based on showDiscountBasedOnCartTotalPrice(), start from 1
  // @TjeEwe must use this function to get discount
  // employees[2].applyDiscount(3);
  // employees[2].applyDiscount(2);
  // cout << endl;

  // Done: show receipt
  employees[2].showReceipt();
  
  return 0;
}