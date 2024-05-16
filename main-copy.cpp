// run this file by typing the following command in the terminal
// g++ Baker.cpp BakeryItem.cpp Cake.cpp Cart.cpp Cashier.cpp Discount.cpp Employee.cpp Ingredient.cpp IngredientInventory.cpp Supervisor.cpp main-copy.cpp -o main-copy.exe && main-copy
// g++ Baker.cpp BakeryItem.cpp Cake.cpp Cart.cpp Cashier.cpp Discount.cpp Employee.cpp Ingredient.cpp IngredientInventory.cpp Supervisor.cpp main-copy.cpp -o main-copy.exe && ./main-copy

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
void processBakerChoice(Employee* employee, int employeeID);
void processCashierChoice(Employee* employee, int employeeID);

// For Supervisor
void checkBakeryItem(Employee* employees, int employeeID);
void InventoryManagement(Employee* employees, int employeeID);
void BakeryItemManagement(Employee* employees, int employeeID);
void DiscountAndPromotion(Employee*, int);
void EmployeeManagement(Employee*, int);
void ReportingAndAnalytics(Employee*, int);

// For Baker
void BakeCookieCake(Employee* employees, int employeeID);

// For cashier
void processOrder(Employee* employees, int employeeID);


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
  cout << "====================================================================================================\n";
  cout << "Bakery Item: " << item->name << endl;
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
  // cout << "Recipe: " << item->recipe << endl;
  cout << "Status: ";
  if (item->disabled) {
    cout << "Sold out." << endl;
  } else {
    cout << "Available." << endl;
  }
  cout << "====================================================================================================\n";
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
  cout << " Employee list:                       \n";
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

// Need to do login and logout option
// When user logout caan let user choose whether close or login with another role
string mainPage(){
  string loginInput;
  string currentDate = convertTimeTOYYYY_MM__DD();
  cout << "      ______                  .  .  .  .  .  .            \n";
  cout << "    /       \\               __|__|__|__|__|__|__         \n";
  cout << "    |  o o   |             |~~~~~~~~~~~~~~~~~~~~|         \n";
  cout << "    | o  o o |             |     Happy Eid!     |         \n";
  cout << "    | o o o  |             |____________________|         \n";
  cout << "    \\______ /                                            \n";
  cout << "==========================================================\n";
  cout << "||                                                      ||\n";
  cout << "||                   Eid Delights Bakery                ||\n";
  cout << "||                                                      ||\n";
  cout << "==========================================================\n";
  cout << "  Today's Date: " << currentDate << endl;
  cout << "  Please any key to login and continue (0 to Exit): ";
  getline(cin, loginInput);
  cout << endl;

  return loginInput;
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

  int employeeID;
  string start = mainPage();

  // If user input 0, exit the program
  if (start == "0") {
    cout << "Thank you for using Eid Delights Bakery!" << endl;
    employees[employeeID].closeBakery(DATE_YYYYMMDD);
    return 0;
  }

  // Done: login
  cout << "Welcome to Eid Delights Bakery!" << endl;
  employeeID = login(employees); // Employee Index
  employees[employeeID].startBakery(DATE_YYYYMMDD);

  // employees[1].bakeNewBakeryItem(2,2);
  // employees[2].addBakeryItemToCart(2,2);
  // employees[2].displayCartDetails();
  // employees[4].displayCartDetails();
  // employees[2].moveCartFromThisCashierToAnotherCashier(employees+4);
  // employees[2].displayCartDetails();
  // employees[4].displayCartDetails();

  string role = employees[employeeID].getRole();

  if (role == "Supervisor"){
    processSupervisorChoice(employees, employeeID);
  }
  else if (role == "Baker"){
    processBakerChoice(employees, employeeID);
  }
  else if (role == "Cashier"){
    processCashierChoice(employees, employeeID);
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
  cout << "| 7. Log Out                                             |\n";
  cout << "==========================================================\n";
}

void displayBakerMenu(){
cout << "=============================================================\n";
cout << "||                                                         ||\n";
cout << "||                        Baker Menu                       ||\n";
cout << "||                                                         ||\n";
cout << "=============================================================\n";
cout << "| 1. Check Bakery Item                                      |\n"; // View today's menu items and details
cout << "| 2. Inventory Management                                   |\n"; // Display inventory list and details
cout << "| 3. Cookies and Cakes Management                           |\n"; // For baking today's cookies and cakes
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
  cout << "| 3. Quit                                                |\n";
  cout << "==========================================================\n";
}

void processSupervisorChoice(Employee* employees, int employeeID){
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
        checkBakeryItem(employees, employeeID);
        break;
      case '2':
        // Inventory Management
        InventoryManagement(employees, employeeID);
        break;
      case '3':
        // Menu Items Management
        BakeryItemManagement(employees, employeeID);
        break;
      case '4':
        // Promotions and Discounts
        DiscountAndPromotion(employees, employeeID);
        break;
      case '5':
        // Employee Management
        EmployeeManagement(employees, employeeID);
        break;
      case '6':
        // Reporting and Analytics
        ReportingAndAnalytics(employees, employeeID);
        break;
      case '7':
        // LogOut
        quit = true; // Need to do log out here
        mainPage();
        break;
    }
  } while (quit != true);
}

