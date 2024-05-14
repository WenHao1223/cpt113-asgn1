// run this file by typing the following command in the terminal
// g++ *.cpp -o main.exe && ./main

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

// forward declaration
class Employee;

// class declaration
#include "Constant.h"
#include "Discount.h"
#include "Ingredient.h"
#include "Cake.h"
#include "BakeryItem.h"
#include "IngredientInventory.h"
#include "Cart.h"
#include "Supervisor.h"
#include "Baker.h"
#include "Cashier.h"
#include "Employee.h"

// global constant
const int MAX_EMPLOYEES = Constant::MAX_EMPLOYEES;

string convertTimeToYYYYMMDD() {
  // Get current time
  auto currentTime = time(0);
  auto* timeNow = localtime(&currentTime);

  char buffer[9];
  strftime(buffer, sizeof(buffer), "%Y%m%d", timeNow);

  return buffer;
}

string convertTimeTOYYYY_MM__DD() {
  // Get current time
  auto currentTime = time(0);
  auto* timeNow = localtime(&currentTime);

  char buffer[11];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeNow);

  return buffer;
}

string convertTimeToYYYY__MM__DD_HH_MM_SS() {
  // Get current time
  auto currentTime = time(0);
  auto* timeNow = localtime(&currentTime);

  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeNow);

  return buffer;
}

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

int findEmployeeIndex(Employee employees[], string employeeID) {
  int index = -1;
  for (int i = 0; i < MAX_EMPLOYEES; i++) {
    if (employees[i].employeeID == employeeID) {
      index = i;
      break;
    }
  }
  return index;
}

