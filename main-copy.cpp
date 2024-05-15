// run this file by typing the following command in the terminal
// g++ Baker.cpp BakeryItem.cpp Cake.cpp Cart.cpp Cashier.cpp Discount.cpp Employee.cpp Ingredient.cpp IngredientInventory.cpp Supervisor.cpp main-copy.cpp -o main-copy.exe && main-copy

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

void displaySupervisorMenu();
void displayBakerMenu();
void displayCashierMenu();

void processSupervisorChoice(Employee* employee, int employeeID);
void processBakerChoice();
void processCashierChoice();

// For Supervisor
void checkBakeryItem(Employee* employees, int employeeID);
void InventoryManagement(Employee* employees, int employeeID);

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

void accessMenuDetails(const BakeryItem * item) {
  cout << "==========================================================\n";
  cout << "Bakery Item: " << item->name << endl;
  cout << "==========================================================\n";
  cout << "Description: " << item->description << endl;
  cout << "Quantity: " << item->quantity << " units available." << endl;
  cout << "Price: RM " << setprecision(2) << fixed << item->pricePerUnit << endl;
  cout << "Ingredients: ";
  for (int i = 0; i < item->ingredientCount; i++) {
    // display ingredient details as 200g sugar, 1 egg, 1 cup flour
    if (item->ingredient[i].getCountable()) {
      cout << item->ingredient[i].getPiece() << "x " << item->ingredient[i].getName();
    } else {
      cout << item->ingredient[i].getWeight() << "g " << item->ingredient[i].getName();
    }
    if (i < item->ingredientCount - 1) {
      cout << ", ";
    }
  }
  cout << endl;

  cout << "Status: ";
  if (item->disabled) {
    cout << "Sold out." << endl;
  } else {
    cout << "Available." << endl;
  }
  cout << "==========================================================\n";
  cout << endl;
}

int findEmployeeIndex(Employee employees[], string employeeID) {
  int index = -1;
  for (int i = 0; i < MAX_EMPLOYEES; i++) {
    if (employees[i].getEmployeeID() == employeeID) {
      index = i;
      break;
    }
  }
  return index;
}

// Convert from char to int
int charToInt(char c) {
  return c - '0';
}

int login (Employee employees[]) {
  cout << "+=====================================+\n";
  cout << "|     >_< EMPLOYEE LOGIN PAGE >_<     |\n";
  cout << "+=====================================+\n";
  cout << "| Employee list:                      |\n";
  cout << "---------------------------------------\n";
  cout << "| No. | Employee Name                 |\n";
  cout << "---------------------------------------\n";
  for (int i = 0; i < MAX_EMPLOYEES; i++) {
    if (employees[i].getName() != "") {
        cout << "| " << setw(3) << left << i+1 << " | " << setw(29) << left << employees[i].getName() << " |\n";
    }
  }
  cout << "---------------------------------------\n";

  int employeeChoice;

  do {
    cout << "Choose employee: ";
    cin >> employeeChoice;
    if (employeeChoice < 1 || employeeChoice > MAX_EMPLOYEES || employees[employeeChoice-1].getName() == "") {
      cout << "Invalid choice. Please try again." << endl;
    }
    
    string employeeID;
    cout << "Enter employee ID: ";
    cin >> employeeID;

    string password;
    cout << "Enter password: ";
    cin >> password;
    cout << endl;

    if (employees[employeeChoice-1].login(employeeID, password)) {
      break;
    } else {
      cout << endl;
      cout << "Invalid employee ID or password. Please try again." << endl;
    }
  } while (true);

  return employeeChoice-1;
}


int main () {
  // Done: display current date in YYYYMMDD format
  const string DATE_YYYYMMDD = convertTimeToYYYYMMDD();

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

  // display welcome message
  string loginInput;
  int employeeID;
  cout << "==========================================================\n";
  cout << "||                                                      ||\n";
  cout << "||                   Eid Delights Bakery                ||\n";
  cout << "||                                                      ||\n";
  cout << "==========================================================\n";
  cout << "Today's Date: " << DATE_YYYYMMDD << endl;
  cout << "Please any keys to login and continue: " << endl;
  cout << "Please login to close the bakery system";
  cin >> loginInput;
  cout << endl;

  // Done: login
  cout << "Welcome to Eid Delights Bakery!" << endl;
  employeeID = login(employees); // Employee Index
  employees[employeeID].startBakery(DATE_YYYYMMDD);

  string role = employees[employeeID].getRole();

  if (role == "Supervisor"){
    processSupervisorChoice(employees, employeeID);
  }
  else if (role == "Baker"){
    displayBakerMenu();
    processBakerChoice();
  }
  else if (role == "Cashier"){
    displayCashierMenu();
    processCashierChoice();
  }
  return 0;
}