void processBakerChoice(Employee* employees, int employeeID){
  char bakerChoice;
  do {
    displayBakerMenu();
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
        checkBakeryItem(employees, employeeID);
        break;
      case '2':
        // Inventory Management
        InventoryManagement(employees, employeeID);
        break;
      case '3':
        // Cookies and Cakes Management
        BakeCookieCake(employees, employeeID);
        break;
      case '4':
        // Quit
        mainPage();
        break;
    }
  } while (bakerChoice != '4');
}

void processCashierChoice(Employee* employees, int employeeID){
  char cashierChoice;
  do {
    displayCashierMenu();
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
        checkBakeryItem(employees, employeeID);
        break;
      case '2':
        // Process Order
        processOrder(employees, employeeID);
        break;
      case '3':
        // Quit 
        break;
    }
  } while (cashierChoice != '3');
}

void checkBakeryItem(Employee* employees, int employeeID) {
  int index;
  char cont;
  bool exit = false;
    // Show bakery item list
    cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
    cout << "|              Check Bakery Item                   |\n";
    cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
    employees[employeeID].accessMenuList();
    cout << endl;

    if (cont == 'N' || cont == 'n') {
      processSupervisorChoice(employees, employeeID); // Back to display Menu
    } else {
      // Ask for the index of the bakery item to view details
        do{
          cout << "Enter the choice of the bakery item to view details: ";
          cin >> index; // Input Validation (Needed)
          cout << endl;
          employees[employeeID].accessMenuItem(index - 1);

          cout << endl;
          cout << "Do you want to view the details of another bakery item? (Y/N):";
          cin >> cont;
          if (cont != 'Y' && cont != 'y'){
            break;
          } else {
            employees[employeeID].accessMenuList();
            cout << endl;
          }
        } while(cont == 'Y' || cont == 'y');
    }
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
    cout << "| 1. Display Ingredient Inventory                        |" << endl;
    cout << "| 2. Check Ingredient Inventory                          |" << endl;
    cout << "| 3. Restock Ingredient Inventory                        |" << endl;
    cout << "| 4. Edit Ingredient Inventory (Cost)                    |" << endl;
    cout << "| 5. Exit                                                |" << endl;
    cout << "==========================================================\n";
    do{
      cout << "Enter your choice: ";
      cin >> inventoryMenuChoice;
      if (inventoryMenuChoice < '1' || inventoryMenuChoice > '5'){
        cout << "Invalid choice. Please try again." << endl;
      }
    }while(inventoryMenuChoice < '1' || inventoryMenuChoice > '5');

    switch(inventoryMenuChoice){
      //Done
      case '1':
        // Display Ingredient Inventory
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|           Display Ingredient Inventory           |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        employees[employeeID].displayIngredientInventoryList();
        cout << endl;

        // Break if user does not want to view ingredient details
        if (cont == 'N' || cont == 'n') {
          break; // Back to Inventory Management Menu
        } else {
            do{
              cout << "Enter the choice of the ingredient to view details: ";
              cin >> index; // Input Validation (Needed)
              cout << endl;
              employees[employeeID].accessIngredientInventoryDetails(index - 1);

              cout << endl;
              cout << "Do you want to view the details of other ingredient? (Y/N):";
              cin >> cont;
              if (cont != 'Y' && cont != 'y'){
                break;
              } else {
                employees[employeeID].displayIngredientInventoryList();
                cout << endl;
              }
            } while(cont == 'Y' || cont == 'y');
        }
        break;

      // Done
      case '2':
        // Check Ingredient Inventory (Dispolay if the ingredient 0)
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|           Check Ingredient Inventory             |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        employees[employeeID].checkIngredientInventory();
        break;

      // Done
      case '3':
        // Restock Ingredient Inventory
        // Show ingredient details
        employees[employeeID].displayIngredientInventoryList();

        // Ask for the ingredient to restock
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|            Restock Ingredient Inventory          |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

        // Do while loop for user multiple restock
        do{
          cout << "Enter the choice of the ingredient to restock: ";
          cin >> index;
          cout << "Enter the quantity to restock: ";
          cin >> quantity;
          cout << endl;
          employees[employeeID].restockIngredientInventory(index-1, quantity);
          cout << "Restock successful!" << endl;

          cout << endl;
          cout << "Do you want to restock another ingredient? (Y/N): ";
          cin >> cont;
          if (cont != 'Y' && cont != 'y'){
            break;
          }
        }while(cont == 'Y' || cont == 'y');
        break;

      // Done
      case '4':
        // Edit Ingredient Inventory (Cost)
        // Show ingredient details
        employees[employeeID].displayIngredientInventoryList();

        // Ask for the ingredient to edit cost
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|           Edit Ingredient Inventory (Cost)       |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

        // Do while loop for user multiple edit cost
        do{
          cout << "Enter the choice of the ingredient to edit cost: ";
          cin >> index;
          cout << "Enter the new cost (Per Unit): ";
          cin >> newCost;
          cout << endl;
          employees[employeeID].changeIngredientCost(index-1, newCost);
          cout << "Edit successful!" << endl;

          cout << endl;
          cout << "Do you want to edit another ingredient? (Y/N): ";
          cin >> cont;
          if (cont != 'Y' && cont != 'y'){
            break;
          }
        }while(cont == 'Y' || cont == 'y');
        break;

      case '5':
        // Exit
        exit = true;
        break;
    }
  
    // Continue in Inventory Management Menu or Exit
    if (exit != true){
      cout << "Do you want to continue in Inventory Management Menu? (Y/N): ";
      cin >> inventoryMenuChoice;
    }
  }while(exit != true && (inventoryMenuChoice == 'Y' || inventoryMenuChoice == 'y'));
}