int main () {
  // Done: display current date in YYYYMMDD format
  const string DATE_YYYYMMDD = convertTimeToYYYYMMDD();
  // cout << DATE_YYYYMMDD << endl;

  // int numberOfIngredients;

  // Done: create employees
  // not use anymore since data fetch from file
  // Employee employees[MAX_EMPLOYEES] = {
  //   Employee("S1", "Adam", "Supervisor", "password"),
  //   Employee("B1", "Juin Ewe", "Baker", "password"),
  //   Employee("C1", "Jennie Ng", "Cashier", "password")
  // };

  Employee * employees = new Employee[MAX_EMPLOYEES];

  // read employee data from employeeData.csv
  string line;
  int employeeCount = 0;
  ifstream employeeDataFile("files/employeeData.csv");
  if (employeeDataFile) {
    getline(employeeDataFile, line); // skip first line (header)
    while (!employeeDataFile.eof() && employeeCount < MAX_EMPLOYEES) {
      string employeeID;
      string name;
      string role;
      string password;
      getline(employeeDataFile, employeeID, ',');
      getline(employeeDataFile, name, ',');
      getline(employeeDataFile, role, ',');
      getline(employeeDataFile, password);

      employees[employeeCount].setEmployeeID(employeeID);
      employees[employeeCount].setName(name);
      employees[employeeCount].setRole(role);
      employees[employeeCount].setPassword(password);

      employeeCount++;
    }
  } else {
    cout << "Error: employeeData.csv not found" << endl;
    return 0;
  }
  cout << endl;

  // cout << "employees address: " << &employees << endl;
  // for (int i = 0; i < MAX_EMPLOYEES; i++) {
  //   cout << "employees[" << i << "] address: " << &employees[i] << endl;
  // }

  // Done: login
  cout << "Employee list: " << endl;
  for (int i = 0; i < MAX_EMPLOYEES; i++) {
    if (employees[i].getName() != "") {
      cout << i+1 << ". " << employees[i].getName() << endl;
    }
  }
  // @AeroRin input validation
  cout << "Choose employee: ";
  int employeeChoice;
  cin >> employeeChoice;
  string employeeID;
  string password;
  cout << "Enter employee ID: ";
  cin >> employeeID;
  cout << "Enter password: ";
  cin >> password;
  // @TjeEwe .login() will return true if login is successful
  // then only start accessing other functions
  employees[employeeChoice-1].login(employeeID, password);

  // employees[0].login("S1", "password");
  // employees[0].login("B1", "password"); // wrong id
  // employees[2].login("C1", "password123"); // wrong password

  // Done: show employee id
  // @TjeEwe useful for showing different menu options based on employee id
  // S1, B1, C1
  // cout << "Employee ID: " << employees[0].getEmployeeID() << endl;

  // Done: show employee name
  // @TjeEwe useful for showing different menu options based on employee name
  // Adam, Juin Ewe, Jennie Ng
  // cout << "Name: " << employees[0].getName() << endl;

  // Done: show employee role
  // @TjeEwe useful for showing different menu options based on role
  // Supervisor, Baker, Cashier
  // cout << "Role: " << employees[0].getRole() << endl;

  // Done: display employee details
  // employees[0].displayEmployeeDetails();
  // employees[1].displayEmployeeDetails();
  // employees[2].displayEmployeeDetails();

  // Done: display bakery item details
  // not used anymore
  // bakeryItems[0].displayBakeryItemDetails();

  // Done: find the index in employees using employeeID
  // -1 if not found
  // cout << "Employee index: " << findEmployeeIndex(employees, "C1") << endl;

  // use only once per program
  // can be started by random employee
  employees[2].startBakery(convertTimeTOYYYY_MM__DD());
  cout << endl;

  // Done: set ingredient cost of bakery item to latest ingredient cost from inventory
  // not used anymore as it is done in Employee::startBakery()
  // employees[2].setIngredientCostToInventoryIngredientCost();

  // Done: Access menu list
  // employees[0].accessMenuList();
  // cout << endl;

  // Done: Access menu details
  // employees[0].accessMenuItem(1);

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
  // employees[0].restockIngredientInventory(0, 50003.6);
  // employees[0].restockIngredientInventory(2, 300);
  // employees[0].restockIngredientInventory(1, 3200);
  // employees[2].restockIngredientInventory(1, 300);
  // employees[0].checkIngredientInventory();
  // cout << endl;

  // Done: change ingredient cost
  // employees[0].accessIngredientInventoryDetails(1);
  // employees[0].changeIngredientCost(0, 30.0);
  // employees[1].changeIngredientCost(0, 30.0);
  // employees[2].changeIngredientCost(0, 30.0);
  // cout << endl;
  // employees[0].accessIngredientInventoryDetails(1);
  // cout << endl;

  // Done: add new ingredient into inventory
  // employees[0].addNewInventoryIngredientWeight("Salt", 0.01, 500);
  // employees[0].addNewInventoryIngredientWeight("TestNewUncountable", 0.01, 500);
  // employees[0].addNewInventoryIngredientPiece("TestNewCountable", 3.1, 50);
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
  // employees[0].createBakeryItem();
  // employees[0].checkIngredientInventory();
  // after creating new bakery item
  // employees[0].accessMenuList();
  // employees[0].accessMenuItem(3);
  // cout << endl;

  // Done: withdraw bakery item
  // employees[0].accessMenuItem(1);
  // employees[0].withdrawBakeryItem(1);
  // employees[0].accessMenuItem(1);

  // Done: enable bakery item
  // employees[0].enableBakeryItem(1);
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
  // employees[0].accessMenuItem(0);
  // employees[1].bakeNewBakeryItem(2, 6);
  // cout << endl;
  // employees[1].bakeNewBakeryItem(0, 2);
  // cout << endl;
  // employees[1].bakeNewBakeryItem(1, 2);
  // employees[0].accessMenuItem(0);

  // Done: display all employee details
  // employees[0].displayAllEmployeeDetails(employees);

  // Done: create new employee by supervisor
  // employees[0].createNewEmployee(employees, "C3", "Bob", "Supervisor", "password");
  // employees[3].login("C2", "password");

  // Done: change employee role
  // Juin Ewe and Jennie are now Cashiers *^____^*
  // employees[0].changeEmployeeRole(employees, 1, "Cashier");
  // employees[0].changeEmployeeRole(employees, 0, "Baker");
  // employees[0].changeEmployeeRole(employees, 3, "Baker");
  // employees[0].displayAllEmployeeDetails(employees);

  // WIP: delete employees
  // @WenHao1223
  // employees[0].deleteEmployee(employees, 2);
  // employees[0].displayAllEmployeeDetails(employees);

  // add cake to cart by total weight
  // employees[2].addCakeByWeightToCart(2, 200);
  // employees[2].addCakeByWeightToCart(2, 1200);
  // employees[2].addCakeByWeightToCart(1, 200);

  // Done: add bakery item to cart
  // employees[1].addBakeryItemToCart(0, 2);
  // employees[2].addBakeryItemToCart(0, 2);
  // cout << endl;
  // employees[1].bakeNewBakeryItem(0, 10);
  // employees[1].bakeNewBakeryItem(2, 3);
  // employees[0].accessMenuItem(2);
  // employees[1].accessIngredientInventoryDetails(1);
  // cout << endl;
  // employees[2].addBakeryItemToCart(0, 2);
  // employees[2].addBakeryItemToCart(0, 3);
  // employees[2].addBakeryItemToCart(2, 1);
  // cout << endl;

  // // Done: display cart details
  // employees[2].displayCartDetails();
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
  // employees[2].updateBakeryItemQuantityInCart(0, 4);
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

  // Done: edit minimum purchase
  // employees[0].editDiscountMinimumPurchase(1, 10.0);
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

  // Done: delete discount
  // employees[0].deleteDiscount(1);
  // employees[0].accessDiscountList();

  // Done: show available discount based on cart total price
  // extra option as it is used in checkout()
  // employees[2].showDiscountBasedOnCartTotalPrice();
  // cout << endl;
  // employees[2].showDiscountBasedOnCartTotalPrice();
  // cout << endl;

  // Done: calculate price after discount
  // not using this since it is used in checkout()
  // discount choice based on showDiscountBasedOnCartTotalPrice(), start from 1
  // employees[2].applyDiscount(1);
  // cout << endl;
  // employees[2].applyDiscount(1);
  // cout << endl;

  // Done: calculate cart total price after discount
  // extra option as it is used in checkout()
  // employees[2].calculateDiscountedTotalPrice();
  // employees[2].calculateDiscountedTotalPrice();
  // cout << endl;
  // not needed since integrated in checkout function
  // double discountedPrice = employees[2].calculateDiscountedTotalPrice();

  // Done: checkout
  // employees[2].accessMenuItem(0);
  // employees[2].checkout(convertTimeToYYYY__MM__DD_HH_MM_SS());
  // employees[2].accessMenuItem(2);

  // cout << endl << endl;

  // second order

  // employees[2].displayCartDetails();
  // employees[2].addBakeryItemToCart(0, 3);
  // employees[2].displayCartDetails();
  // employees[2].checkout(convertTimeToYYYY__MM__DD_HH_MM_SS());

  // Done: show receipt
  // default parameter is referring previous order's receipt
  // employees[2].showReceipt(DATE_YYYYMMDD);
  // DATE_YYYYMMDD = today's date
  // employees[2].showReceipt(DATE_YYYYMMDD, 1);
  // employees[2].showReceipt("20240510", 1);
  // employees[1].showReceipt("20240510", 1);
  // employees[0].showReceipt("20240510", 1);

  // Done: show total debit
  // employees[2].showTotalDebit();

  // Done: show total credit
  // employees[2].showTotalCredit();

  // Done: show total profit per day
  // employees[2].showTotalProfitPerDay();

  // show total balance
  // employees[2].showTotalBalance();

  // employees[2].closeBakery(convertTimeTOYYYY_MM__DD());

  // Done: display balance sheet
  // can be accessed even bakery is not opened
  // employees[0].displayBalanceSheet();

  // Done: access transaction history
  // employees[0].accessTransactionHistory(DATE_YYYYMMDD);
  // can be accessed even bakery is not opened
  // except if the date is not available
  // employees[0].accessTransactionHistory("20240510");
  return 0;
}