void displaySupervisorMenu(){
  cout << "==========================================================\n";
  cout << "||                                                      ||\n";
  cout << "||                   Supervisor Menu                    ||\n";
  cout << "||                                                      ||\n";
  cout << "==========================================================\n";
  cout << "| 1. Check Bakery Item                                   |\n"; // View today's menu items and details
  cout << "| 2. Inventory Management                                |\n"; // Manage inventory list and details
  cout << "| 3. Menu Items Management                               |\n"; // Create new menu items, edit and delete existing menu items
  cout << "| 4. Promotions and Discounts                            |\n";
  cout << "| 5. Employee Management                                 |\n";
  cout << "| 6. Reporting and Analytics                             |\n"; // For displaying balance sheet and transaction history
  cout << "| 7. Quit                                                |\n";
  cout << "==========================================================\n";
}

void displayBakerMenu(){
  cout << "==========================================================\n";
cout << "||                                                         ||\n";
cout << "||                        Baker Menu                       ||\n";
cout << "||                                                         ||\n";
cout << "=============================================================\n";
cout << "| 1. Check Bakery Item                                      |\n"; // View today's menu items and details
cout << "| 2. Inventory Management                                   |\n"; // Display inventory list and details
cout << "| 3. Cookies and Cakes Management                           |\n"; // For adding today's cookies and cakes
cout << "| 4. Quit                                                   |\n";
cout << "=============================================================\n";
}

void displayCashierMenu(){
  cout << "==========================================================\n";
  cout << "||                                                      ||\n";
  cout << "||                    Cashier Menu                      ||\n";
  cout << "||                                                      ||\n";
  cout << "==========================================================\n";
  cout << "| 1. Check Bakery Item                                   |\n"; // View today's menu items and details
  cout << "| 2. Process Order                                       |\n"; // For processing customer orders
  cout << "| 3 . Quit                                               |\n";
  cout << "==========================================================\n";
}

void processSupervisorChoice(Employee* employee, int employeeID){
  char supervisorChoice;
  bool quit = false;
  do {
    displaySupervisorMenu();
    do {
      cout << "Enter your choice: ";
      cin >> supervisorChoice;
      if (supervisorChoice < '1' || supervisorChoice > '7') {
        cout << "Invalid choice. Please try again." << endl;
      }
    } while (supervisorChoice < '1' || supervisorChoice > '7');

    switch (supervisorChoice) {
      case '1':
        checkBakeryItem(employee, employeeID);
        break;
      case '2':
        // Inventory Management
        InventoryManagement(employee, employeeID);
        break;
      case '3':
        // Menu Items Management
        // MenuItemsManagement(employee, employeeID);
        break;
      case '4':
        // Promotions and Discounts
        break;
      case '5':
        // Employee Management
        break;
      case '6':
        // Reporting and Analytics
        break;
      case '7':
        // Quit
        quit = true;
        break;
    }
    if (quit != true) {
      displaySupervisorMenu();
      cout << "Do you want to continue? (Y/N): ";
      cin >> supervisorChoice;
    }
  } while (quit != true && (supervisorChoice == 'Y' || supervisorChoice == 'y'));
}

void processBakerChoice(){
  char bakerChoice;
  do {
    do {
      cout << "Enter your choice: ";
      cin >> bakerChoice;
      if (bakerChoice < '1' || bakerChoice > '4') {
        cout << "Invalid choice. Please try again." << endl;
      }
    } while (bakerChoice < '1' || bakerChoice > '4');

    switch (bakerChoice) {
      case '1':
        // Check Bakery Item
        break;
      case '2':
        // Inventory Management
        break;
      case '3':
        // Cookies and Cakes Management
        break;
      case '4':
        // Quit
        break;
    }
  } while (bakerChoice != '4');
}

void processCashierChoice(){
  char cashierChoice;
  do {
    do {
      cout << "Enter your choice: ";
      cin >> cashierChoice;
      if (cashierChoice < '1' || cashierChoice > '4') {
        cout << "Invalid choice. Please try again." << endl;
      }
    } while (cashierChoice < '1' || cashierChoice > '4');

    switch (cashierChoice) {
      case '1':
        // Check Bakery Item
        break;
      case '2':
        // Process Order
        break;
      case '3':
        // Quit 
        break;
    }
  } while (cashierChoice != '3');
}

void checkBakeryItem(Employee* employees, int employeeID) {
  char index;
  char cont;
  bool exit = false;
    // Show bakery item list
    employees[employeeID].accessMenuList();
    cout << endl;

  do {

    // Input validation for cont
    do {
      cout << "Do you want to view the details of a bakery item? (Y/N): ";
      cin >> cont;
      if (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n') {
        cout << "Invalid choice. Please try again." << endl;
      }
    } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

    if (cont == 'N' || cont == 'n') {
      break;
    } else {
      // Ask for the index of the bakery item to view details
      do{
        cout << "Enter the index of the bakery item to view details: ";
        cin >> index;
        cout << endl;

        // Got Bug here
        employees[employeeID].accessMenuItem(charToInt(index) - 1);
        cout << endl;
      }while(index < '1' || index > '9');
    }

    //Show Menu again for user to choose another bakery item to view
    cout << "Do you want to view the details of another bakery item? (Y/N):";
    cin >> cont;
    if (cont != 'Y' && cont != 'y'){
      break;
    } else{
      employees[employeeID].accessMenuList();
      cout << endl;
    }
  }while(cont == 'Y' || cont == 'y');
}