void BakeryItemManagement(Employee* employees, int employeeID){
  char cont;
  int index;
  double newPrice;
  char BakeryItemChoice;
  bool exit = false;
  do{
    cout << "==========================================================\n";
    cout << "||                Bakery Items Management               ||\n";
    cout << "==========================================================\n";
    cout << "| 1. Add New Bakery Item                                 |" << endl;
    cout << "| 2. Update Bakery Item Price                            |" << endl;
    cout << "| 3. Enable Bakery Item                                  |" << endl;
    cout << "| 4. Disable Bakery Item                                 |" << endl;
    cout << "| 5. Exit                                                |" << endl;
    cout << "==========================================================\n";
    do{ // Input Validation
      cout << "Enter your choice: ";
      cin >> BakeryItemChoice;
      if (BakeryItemChoice < '1' || BakeryItemChoice > '5'){
        cout << "Invalid choice. Please try again." << endl;
      }
    }while(BakeryItemChoice < '1' || BakeryItemChoice > '5');

    switch(BakeryItemChoice){
      case '1':
        // Add New Bakery Item
        employees[employeeID].accessMenuList();
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|                Add New Bakery Item               |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

        // Do while loop for user multiple create bakery item
        do{
          employees[employeeID].createBakeryItem();
          cout << "Add successful!" << endl;

          cout << endl;
          cout << "Do you want to add another bakery item? (Y/N): ";
          cin >> cont;
          if (cont != 'Y' && cont != 'y'){
            break;
          } else {
            employees[employeeID].accessMenuList();
            cout << endl;
          }
        }while(cont == 'Y' || cont == 'y');
        break;

      case '2':
        // Update Bakery Item Price
        employees[employeeID].accessMenuList();
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|            Update Bakery Item Price              |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        //Do while loop for user multiple update price
        // Ask User to choose the bakery item to update price
        do{
          cout << "Enter the choice of the bakery item to update price: ";
          cin >> index;
          cout << "Enter the new price:";
          cin >> newPrice;
          employees[employeeID].changeBakeryItemPrice(index - 1, newPrice);
          cout << "Update successful!" << endl;

          cout << endl;
          cout << "Do you want to update the price of another bakery item? (Y/N): ";
          cin >> cont;
          if (cont != 'Y' && cont != 'y'){
            break;
          } else {
            employees[employeeID].accessMenuList();
            cout << endl;
          }
        }while(cont == 'Y' || cont == 'y');
        break;

      case '3':
        // Enable Bakery Item
        employees[employeeID].accessMenuList();
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|               Enable Bakery Item                 |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        //Do while loop for user multiple enable bakery item
        // Ask User to choose the bakery item to enable
        do{
          cout << "Enter the choice of the bakery item to enable: ";
          cin >> index;
          employees[employeeID].enableBakeryItem(index - 1);
          cout << "Enable successful!" << endl;

          cout << endl;
          cout << "Do you want to enable another bakery item? (Y/N): ";
          cin >> cont;
          if (cont != 'Y' && cont != 'y'){
            break;
          } else {
            employees[employeeID].accessMenuList();
            cout << endl;
          }
        }while(cont == 'Y' || cont == 'y');
        break;
      
      case '4':
        // Disable Bakery Item
        employees[employeeID].accessMenuList();
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|               Disable Bakery Item                |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        //Do while loop for user multiple disable bakery item
        // Ask User to choose the bakery item to disable
        do{
          cout << "Enter the choice of the bakery item to disable: ";
          cin >> index;
          employees[employeeID].withdrawBakeryItem(index - 1);
          cout << "Disable successful!" << endl;

          cout << endl;
          cout << "Do you want to disable another bakery item? (Y/N): ";
          cin >> cont;
          if (cont != 'Y' && cont != 'y'){
            break;
          } else {
            employees[employeeID].accessMenuList();
            cout << endl;
          }
        }while(cont == 'Y' || cont == 'y');
        break;

      case '5':
        // Exit
        exit = true;
        break;
    }
    if (exit != true){
      cout << "Do you want to continue in Bakery Items Management Menu? (Y/N): ";
      cin >> BakeryItemChoice;
    }
  }while(exit != true && (BakeryItemChoice == 'Y' || BakeryItemChoice == 'y'));
}

void DiscountAndPromotion(Employee* employees, int employeeID){

  char cont;
  int index;
  string newName;
  double newMinSpend;
  string newDesc;
  double newDiscountPercentage;
  char discountChoice;
  bool exit = false;
  do{
    cout << "==========================================================\n";
    cout << "||                Promotions and Discounts               ||\n";
    cout << "==========================================================\n";
    cout << "| 1. Add New Discount                                     |" << endl;
    cout << "| 2. Edit Discount (Name, Min.Spend, Descp, etc.)         |" << endl;
    cout << "| 3. Enable Discount                                      |" << endl;
    cout << "| 4. Disable Discount                                     |" << endl;
    cout << "| 5. Delete Discount                                      |" << endl;
    cout << "| 6. Exit                                                 |" << endl;
    cout << "==========================================================\n";
    do{ // Input Validation
      cout << "Enter your choice: ";
      cin >> discountChoice;
      if (discountChoice < '1' || discountChoice > '6'){
        cout << "Invalid choice. Please try again." << endl;
      }
    }while(discountChoice < '1' || discountChoice > '6');

    // Switch case for Discount and Promotion
    switch (discountChoice){
      case '1':
        // Add New Discount
        employees[employeeID].accessDiscountList();
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|                  Add New Discount                |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

        // Do while loop for user multiple create discount
        do{
          employees[employeeID].addNewDiscount();
          // cout << "Add successful!" << endl;

          cout << endl;
          cout << "Do you want to add another discount? (Y/N): ";
          cin >> cont;
          if (cont != 'Y' && cont != 'y'){
            break;
          } else {
            employees[employeeID].accessDiscountList();
            cout << endl;
          }
        }while(cont == 'Y' || cont == 'y');
        break;

      // Bug in Edit Discount
      case '2': // Separate function to edit name, min spend, desc, discountPercentange
        do{
          cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
          cout << "|                   Edit Discount                  |\n";
          cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
          cout << "| 1. Edit Name                                     |" << endl;
          cout << "| 2. Edit Minimum Spend                            |" << endl;
          cout << "| 3. Edit Description                              |" << endl;
          cout << "| 4. Edit Discount Percentage                      |" << endl;
          cout << "| 5. Exit                                          |" << endl;
          cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
          do{
            cout << "Enter your choice: ";
            cin >> discountChoice;
            cout << endl;
            if (discountChoice < '1' || discountChoice > '5'){
              cout << "Invalid choice. Please try again." << endl;
            }
          }while(discountChoice < '1' || discountChoice > '5');

          // Switch case for Edit Discount
          switch(discountChoice){
            case '1':
              // Edit Name
              employees[employeeID].accessDiscountList();
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
              cout << "|                    Edit Name                     |\n";
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
              //Do while loop for user multiple edit name
              // Ask User to choose the discount to edit name
              do{
                cout << "Enter the choice of the discount to edit name: ";
                cin >> index;
                cout << "Enter the new name: ";
                cin.ignore();
                getline(cin, newName);

                employees[employeeID].editDiscountName(index - 1, newName);
                // cout << "Edit the discount name successful!" << endl;

                cout << endl;
                cout << "Do you want to edit another discount name? (Y/N): ";
                cin >> cont;
                if (cont != 'Y' && cont != 'y'){
                  break;
                } else {
                  employees[employeeID].accessDiscountList(); // Bug: New Discount dou=esnt update to object ??
                }
              }while(cont == 'Y' || cont == 'y');
              break;

            case '2':
              // Edit Minimum Spend
              employees[employeeID].accessDiscountList();
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
              cout << "|            Edit Minimum Spend                    |\n";
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
              //Do while loop for user multiple edit min spend
              // Ask User to choose the discount to edit min spend
              do{
                cout << "Enter the choice of the discount to edit min spend: ";
                cin >> index;
                cout << "Enter the new minimum spend: ";
                cin >> newMinSpend;
                employees[employeeID].editDiscountMinimumPurchase(index - 1, newMinSpend);
                // cout << "Edit the discount min spend successful!" << endl;

                cout << endl;
                cout << "Do you want to edit another discount min spend? (Y/N): ";
                cin >> cont;
                if (cont != 'Y' && cont != 'y'){
                  break;
                } else {
                  employees[employeeID].accessDiscountList();
                  cout << endl;
                }
              }while(cont == 'Y' || cont == 'y');
              break;

            case '3':
              // Edit Description
              employees[employeeID].accessDiscountList();
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
              cout << "|            Edit Description                      |\n";
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
              //Do while loop for user multiple edit description
              // Ask User to choose the discount to edit description
              do{
                cout << "Enter the choice of the discount to edit description: ";
                cin >> index;
                cout << "Enter the new description: ";
                cin.ignore();
                getline(cin, newDesc);

                employees[employeeID].editDiscountDescription(index - 1, newDesc);
                // cout << "Edit the discount description successful!" << endl;

                cout << endl;
                cout << "Do you want to edit another discount description? (Y/N): ";
                cin >> cont;
                if (cont != 'Y' && cont != 'y'){
                  break;
                } else {
                  employees[employeeID].accessDiscountList();
                  cout << endl;
                }
              }while(cont == 'Y' || cont == 'y');
              break;

            case '4':
              // Edit Discount Percentage
              employees[employeeID].accessDiscountList();
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\nn";
              cout << "|            Edit Discount Percentage              |\n";
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\nn";
              //Do while loop for user multiple edit discount percentage
              // Ask User to choose the discount to edit discount percentage
              do{
                cout << "Enter the choice of the discount to edit discount percentage: ";
                cin >> index;
                cout << "Enter the new discount percentage: ";
                cin >> newDiscountPercentage;
                employees[employeeID].editDiscountPercentage(index - 1, newDiscountPercentage);
                // cout << "Edit the discount percentage successful!" << endl;

                cout << endl;
                cout << "Do you want to edit another discount percentage? (Y/N): ";
                cin >> cont;
                if (cont != 'Y' && cont != 'y'){
                  break;
                } else {
                  employees[employeeID].accessDiscountList();
                  cout << endl;
                }
              }while(cont == 'Y' || cont == 'y');
              break;  

            case '5':
              // Exit
              exit = true;
              DiscountAndPromotion(employees, employeeID);
          }
            // Ask whether continue edit
            if (exit != true){
              cout << "Do you want to continue in Edit Discount Menu? (Y/N): ";
              cin >> discountChoice;
            }

        }while (exit != true && (discountChoice == 'Y' || discountChoice == 'y'));
        break;

        
      case '3':
        // Enable Discount
        employees[employeeID].accessDiscountList();
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|                   Enable Discount                |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        //Do while loop for user multiple enable discount
        // Ask User to choose the discount to enable
        do{
          cout << "Enter the choice of the discount to enable: ";
          cin >> index;
          employees[employeeID].enableDiscount(index - 1);
          // cout << "Enable successful!" << endl;

          cout << endl;
          cout << "Do you want to enable another discount? (Y/N): ";
          cin >> cont;
          if (cont != 'Y' && cont != 'y'){
            break;
          } else {
            employees[employeeID].accessDiscountList();
            cout << endl;
          }
        }while(cont == 'Y' || cont == 'y');
        break;

      case '4':
        // Disable Discount
        employees[employeeID].accessDiscountList();
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|                  Disable Discount                |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\nn";
        //Do while loop for user multiple disable discount
        // Ask User to choose the discount to disable
        do{
          cout << "Enter the choice of the discount to disable: ";
          cin >> index;
          employees[employeeID].disableDiscount(index - 1);
          // cout << "Disable successful!" << endl;

          cout << endl;
          cout << "Do you want to disable another discount? (Y/N): ";
          cin >> cont;
          if (cont != 'Y' && cont != 'y'){
            break;
          } else {
            employees[employeeID].accessDiscountList();
            cout << endl;
          }
        }while(cont == 'Y' || cont == 'y');
        break;

      case '5':
        // Delete Discount
        employees[employeeID].accessDiscountList();
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|                  Delete Discount                 |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        //Do while loop for user multiple delete discount
        // Ask User to choose the discount to delete
        do{
          cout << "Enter the choice of the discount to delete: ";
          cin >> index;
          employees[employeeID].deleteDiscount(index - 1);
          // cout << "Delete successful!" << endl;

          cout << endl;
          cout << "Do you want to delete another discount? (Y/N): ";
          cin >> cont;
          if (cont != 'Y' && cont != 'y'){
            break;
          } else {
            employees[employeeID].accessDiscountList();
            cout << endl;
          }
        }while(cont == 'Y' || cont == 'y');
        break;

      case '6':
        // Exit
        exit = true;
        break;
    }
    
    if (exit != true){
      cout << "Do you want to continue in Promotions and Discounts Menu? (Y/N): ";
      cin >> discountChoice;
    }
  }  while (exit != true && (discountChoice == 'Y' || discountChoice == 'y'));
}