void InventoryManagement(Employee* employees, int employeeID){
  char inventoryMenuChoice; // Menu Option
  int index; // IngredientInventory Option
  double quantity; // For restocking
  double newCost; // For editing cost
  char cont;
  bool exit = false;

  //Input Validation
  do{
    cout << "==========================================================\n";
    cout << "||                Inventory Management                  ||\n";
    cout << "==========================================================\n";
    cout << "1. Display Ingredient Inventory                          |" << endl;
    cout << "2. Check Ingredient Inventory                            |" << endl;
    cout << "3. Restock Ingredient Inventory                          |" << endl;
    cout << "4. Edit Ingredient Inventory (Cost)                      |" << endl;
    cout << "5. Exit                                                  |" << endl;
    cout << "==========================================================\n";
    do{
      cout << "Enter your choice: ";
      cin >> inventoryMenuChoice;
      if (inventoryMenuChoice < '1' || inventoryMenuChoice > '5'){
        cout << "Invalid choice. Please try again." << endl;
      }
    }while(inventoryMenuChoice < '1' || inventoryMenuChoice > '5');

    switch(inventoryMenuChoice){
      case '1':
        // Display Ingredient Inventory
        employees[employeeID].displayIngredientInventoryList();
        cout << endl;
        do{
          // Show ingredient details
          cout << "Do you want to view the details of an ingredient? (Y/N): ";
          cin >> cont;
          if (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n') {
            cout << "Invalid choice. Please try again." << endl;
          }
        }while(cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

        cout << "Enter the index of the ingredient to view details: ";
        cin >> index;
        cout << endl;
        employees[employeeID].accessIngredientInventoryDetails(index - 1);
        break;
      case '2':
        // Check Ingredient Inventory (Dispolay if the ingredient 0)
        employees[employeeID].checkIngredientInventory();
        break;
      case '3':
        // Restock Ingredient Inventory
        // Show ingredient details
        employees[employeeID].displayIngredientInventoryList();

        // Ask for the ingredient to restock
        cout << "Enter the index of the ingredient to restock: ";
        cin >> index;
        cout << "Enter the quantity to restock: ";
        cin >> quantity;
        cout << endl;
        employees[employeeID].restockIngredientInventory(index-1, quantity);
        break;
      case '4':
        // Edit Ingredient Inventory (Cost)
        // Show ingredient details
        employees[employeeID].displayIngredientInventoryList();

        // Ask for the ingredient to edit cost
        cout << "Enter the index of the ingredient to edit cost: ";
        cin >> index;
        cout << "Enter the new cost: ";
        cin >> newCost;
        cout << endl;
        employees[employeeID].changeIngredientCost(index-1, newCost);
        break;
      case '5':
        // Exit
        exit = true;
        break;
    }
  
    if (exit != true){
      cout << "Do you want to continue? (Y/N): ";
      cin >> inventoryMenuChoice;
    }
  }while(exit != true && (inventoryMenuChoice == 'Y' || inventoryMenuChoice == 'y'));
}

// void MenuItemManagement(Employee* employees, int employeeID){
//   char menuItemChoice;
//   bool exit = false;
//   do{
//     cout << "==========================================================\n";
//     cout << "||                Menu Items Management                  ||\n";
//     cout << "==========================================================\n";
//     cout << "1. Add New Bakery Item                                    |" << endl;
//     cout << "2. Update Bakery Item Price                               |" << endl;
//     cout << "3. Enable Bakery Item                                     |" << endl;
//     cout << "4. Disable Bakery Item                                    |" << endl;
//     cout << "5. Exit                                                   |" << endl;
//     cout << "==========================================================\n";
//     do{
//       cout << "Enter your choice: ";
//       cin >> menuItemChoice;
//       if (menuItemChoice < '1' || menuItemChoice > '4'){
//         cout << "Invalid choice. Please try again." << endl;
//       }
//     }while(menuItemChoice < '1' || menuItemChoice > '4');

//     switch(menuItemChoice){
//       case '1':
//         // Add New Menu Item
//         employees[employeeID].createBakeryItem();
//         break;
//       case '2':
//         // Update Menu Item Price
//         employees[employeeID].changeBakeryItemPrice();
//         break;
//       case '3':
//         // Enable Menu Item
//         employees[employeeID].enableBakeryItem();
//         break;
//       case '4':
//         // Disable Menu Item
//         employees[employeeID].disableBakeryItem();
//         break;
//       case '5':
//         // Exit
//         exit = true;
//         break;
//     }
//     if (exit != true){
//       cout << "Do you want to continue? (Y/N): ";
//       cin >> menuItemChoice;
//     }
//   }while(exit != true && (menuItemChoice == 'Y' || menuItemChoice == 'y'));
// }