void EmployeeManagement(Employee* employees, int employeeID){
  char cont;
  string newEmployee;
  string newRole;
  string newEmployeeID;
  string newEmployeePassword;
  int index;
  char employeeMangementChoice;
  bool exit = false;
  // createNewEmployee, changeRole, deleteEmployee
  do{
    cout << "==========================================================\n";
    cout << "||                Employee Management                   ||\n";
    cout << "==========================================================\n";
    cout << "| 1. Display Employee Details                            |" << endl;
    cout << "| 2. Create New Employee                                 |" << endl;
    cout << "| 3. Change Employee Role                                |" << endl;
    cout << "| 4. Delete Employee                                     |" << endl;
    cout << "| 5. Exit                                                |" << endl;
    cout << "==========================================================\n";
    do{
      cout << "Enter your choice: ";
      cin >> employeeMangementChoice;
      if (employeeMangementChoice < '1' || employeeMangementChoice > '5'){
        cout << "Invalid choice. Please try again." << endl;
      }
    }while(employeeMangementChoice < '1' || employeeMangementChoice > '5');
    
    // switch case for Employee Management
    switch(employeeMangementChoice){
      case '1':
        // Display Employee Details
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|           Display Employee Details               |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << endl;
        employees[employeeID].displayAllEmployeeDetails(employees);
        break;

      case '2':
        // Create New Employee
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|                Create New Employee               |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        // Do while loop for user multiple create employee
        do{
          cout << "Enter the new employee name: ";
          cin.ignore();
          getline(cin, newEmployee);

          cout << "Enter the new employee role: ";
          getline(cin, newRole);

          cout << "Enter the new employee ID: ";
          cin >> newEmployeeID;

          cout << "Enter the new employee password: ";
          cin >> newEmployeePassword;

          employees[employeeID].createNewEmployee(employees, newEmployeeID, newEmployee, newRole, newEmployeePassword);
          // cout << "Create successful!" << endl;

          cout << endl;
          cout << "Do you want to create another employee? (Y/N): ";
          cin >> cont;
          if (cont != 'Y' && cont != 'y'){
            cout << "Updated Employee List: " << endl;
            employees[employeeID].displayAllEmployeeDetails(employees);
            break;
          }
        }while(cont == 'Y' || cont == 'y');
        

        break;

      case '3':
        // Change Employee Role
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|           Change Employee Role                   |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        employees[employeeID].displayAllEmployeeDetails(employees);
        // Do while loop for user multiple change employee role
        do{
          cout << "Enter the choice of the employee to change role: ";
          cin >> index;
          cout << "Enter the new role: ";
          cin >> newRole;
          employees[employeeID].changeEmployeeRole(employees, index - 1, newRole);
          // cout << "Change successful!" << endl;
          
          cout << endl;
          cout << "Do you want to change another employee role? (Y/N): ";
          cin >> cont;
          if (cont != 'Y' && cont != 'y'){
            break;
          } else {
            cout << endl;
          }
        }while(cont == 'Y' || cont == 'y');
        break;

      case '4':
        // Delete Employee
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|                 Delete Employee                  |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        employees[employeeID].displayAllEmployeeDetails(employees);
        // Do while loop for user multiple delete employee
        do{
          cout << "Enter the choice of the employee to delete: ";
          cin >> index;
          employees[employeeID].deleteEmployee(employees, index - 1);
          // cout << "Delete successful!" << endl;

          cout << endl;
          cout << "Do you want to delete another employee? (Y/N): ";
          cin >> cont;
          if (cont != 'Y' && cont != 'y'){
            break;
          } else {
            cout << endl;
          }
        }while(cont == 'Y' || cont == 'y');
        break;

      case '5':
        // Exit
        exit = true;
        break;
      }
    
    if (exit != true){
      cout << "Do you want to continue in Employee Management Menu? (Y/N): ";
      cin >> employeeMangementChoice;
    }
  }while(exit != true && (employeeMangementChoice == 'Y' || employeeMangementChoice == 'y'));
}

void ReportingAndAnalytics(Employee* employees, int employeeID){
  char reportingChoice;
  string date;
  bool exit = false;
  //Show Total Profit per day, Show total credit and total debit, show total balance
  do{  
    cout << "==========================================================\n";
    cout << "||                 Reporting and Analytics              ||\n";
    cout << "==========================================================\n";
    cout << "| 1. Display Current Financial Summary                   |" << endl;
    cout << "| 2. Display Transaction History                         |" << endl;
    cout << "| 3. Display Balance Sheet                               |" << endl;
    cout << "| 4. Exit                                                |" << endl;
    cout << "==========================================================\n";
    do{
      cout << "Enter your choice: ";
      cin >> reportingChoice;
      if (reportingChoice < '1' || reportingChoice > '4'){
        cout << "Invalid choice. Please try again." << endl;
      }
    }while(reportingChoice < '1' || reportingChoice > '4');

    // Switch case for Reporting and Analytics
    switch(reportingChoice){
      case '1':
        // Display Current Financial Summary
        cout << "************Current Financial Summary************\n";
        employees[employeeID].showTotalDebit();
        employees[employeeID].showTotalCredit();
        employees[employeeID].showTotalBalance();
        employees[employeeID].showTotalProfitPerDay();
        cout << "*************************************************\n";
        break;

      case '2':
        // Display Transaction History
        // Do while loop for user multiple access transaction history
        do {
          do { // Input Validation for YYYYMMDD
            cout << "Enter the date to access transaction history (YYYYMMDD): ";
            cin >> date;
            if (date.length() != 8) {
              cout << "Invalid date. Please try again." << endl;
            }
          } while (date.length() != 8);

          employees[employeeID].accessTransactionHistory(date);

          cout << "Do you want to access another transaction history? (Y/N): ";
          cin >> reportingChoice;
          if (reportingChoice != 'Y' && reportingChoice != 'y') {
            break;
          }
        } while (reportingChoice == 'Y' || reportingChoice == 'y');
        break;

      case '3':
        // Display Balance Sheet
        employees[employeeID].displayBalanceSheet();
        break;

      case '4':
        // Exit
        exit = true;
        break;
    }
    if (exit != true){
      cout << endl;
      cout << "Do you want to continue in Reporting and Analytics Menu? (Y/N): ";
      cin >> reportingChoice;
    }
  }while (exit != true && (reportingChoice == 'Y' || reportingChoice == 'y'));
}

void BakeCookieCake(Employee* employees, int employeeID){
  int index, quantity;
  char cont;
  cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
  cout << "|           Cookies and Cakes Management           |\n";
  cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
  employees[employeeID].accessMenuList();

  // Do while loop for user multiple create bakery item
  do{
    cout << "Enter the choice for the baking item: ";
    cin >> index;

    cin.ignore();
    cout << "Enter the quantity to bake: "; // Bug: Will show negative (constructor ?)
    cin >> quantity;
    employees[employeeID].bakeNewBakeryItem(index - 1, quantity);

    cout << endl;
    cout << "Do you want to add another baking item? (Y/N): ";
    cin >> cont;
    if (cont != 'Y' && cont != 'y'){
      break;
    } else {
      cout << endl;
    }
  }while(cont == 'Y' || cont == 'y');
}

void processOrder(Employee* employees, int employeeID){
  bool exit = false;
  char cashierChoice;
  int quantity;
  double weight;
  char cont;
  int index;

  do {
    cout << "==========================================================\n";
    cout << "||                 Cashier Order Processing             ||\n";
    cout << "==========================================================\n";
    cout << "| 1. Add Cakes/ Cookies                                  |\n";
    cout << "| 2. Add Cakes by Weight                                 |\n";
    cout << "| 3. Edit item                                           |\n";
    cout << "| 4. Display Cart                                        |\n";
    cout << "| 5. Checkout                                            |\n";
    cout << "| 6. Show receipt                                        |\n";
    cout << "| 7. Exit                                                |\n";
    cout << "==========================================================\n";

    do {
        cout << "Enter your choice: ";
        cin >> cashierChoice;
        if (cashierChoice < '1' || cashierChoice > '5'){
            cout << "Invalid choice. Please try again." << endl;
        }
    } while(cashierChoice < '1' || cashierChoice > '5');

    bool addMoreItems = true;
    // Switch case for Cashier Order Processing
    switch(cashierChoice){
      case '1':
      employees[1].bakeNewBakeryItem(2, 2); // Check
      char itemType;
      while(addMoreItems){
        employees[employeeID].accessMenuList();
        do {
          cout << "Enter item type (c for cookie, k for cake): ";
          cin >> itemType;
          if (itemType == 'c') {
            cout << "Enter the choice of the cookie: ";
            cin >> index;

            cout << "Enter the quantity of cookies:";
            cin >> quantity;
            cout << endl;

            employees[employeeID].addBakeryItemToCart(index - 1, quantity);
            break; // Exit the loop

          } else if (itemType == 'k') {
              cout << "Enter the choice of the cake: ";
              cin >> index;

              cout << "Enter the quantity of cake: ";
              cin >> quantity;

              employees[employeeID].addBakeryItemToCart(index - 1, quantity);
              break; // Exit the loop

            } else {
              cout << "Invalid item type. Please try again." << endl;
            }
        } while (true); // Loop until valid item type is entered

        cout << "Do you want to add more items? (Y/N): ";
        cin >> cont;
        if (cont != 'Y' && cont != 'y') {
          char display;
          addMoreItems = false;
          cout << "Do you want to display cart details: " << endl;
          cin >> display;
          if (display == 'Y' || display == 'y') {
            employees[employeeID].displayCartDetails();
          }
          break;
        }
      }
      break;

      case '2':
        // Add Cake by Weight
        employees[employeeID].accessMenuList();
        do {
          cout << "Enter the choice of the cake: ";
          cin >> index;

          cout << "Enter the weight of the cake: ";
          cin >> weight;

          employees[employeeID].addBakeryItemToCart(index - 1, weight);
          cout << "Add successful!" << endl;

          cout << "Do you want to add more cakes by weight? (Y/N): ";
          cin >> cont;

          if (cont != 'Y' && cont != 'y') {
            char display;
            addMoreItems = false;
            cout << "Do you want to display cart details: " << endl;
            cin >> display;
            if (display == 'Y' || display == 'y') {
              employees[employeeID].displayCartDetails();
              break;
            }
          }
        } while (cont == 'Y' || cont == 'y');
        break;

      case '3':
        // Edit Item
        // Ask whether delete or edit
        char editOrDelete;
        char cont;
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|                   Edit Item                      |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "| 1. Edit Item                                     |\n";
        cout << "| 2. Delete Item                                   |\n";
        cout << "| 3. Exit                                          |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        do {
          cout << "Enter your choice: ";
          cin >> editOrDelete;
          if (editOrDelete < '1' || editOrDelete > '3') {
            cout << "Invalid choice. Please try again." << endl;
          }
        } while (editOrDelete < '1' || editOrDelete > '3');

        switch(editOrDelete){
          case '1':
            // Edit Item
            // Do while loop for user multiple edit item
            do {
              employees[employeeID].displayCartDetails();
              cout << "Enter the choice of the item to update: ";
              cin >> index;
              cout << "Enter the new quantity: ";
              cin >> quantity;
              employees[employeeID].updateBakeryItemQuantityInCart(index - 1, quantity);

              cout << "Do you want to edit another item? (Y/N): ";
              cin >> cont;
              if (cont != 'Y' && cont != 'y') {
                break;
              }
            } while (cont == 'Y' || cont == 'y');

            break;

          case '2':
            // Delete Item
            // Do while loop for user multiple delete item
            do {
              employees[employeeID].displayCartDetails();
              cout << "Enter the choice of the item to delete: ";
              cin >> index;
              employees[employeeID].removeBakeryItemFromCart(index - 1);

              cout << "Do you want to delete another item? (Y/N): ";
              cin >> cont;
              if (cont != 'Y' && cont != 'y') {
                break;
              }
            } while (cont == 'Y' || cont == 'y');
            break;

          case '3':
            // Exit
            exit = true;
            break;
        }

      case '4':
        // Display Cart
        employees[employeeID].displayCartDetails();
        break;

      case '5':
        // Checkout
        employees[employeeID].checkout(convertTimeToYYYYMMDD());
        break;

      case '6':
        // Show Receipt
        employees[employeeID].showReceipt(convertTimeToYYYYMMDD(), employees[employeeID].getOrderNo());
        break;

      case '7':
        // Exit
        exit = true;
        break;
      }

      if (exit != true) {
        cout << "Do you want to continue in Cashier Order Processing Menu? (Y/N): ";
        cin >> cashierChoice;
      }

  } while (exit != true && (cashierChoice == 'Y' || cashierChoice == 'y'));
}