// run this file by typing the following command in the terminal
// g++ *.cpp -o main.exe && main
// g++ *.cpp -o main.exe && ./main

#include <iostream> // for input/output
#include <iomanip> // for input/output manipulation
#include <string> // for string
#include <cmath> // for math functions
#include <ctime> // for time functions
#include <cstdlib> // for random number generation
#include <fstream> // for file input/output
using namespace std;

// forward declaration
class Employee;

// class declaration
#include "Constant.h" // Implementation file for the Constant namespace.
#include "Discount.h" // Implementation file for the Discount class.
#include "Ingredient.h" // Implementation file for the Ingredient class.
#include "Cake.h" // Implementation file for the Cake class.
#include "BakeryItem.h" // Implementation file for the BakeryItem class.
#include "IngredientInventory.h" // Implementation file for the IngredientInventory class.
#include "Cart.h" // Implementation file for the Cart class.
#include "Supervisor.h" // Implementation file for the Supervisor class.
#include "Baker.h" // Implementation file for the Baker class.
#include "Cashier.h" // Implementation file for the Cashier class.
#include "Employee.h" // Implementation file for the Employee class.

// global constant
const int MAX_EMPLOYEES = Constant::MAX_EMPLOYEES; // Maximum number of employees

// Function Prototype
// For all role
void displaySupervisorMenu(); // Display Supervisor Menu
void displayBakerMenu(); // Display Baker Menu
void displayCashierMenu(); // Display Cashier Menu
void processSupervisorChoice(Employee*, int, int); // Process Supervisor Choice
void processBakerChoice(Employee*, int); // Process Baker Choice
void processCashierChoice(Employee*, int, int); // Process Cashier Choice

// For Supervisor
void checkBakeryItem(Employee* , int); // Check Bakery Item
void InventoryManagement(Employee* , int); // Inventory Management
void BakeryItemManagement(Employee* , int); // Bakery Items Management
void DiscountAndPromotion(Employee*, int); // Promotions and Discounts
void EmployeeManagement(Employee*, int, int); // Employee Management
void ReportingAndAnalytics(Employee*, int); // Reporting and Analytics

// For Baker
void BakeCookieCake(Employee* , int); // Bake New Cookies and Cakes

// For cashier
void processOrder(Employee* , int, int); // Process Order
void checkout(Employee* , int); // Checkout

string convertTimeToYYYYMMDD() { // Convert time to YYYYMMDD
  // Get current time
  auto currentTime = time(0);
  auto* timeNow = localtime(&currentTime); // Convert to local time

  char buffer[9]; // YYYYMMDD
  strftime(buffer, sizeof(buffer), "%Y%m%d", timeNow); // Format time to YYYYMMDD

  return buffer;
}

string convertTimeTOYYYY_MM__DD() { // Convert time to YYYY-MM-DD
  // Get current time
  auto currentTime = time(0);
  auto* timeNow = localtime(&currentTime);

  char buffer[11]; // YYYY-MM-DD
  strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeNow); // Format time to YYYY-MM-DD

  return buffer;
}

string convertTimeToYYYY__MM__DD_HH_MM_SS() { // Convert time to YYYY-MM-DD HH:MM:SS
  // Get current time
  auto currentTime = time(0);
  auto* timeNow = localtime(&currentTime);

  char buffer[20]; // YYYY-MM-DD HH:MM:SS
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeNow); // Format time to YYYY-MM-DD HH:MM:SS

  return buffer;
}

// Function to display menu details
void accessMenuDetails(const BakeryItem * item) {
  cout << "====================================================================================================\n";
  cout << "Bakery Item: " << item->name << endl; // Display bakery item name
  cout << "Description: " << item->description << endl; // Display bakery item description
  cout << "Quantity: " << item->quantity << " unit(s) available." << endl; // Display bakery item quantity
  cout << "Price: RM " << setprecision(2) << fixed << item->pricePerUnit << endl; // Display bakery item price
  cout << "Ingredients: "; // Display bakery item ingredients
  for (int i = 0; i < item->ingredientCount; i++) {
    // display ingredient details as 200g sugar, 1 egg, 1 cup flour
    if (item->ingredient[i].getCountable()) { // if ingredient is countable
      cout << item->ingredient[i].getPiece() << "x " << item->ingredient[i].getName(); // display ingredient as (e.g. 1x egg)
    } else {
      cout << item->ingredient[i].getWeight() << "g " << item->ingredient[i].getName(); // display ingredient as (e.g. 200g sugar)
    }
    if (i < item->ingredientCount - 1) { // if not the last ingredient
      cout << ", ";
    }
  }
  // cout << endl;
  // cout << "Recipe: " << item->recipe << endl;
  // Display bakery item status (available or not)
  cout << "Status: ";
  if (item->disabled) {
    cout << "Sold out." << endl; 
  } else {
    cout << "Available." << endl;
  }
  cout << endl;

  // show recipe
  char showRecipe; // flag of boolean to show recipe
  do {
    cout << "Do you want to view the recipe? (Y/N): "; // Ask user if they want to view the recipe
    cin >> showRecipe;
  } while (showRecipe != 'Y' && showRecipe != 'N' && showRecipe != 'y' && showRecipe != 'n');  // Input Validation

  if (showRecipe == 'Y' || showRecipe == 'y') { // if user wants to view the recipe
    cout << "====================================================================================================" << endl;
    cout << "Recipe: " << endl;
    
    // if read \n then go to another line
    // if read \t then go to next tab
    if (item->recipe == "") {
      cout << "No recipe available." << endl;
    } else {
      // read char by char
      for (int i = 0; i < item->recipe.length(); i++) {
        if (item->recipe[i] == '\\') {
          if (item->recipe[i+1] == 'n') {
            // if read \n then go to another line
            cout << endl;
          } else if (item->recipe[i+1] == 't') {
            // if read \t then go to next tab
            cout << "\t";
          }
          i++;
        } else {
          cout << item->recipe[i];
        }
      }
    }
  }

  cout << "====================================================================================================\n";
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
  int i;
  for (i = 0; i < MAX_EMPLOYEES; i++) { // Display employee list
    if (employees[i].getName() != "") {
        cout << "| " << setw(3) << left << i+1 << " | " << setw(29) << left << employees[i].getName() << " |\n";
    }
  }
  cout << "---------------------------------------\n";

  int employeeChoice;

  do {
    cout << "Choose employee: ";
    cin >> employeeChoice;
    if (employeeChoice <= 0 || employeeChoice > i || employees[employeeChoice-1].getName() == "") { // Input Validation
      cout << "Invalid choice. Please try again." << endl;
      continue;
    }
    
    string employeeID;
    cout << "Enter employee ID: ";
    cin >> employeeID;

    string password;
    cout << "Enter password: ";
    cin >> password;
    cout << endl;

    if (employees[employeeChoice-1].login(employeeID, password)) { // Check if employee ID and password match
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
      getline(employeeDataFile, employeeID, ','); // read employee ID
      getline(employeeDataFile, name, ','); // read employee name
      getline(employeeDataFile, role, ','); // read employee role
      getline(employeeDataFile, password); // read employee password

      employees[employeeCount].setEmployeeID(employeeID); // set employee ID
      employees[employeeCount].setName(name); // set employee name
      employees[employeeCount].setRole(role); // set employee role
      employees[employeeCount].setPassword(password); // set employee password

      employeeCount++;
    }
  } else {
    cout << "Error: employeeData.csv not found" << endl;
    return 0;
  }
  cout << endl;

  int employeeID;

  // Done: login
  cout << "Welcome to Eid Delights Bakery!" << endl;
  employeeID = login(employees); // Employee Index
  employees[employeeID].startBakery(DATE_YYYYMMDD); // Start bakery

  // employees[1].bakeNewBakeryItem(2,2);
  // employees[2].addBakeryItemToCart(2,2);
  // employees[2].displayCartDetails();
  // employees[4].displayCartDetails();
  // employees[2].moveCartFromThisCashierToAnotherCashier(employees+4);
  // employees[2].displayCartDetails();
  // employees[4].displayCartDetails();

  string role = employees[employeeID].getRole();

  char q;
  do {
    string currentDate = convertTimeTOYYYY_MM__DD();
    cout << "                                                           \n";
    cout << "             ______            .  .  .  .  .  .            \n";
    cout << "           /       \\         __|__|__|__|__|__|__         \n";
    cout << "           |  o o   |       |~~~~~~~~~~~~~~~~~~~~|         \n";
    cout << "           | o  o o |       |     Happy Eid!     |         \n";
    cout << "           | o o o  |       |____________________|         \n";
    cout << "           \\______ /                                      \n";
    cout << "                                                           \n";
    cout << "==========================================================\n";
    cout << "||                                                      ||\n";
    cout << "||                   Eid Delights Bakery                ||\n";
    cout << "||                                                      ||\n";
    cout << "==========================================================\n";
    cout << "  Today's Date: " << currentDate << endl;
    cout << "  Welcome, " << employees[employeeID].getRole() << " " << employees[employeeID].getName() << "!" << endl;
    cout << "==========================================================\n";
    cout << "1 - Continue to Menu\n";
    cout << "2 - Log In to Change Role\n";
    cout << "3 - Quit\n";
    cout << "Enter your choice: ";
    cin >> q;
    cin.ignore();
    cout << endl;
    cout << "==========================================================\n";
    cout << endl;
    if (q == '2') {
      employeeID = login(employees);
      role = employees[employeeID].getRole();
    }
    if (q == '3') {
      cout << "Thank you for using Eid Delights Bakery!" << endl;
      employees[employeeID].closeBakery(DATE_YYYYMMDD);
      break;
    }
    cout << endl;
    if (role == "Supervisor"){
      processSupervisorChoice(employees, employeeID, employeeCount); // Process Supervisor Choice
    }
    else if (role == "Baker"){
      processBakerChoice(employees, employeeID); // Process Baker Choice
    }
    else if (role == "Cashier"){
      processCashierChoice(employees, employeeID, employeeCount); // Process Cashier Choice
    }
  } while (q != '0');

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
  cout << "| 3. Bakery Items Management                               |\n"; // Create new menu items, edit and delete existing menu items
  cout << "| 4. Promotions and Discounts                            |\n";
  cout << "| 5. Employee Management                                 |\n";
  cout << "| 6. Reporting and Analytics                             |\n"; // For displaying balance sheet and transaction history
  cout << "| 7. Back to Main Menu                                   |\n";
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
cout << "| 3. Bake New Cookies and Cakes                             |\n"; // For baking today's cookies and cakes
cout << "| 4. Back to Main Menu                                      |\n";
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
  cout << "| 3. Back to Main Menu                                   |\n";
  cout << "==========================================================\n";
}

void processSupervisorChoice(Employee* employees, int employeeID, int employeeCount){
  char supervisorChoice;
  bool quit = false;
  do {
    displaySupervisorMenu(); // Display Supervisor Menu
    do {
      cout << "Enter your choice: ";
      cin >> supervisorChoice;  
      if (supervisorChoice < '1' || supervisorChoice > '7') { // Input Validation
        cout << "Invalid choice. Please try again." << endl;
      }
    } while (supervisorChoice < '1' || supervisorChoice > '7');

    switch (supervisorChoice) {
      case '1':
        // Check Bakery Item
        checkBakeryItem(employees, employeeID);
        break;
      case '2':
        // Inventory Management
        InventoryManagement(employees, employeeID);
        break;
      case '3':
        // Bakery Items Management
        BakeryItemManagement(employees, employeeID);
        break;
      case '4':
        // Promotions and Discounts
        DiscountAndPromotion(employees, employeeID);
        break;
      case '5':
        // Employee Management
        EmployeeManagement(employees, employeeID, employeeCount);
        break;
      case '6':
        // Reporting and Analytics
        ReportingAndAnalytics(employees, employeeID);
        break;
      case '7':
        // Back to Main Menu
        quit = true; // Need to do log out here
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
      if (bakerChoice < '1' || bakerChoice > '4') { // Input Validation
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
        // Back to Main Menu
        break;
    }
  } while (bakerChoice != '4');
}

void processCashierChoice(Employee* employees, int employeeID, int employeeCount){
  char cashierChoice;
  do {
    displayCashierMenu();
    do {
      cout << "Enter your choice: ";
      cin >> cashierChoice;
      if (cashierChoice < '1' || cashierChoice > '3') { // Input Validation
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
        processOrder(employees, employeeID, employeeCount);
        break;
      case '3':
        // Back to Main Menu
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

    // Ask for the index of the bakery item to view details
    do{
      cout << "Press (0) to exit....\n";
      cout << "Enter the choice of the bakery item to view details: ";
      cin >> index; // Input Validation (Needed)

      while(cin.fail()) {
      cin.clear(); // clear the error state
      cin.ignore(10, '\n'); // ignore the next 10 characters...
      cout << "Invalid input. Please enter a valid choice: ";
      cin >> index;
      }
      
      if (index == 0){ // Allow user to exit
        break;
      }
      cout << endl;
      employees[employeeID].accessMenuItem(index - 1); // Access bakery item details

      cout << endl;
      do {
        cout << "Do you want to view the details of another bakery item? (Y/N):"; // Ask user if they want to view another bakery item
        cin >> cont;
      } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

      if (cont == 'Y' && cont == 'y'){
        employees[employeeID].accessMenuList(); // Show bakery item list
        cout << endl;
      }
      if (cont == 'N' && cont == 'n'){ // Break if user does not want to view another bakery item
        break;
      }

    } while(cont == 'Y' || cont == 'y'); // Continue if user wants to view another bakery item
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
        cout << "Invalid choice. Please try again." << endl; // Input Validation
      }
    }while(inventoryMenuChoice < '1' || inventoryMenuChoice > '5');

    switch(inventoryMenuChoice){
      //Done
      case '1':
        // Display Ingredient Inventory
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|           Display Ingredient Inventory           |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        employees[employeeID].displayIngredientInventoryList(); // Display ingredient inventory list
        cout << endl;

        // Break if user does not want to view ingredient details
        do{
          cout << "Press (0) to exit....\n";
          cout << "Enter the choice of the ingredient to view details: ";
          cin >> index; // Input Validation (Needed)

          while(cin.fail()) {
            cin.clear(); // clear the error state
            cin.ignore(10, '\n'); // ignore the next 10 characters...
            cout << "Invalid input. Please enter a valid choice: ";
            cin >> index;
          }

          if (index == 0){ // Allow user to exit
            break;
          }
          cout << endl; 
          employees[employeeID].accessIngredientInventoryDetails(index - 1); // Access ingredient inventory details

          cout << endl;
          do {
            cout << "Do you want to view the details of other ingredient? (Y/N):"; // Ask user if they want to view another ingredient
            cin >> cont;
          } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n'); // Input Validation

          if (cont != 'Y' && cont != 'y'){
            employees[employeeID].displayIngredientInventoryList(); // Show ingredient inventory list
            cout << endl;
          }

          if (cont == 'N' && cont == 'n'){ // Break if user does not want to view another ingredient
            break;
          }
          
        } while(cont == 'Y' || cont == 'y'); // Continue if user wants to view another ingredient
        
        break;

      // Done
      case '2':
        // Check Ingredient Inventory (Dispolay if the ingredient 0)
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|           Check Ingredient Inventory             |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        employees[employeeID].checkIngredientInventory(); // Check ingredient inventory
        break;

      // Done
      case '3':
        // Restock Ingredient Inventory
        // Show ingredient details
        employees[employeeID].displayIngredientInventoryList(); // Display ingredient inventory list (which is needed to restock)

        // Ask for the ingredient to restock
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|            Restock Ingredient Inventory          |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

        // Do while loop for user multiple restock
        do{
          cout << "Press (0) to exit....\n";
          cout << "Enter the choice of the ingredient to restock: ";
          cin >> index;

          while(cin.fail()) { // Input Validation
            cin.clear(); // clear the error state
            cin.ignore(10, '\n'); // ignore the next 10 characters...
            cout << "Invalid input. Please enter a valid choice: ";
            cin >> index;
          }

          if (index == 0){ // Allow user to exit
            break;
          }

          cout << "Enter the quantity to restock: ";
          cin >> quantity;
          cout << endl;
          employees[employeeID].restockIngredientInventory(index-1, quantity); // Restock ingredient inventory
          cout << "Restock successful!" << endl;

          cout << endl;
          do {
            cout << "Do you want to restock another ingredient? (Y/N): "; // Ask user if they want to restock another ingredient
            cin >> cont;
          } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n'); // Input Validation
          
          if (cont == 'N' && cont == 'n'){ // Break if user does not want to restock another ingredient
            break;
          }
        }while(cont == 'Y' || cont == 'y');  // Continue if user wants to restock another ingredient
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
          cout << "Press (0) to exit....\n";
          cout << "Enter the choice of the ingredient to edit cost: ";
          cin >> index;

          while(cin.fail()) {
            cin.clear(); // clear the error state
            cin.ignore(10, '\n'); // ignore the next 10 characters...
            cout << "Invalid input. Please enter a valid choice: ";
            cin >> index;
          }

          if (index == 0){ // Allow user to exit
            break;
          }

          cout << "Enter the new cost (Per Unit): ";
          cin >> newCost;
          cout << endl;
          employees[employeeID].changeIngredientCost(index-1, newCost); // Change ingredient cost
          cout << "Edit successful!" << endl;

          cout << endl;
          do {
            cout << "Do you want to edit another ingredient? (Y/N): "; // Ask user if they want to edit another ingredient
            cin >> cont;
          } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n'); // Input Validation

          if (cont == 'N' && cont == 'n'){ // Break if user does not want to edit another ingredient
            break;
          }
        }while(cont == 'Y' || cont == 'y'); // Continue if user wants to edit another ingredient
        break;

      case '5':
        // Exit
        exit = true;
        break;
    }
  
    // Continue in Inventory Management Menu or Exit
    if (exit != true){
      cout << "Do you want to continue in Inventory Management Menu?" << endl; // Ask user if they want to continue in Inventory Management Menu
      cout << "Press 'y' or any key to exit: ";
      cin >> inventoryMenuChoice;
    }
  }while(exit != true && (inventoryMenuChoice == 'Y' || inventoryMenuChoice == 'y')); // Continue if user wants to continue in Inventory Management Menu
}

void BakeryItemManagement(Employee* employees, int employeeID){
  char cont; // For user input
  int index; // Bakery Item Index
  double newPrice; // For updating price
  char BakeryItemChoice; // Menu Option
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
      if (BakeryItemChoice < '1' || BakeryItemChoice > '5'){ // Input Validation
        cout << "Invalid choice. Please try again." << endl;
      }
    }while(BakeryItemChoice < '1' || BakeryItemChoice > '5');

    switch(BakeryItemChoice){
      case '1':
        // Add New Bakery Item
        employees[employeeID].accessMenuList(); // Show bakery item list
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|                Add New Bakery Item               |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

        // Do while loop for user multiple create bakery item
        do{
          employees[employeeID].createBakeryItem();
          // cout << "Add successful!" << endl;

          cout << endl;
          do {
            cout << "Do you want to add another bakery item? (Y/N): "; // Ask user if they want to add another bakery item
            cin >> cont;
          } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n'); // Input Validation

          if (cont == 'Y' && cont == 'y'){
            employees[employeeID].accessMenuList();
            cout << endl;
          }

          if (cont == 'N' && cont == 'n'){ // Break if user does not want to add another bakery item
            break;
          }

        }while(cont == 'Y' || cont == 'y'); // Continue if user wants to add another bakery item
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
          cout << "Press (0) to exit....\n";
          cout << "Enter the choice of the bakery item to update price: ";
          cin >> index;

          while(cin.fail()) {
            cin.clear(); // clear the error state
            cin.ignore(10, '\n'); // ignore the next 10 characters...
            cout << "Invalid input. Please enter a valid choice: ";
            cin >> index;
          }

          if (index == 0){ // Allow user to exit
            break;
          }

          cout << "Enter the new price:";
          cin >> newPrice;
          employees[employeeID].changeBakeryItemPrice(index - 1, newPrice); // Update bakery item price
          cout << "Update successful!" << endl;

          cout << endl;
          do {
            cout << "Do you want to update the price of another bakery item? (Y/N): "; // Ask user if they want to update another bakery item price
            cin >> cont;
          } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n'); // Input Validation

          if (cont == 'Y' && cont == 'y'){
            employees[employeeID].accessMenuList(); // Show bakery item list
            cout << endl;
          }

          if (cont == 'N' && cont == 'n'){ // Break if user does not want to update another bakery item price
            break;
          }

        }while(cont == 'Y' || cont == 'y'); // Continue if user wants to update another bakery item price
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
          cout << "Press (0) to exit....\n";
          cout << "Enter the choice of the bakery item to enable: ";
          cin >> index;

          if (index == 0){ // Allow user to exit
            break;
          }

          employees[employeeID].enableBakeryItem(index - 1); // Enable bakery item
          cout << "Enable successful!" << endl;

          cout << endl;
          do {
            cout << "Do you want to enable another bakery item? (Y/N): "; // Ask user if they want to enable another bakery item
            cin >> cont;
          } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n'); // Input Validation

          if (cont == 'Y' && cont == 'y'){
            employees[employeeID].accessMenuList(); // Show bakery item list
            cout << endl;
          }

          if (cont == 'N' && cont == 'n'){ // Break if user does not want to enable another bakery item
            break;
          }

        }while(cont == 'Y' || cont == 'y'); // Continue if user wants to enable another bakery item
        break;
      
      case '4':
        // Disable Bakery Item
        employees[employeeID].accessMenuList(); // Show bakery item list
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|               Disable Bakery Item                |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        //Do while loop for user multiple disable bakery item
        // Ask User to choose the bakery item to disable
        do{
          cout << "Press (0) to exit....\n";
          cout << "Enter the choice of the bakery item to disable: ";
          cin >> index;

          while(cin.fail()) {
            cin.clear(); // clear the error state
            cin.ignore(10, '\n'); // ignore the next 10 characters...
            cout << "Invalid input. Please enter a valid choice: ";
            cin >> index;
          }

          if (index == 0){ // Allow user to exit
            break;
          }

          employees[employeeID].withdrawBakeryItem(index - 1); // Disable bakery item
          cout << "Disable successful!" << endl;

          cout << endl;
          do {
            cout << "Do you want to disable another bakery item? (Y/N): "; // Ask user if they want to disable another bakery item
            cin >> cont;
          } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n'); // Input Validation

          if (cont == 'Y' && cont == 'y'){
            employees[employeeID].accessMenuList(); // Show bakery item list
            cout << endl;
          }

          if (cont == 'N' && cont == 'n'){ // Break if user does not want to disable another bakery item
            break;
          }

        }while(cont == 'Y' || cont == 'y'); // Continue if user wants to disable another bakery item
        break;

      case '5':
        // Exit
        exit = true;
        break;
    }
    if (exit != true){
      cout << "Do you want to continue in Bakery Items Management Menu?" << endl; // Ask user if they want to continue in Bakery Items Management Menu
      cout << "Press 'y' or any key to exit: ";
      cin >> BakeryItemChoice;
    }
  }while(exit != true && (BakeryItemChoice == 'Y' || BakeryItemChoice == 'y')); // Continue if user wants to continue in Bakery Items Management Menu
}

void DiscountAndPromotion(Employee* employees, int employeeID){

  char cont; // For user to continue or not
  int index; // For user to choose the discount to edit
  string newName; // For user to enter new name
  double newMinSpend; // For user to enter new min spend
  string newDesc; // For user to enter new desc
  double newDiscountPercentage; // For user to enter new discount percentage
  char discountChoice; // For user to choose the discount option
  bool exit = false; // For user to exit
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
      if (discountChoice < '1' || discountChoice > '6'){ // Input Validation
        cout << "Invalid choice. Please try again." << endl;
      }
    }while(discountChoice < '1' || discountChoice > '6');

    // Switch case for Discount and Promotion
    switch (discountChoice){
      case '1':
        // Add New Discount

        // Do while loop for user multiple create discount
        do{
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|                  Add New Discount                |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        employees[employeeID].accessDiscountList(); // Show discount list
        employees[employeeID].addNewDiscount(); // Add new discount
        // cout << "Add successful!" << endl;

          cout << endl;
          do {
            cout << "Do you want to add another discount? (Y/N): "; // Ask user if they want to add another discount
            cin >> cont;
          } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n'); // Input Validation

          if (cont == 'Y' && cont == 'y'){
            employees[employeeID].accessDiscountList(); // Show discount list
            cout << endl;
          }

          if (cont == 'N' && cont == 'n'){ // Break if user does not want to add another discount
            break;
          }

        }while(cont == 'Y' || cont == 'y'); // Continue if user wants to add another discount
        break;

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
            if (discountChoice < '1' || discountChoice > '5'){ // Input Validation
              cout << "Invalid choice. Please try again." << endl;
            }
          }while(discountChoice < '1' || discountChoice > '5');

          // Switch case for Edit Discount
          switch(discountChoice){
            case '1':
              //Do while loop for user multiple edit name
              // Ask User to choose the discount to edit name
              do{
              // Edit Name
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
              cout << "|                    Edit Name                     |\n";
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
              employees[employeeID].accessDiscountList(); // Show discount list
                cout << "Press (0) to exit....\n";
                cout << "Enter the choice of the discount to edit name: "; // Ask user to choose the discount to edit name
                cin >> index;

                while(cin.fail()) {
                  cin.clear(); // clear the error state
                  cin.ignore(10, '\n'); // ignore the next 10 characters...
                  cout << "Invalid input. Please enter a valid choice: ";
                  cin >> index;
                }

                if (index == 0){ // Allow user to exit
                  break;
                }

                cout << "Enter the new name: ";
                cin.ignore();
                getline(cin, newName);

                employees[employeeID].editDiscountName(index - 1, newName);
                // cout << "Edit the discount name successful!" << endl;

                cout << endl;
                do {
                  cout << "Do you want to edit another discount name? (Y/N): ";
                  cin >> cont;
                } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

                if (cont == 'Y' && cont == 'y'){
                  employees[employeeID].accessDiscountList();
                }

                if (cont == 'N' && cont == 'n'){
                  break;
                }

              }while(cont == 'Y' || cont == 'y');
              break;

            case '2':
              // Edit Minimum Spend
              //Do while loop for user multiple edit min spend
              // Ask User to choose the discount to edit min spend
              do{
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
              cout << "|            Edit Minimum Spend                    |\n";
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
              employees[employeeID].accessDiscountList();
                cout << "Press (0) to exit....\n";
                cout << "Enter the choice of the discount to edit min spend: ";
                cin >> index;

                while(cin.fail()) {
                  cin.clear(); // clear the error state
                  cin.ignore(10, '\n'); // ignore the next 10 characters...
                  cout << "Invalid input. Please enter a valid choice: ";
                  cin >> index;
                }

                if (index == 0){ // Allow user to exit
                  break;
                }

                cout << "Enter the new minimum spend: ";
                cin >> newMinSpend;
                employees[employeeID].editDiscountMinimumPurchase(index - 1, newMinSpend);
                // cout << "Edit the discount min spend successful!" << endl;

                cout << endl;
                do {
                  cout << "Do you want to edit another discount min spend? (Y/N): ";
                  cin >> cont;
                } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

                if (cont == 'Y' && cont == 'y'){
                  employees[employeeID].accessDiscountList(); // Show discount list
                  cout << endl;
                }

                if (cont == 'N' && cont == 'n'){ // Break if user does not want to edit another discount min spend
                  break;
                }

              }while(cont == 'Y' || cont == 'y'); // Continue if user wants to edit another discount min spend
              break;

            case '3':
              // Edit Description
              //Do while loop for user multiple edit description
              // Ask User to choose the discount to edit description
              do{
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
              cout << "|            Edit Description                      |\n";
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
              employees[employeeID].accessDiscountList();
                cout << "Press (0) to exit....\n";
                cout << "Enter the choice of the discount to edit description: ";
                cin >> index;

                while(cin.fail()) {
                  cin.clear(); // clear the error state
                  cin.ignore(10, '\n'); // ignore the next 10 characters...
                  cout << "Invalid input. Please enter a valid choice: ";
                  cin >> index;
                }

                if (index == 0){ // Allow user to exit
                  break;
                }

                cout << "Enter the new description: ";
                cin.ignore();
                getline(cin, newDesc);

                employees[employeeID].editDiscountDescription(index - 1, newDesc);
                // cout << "Edit the discount description successful!" << endl;

                cout << endl;
                do {
                  cout << "Do you want to edit another discount description? (Y/N): ";
                  cin >> cont;
                } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

                if (cont != 'Y' && cont != 'y'){
                  employees[employeeID].accessDiscountList();
                  cout << endl;
                }

                if (cont == 'N' && cont == 'n'){
                  break;
                }

              }while(cont == 'Y' || cont == 'y');
              break;

            case '4':
              do{
              // Edit Discount Percentage
              //Do while loop for user multiple edit discount percentage
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
              cout << "|            Edit Discount Percentage              |\n";
              cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\nn";
              employees[employeeID].accessDiscountList();
              // Ask User to choose the discount to edit discount percentage
                cout << "Press (0) to exit....\n";
                cout << "Enter the choice of the discount to edit discount percentage: ";
                cin >> index;

                while(cin.fail()) {
                  cin.clear(); // clear the error state
                  cin.ignore(10, '\n'); // ignore the next 10 characters...
                  cout << "Invalid input. Please enter a valid choice: ";
                  cin >> index;
                }

                if (index == 0){ // Allow user to exit
                  break;
                }

                cout << "Enter the new discount percentage: ";
                cin >> 
                
                newDiscountPercentage;
                employees[employeeID].editDiscountPercentage(index - 1, newDiscountPercentage);
                // cout << "Edit the discount percentage successful!" << endl;

                cout << endl;
                do {
                  cout << "Do you want to edit another discount percentage? (Y/N): ";
                  cin >> cont;
                } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

                if (cont == 'Y' && cont == 'y'){
                  employees[employeeID].accessDiscountList();
                  cout << endl;
                }

                if (cont == 'N' && cont == 'n'){
                  break;
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
              cout << "Do you want to continue in Edit Discount Menu?" << endl;
              cout << "Press 'y' or any key to exit: ";
              cin >> discountChoice;
            }

        }while (exit != true && (discountChoice == 'Y' || discountChoice == 'y'));
        break;

        
      case '3':
        // Enable Discount
        //Do while loop for user multiple enable discount
        do{
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|                   Enable Discount                |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        employees[employeeID].accessDiscountList();
        // Ask User to choose the discount to enable
          cout << "Press (0) to exit....\n";
          cout << "Enter the choice of the discount to enable: ";
          cin >> index;

          while(cin.fail()) {
            cin.clear(); // clear the error state
            cin.ignore(10, '\n'); // ignore the next 10 characters...
            cout << "Invalid input. Please enter a valid choice: ";
            cin >> index;
          }

          if (index == 0){ // Allow user to exit
            break;
          }

          employees[employeeID].enableDiscount(index - 1);
          // cout << "Enable successful!" << endl;

          cout << endl;
          do {
            cout << "Do you want to enable another discount? (Y/N): ";
            cin >> cont;
          } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

          if (cont == 'Y' && cont == 'y'){
            employees[employeeID].accessDiscountList();
            cout << endl;
          }

          if (cont == 'N' && cont == 'n'){
            break;
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
          cout << "Press (0) to exit....\n";
          cout << "Enter the choice of the discount to disable: ";
          cin >> index;

          while(cin.fail()) {
            cin.clear(); // clear the error state
            cin.ignore(10, '\n'); // ignore the next 10 characters...
            cout << "Invalid input. Please enter a valid choice: ";
            cin >> index;
          }

          if (index == 0){ // Allow user to exit
            break;
          }

          employees[employeeID].disableDiscount(index - 1);
          // cout << "Disable successful!" << endl;

          cout << endl;
          do {
            cout << "Do you want to disable another discount? (Y/N): ";
            cin >> cont;
          } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

          if (cont == 'Y' && cont == 'y'){
            employees[employeeID].accessDiscountList();
            cout << endl;
          }

          if (cont == 'N' && cont == 'n'){
            break;
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
          cout << "Press (0) to exit....\n";
          cout << "Enter the choice of the discount to delete: ";
          cin >> index;

          while(cin.fail()) {
            cin.clear(); // clear the error state
            cin.ignore(10, '\n'); // ignore the next 10 characters...
            cout << "Invalid input. Please enter a valid choice: ";
            cin >> index;
          }

          if (index == 0){ // Allow user to exit
            break;
          }

          employees[employeeID].deleteDiscount(index - 1);
          // cout << "Delete successful!" << endl;

          cout << endl;
          do {
            cout << "Do you want to delete another discount? (Y/N): ";
            cin >> cont;
          } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

          if (cont == 'Y' && cont == 'y'){
            employees[employeeID].accessDiscountList();
            cout << endl;
          }

          if (cont == 'N' && cont == 'n'){
            break;
          }
        }while(cont == 'Y' || cont == 'y');
        break;

      case '6':
        // Exit
        exit = true;
        break;
    }
    
    if (exit != true){
      cout << "Do you want to continue in Promotions and Discounts Menu?";
      cout << "Press 'y' or any key to exit: ";
      cin >> discountChoice;
    }
  }  while (exit != true && (discountChoice == 'Y' || discountChoice == 'y'));
}

void EmployeeManagement(Employee* employees, int employeeID, int employeeCount){
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
        do{
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|                Create New Employee               |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        // Do while loop for user multiple create employee
          cout << "Press (0) to exit....\n";
          cout << "Enter the new employee name: ";
          cin.ignore();
          getline(cin, newEmployee);

          if (newEmployee == "0"){ // Allow user to exit
            break;
          }

          cout << "Supervisor/ Baker/ Cashier" << endl;
          cout << "Enter the new employee role: ";
          getline(cin, newRole);

          cout << "Enter the new employee ID: ";
          cin >> newEmployeeID;

          cout << "Enter the new employee password: ";
          cin >> newEmployeePassword;

          employees[employeeID].createNewEmployee(employees, employeeCount, newEmployeeID, newEmployee, newRole, newEmployeePassword);
          // cout << "Create successful!" << endl;

          cout << endl;
          do {
            cout << "Do you want to create another employee? (Y/N): ";
            cin >> cont;
          } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

          if (cont == 'N' && cont == 'n'){
            cout << "Updated Employee List: " << endl;
            employees[employeeID].displayAllEmployeeDetails(employees);
            break;
          }

          if (cont == 'Y' && cont == 'y'){
            cout << endl;
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
          cout << "Press (0) to exit....\n";
          cout << "Enter the choice of the employee to change role: ";
          cin >> index;

          while(cin.fail()) {
            cin.clear(); // clear the error state
            cin.ignore(10, '\n'); // ignore the next 10 characters...
            cout << "Invalid input. Please enter a valid choice: ";
            cin >> index;
         }

          if (index == 0){ // Allow user to exit
            break;
          }

          if (index < 0 || index > employeeCount) {
            cout << "Invalid index." << endl;
            return;
          }

          cout << "Supervisor/ Baker/ Cashier" << endl;
          cout << "Enter the new role: ";
          cin >> newRole;
          employees[employeeID].changeEmployeeRole(employees, index - 1, newRole);
          // cout << "Change successful!" << endl;
          
          cout << endl;
          do {
            cout << "Do you want to change another employee role? (Y/N): ";
            cin >> cont;
          } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

          cout << endl;
          if (cont == 'N' && cont == 'n'){
            break;
          }
        }while(cont == 'Y' || cont == 'y');
        break;

      case '4':
        // Delete Employee
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        cout << "|                 Delete Employee                  |\n";
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
        // Do while loop for user multiple delete employee
        do{
        employees[employeeID].displayAllEmployeeDetails(employees);
          cout << "Press (0) to exit....\n";
          cout << "Enter the choice of the employee to delete: ";
          cin >> index;

          while(cin.fail()) {
            cin.clear(); // clear the error state
            cin.ignore(10, '\n'); // ignore the next 10 characters...
            cout << "Invalid input. Please enter a valid choice: ";
            cin >> index;
          }

          if (index == 0){ // Allow user to exit
            break;
          }

          if (index < 0 || index > employeeCount) {
            cout << "Invalid index." << endl;
            return;
          }

          employees[employeeID].deleteEmployee(employees, index - 1);
          // cout << "Delete successful!" << endl;

          cout << endl;
          do {
            cout << "Do you want to delete another employee? (Y/N): ";
            cin >> cont;
          } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

          if (cont == 'N' && cont == 'n'){
            cout << "Updated Employee List: " << endl;
            employees[employeeID].displayAllEmployeeDetails(employees);
            break;
          }
        }while(cont == 'Y' || cont == 'y');
        break;

      case '5':
        // Exit
        exit = true;
        break;
      }
    
    if (exit != true){
      cout << "Do you want to continue in Employee Management Menu? " << endl;
      cout << "Press 'y' or any key to exit: ";
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
    cout << "| 4. Profit and Cost Analysis                            |" << endl;
    cout << "| 5. Exit                                                |" << endl;
    cout << "==========================================================\n";
    do{
      cout << "Enter your choice: ";
      cin >> reportingChoice;
      if (reportingChoice < '1' || reportingChoice > '5'){
        cout << "Invalid choice. Please try again." << endl;
      }
    }while(reportingChoice < '1' || reportingChoice > '5');

    // Switch case for Reporting and Analytics
    switch(reportingChoice){
      case '1':
        // Display Current Financial Summary
        cout << "*********** Current Financial Summary ***********\n";
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
          cout << "*********** Access Transaction History **********\n";
          do { // Input Validation for YYYYMMDD
            cout << "Enter the date to access transaction history (YYYYMMDD): ";
            cin >> date;
            if (date.length() != 8) {
              cout << "Invalid date. Please try again." << endl;
            }
          } while (date.length() != 8);

          employees[employeeID].accessTransactionHistory(date);

          cout << endl;
          do {
            cout << "Do you want to access another transaction history? (Y/N): ";
            cin >> reportingChoice;
          } while (reportingChoice != 'Y' && reportingChoice != 'y' && reportingChoice != 'N' && reportingChoice != 'n');

          if (reportingChoice == 'N' && reportingChoice != 'n') {
            break;
          }
        } while (reportingChoice == 'Y' || reportingChoice == 'y');
        break;

      case '3':
        // Display Balance Sheet
        employees[employeeID].displayBalanceSheet();
        break;

      case '4':
        // Profit and Cost Analysis, Profit and Price Analysis (switch case)
        char profitChoice;
        char cont;
        int index;
        do{
          cout << "==========================================================\n";
          cout << "||              Profit and Price Analysis               ||\n";
          cout << "==========================================================\n";
          cout << "| 1. Price Analysis                                      |" << endl;
          cout << "| 2. Profit Analysis                                     |" << endl;
          cout << "| 3. Exit                                                |" << endl;
          cout << "==========================================================\n";
          do{
            cout << "Enter your choice: ";
            cin >> profitChoice;
            if (profitChoice < '1' || profitChoice > '3'){
              cout << "Invalid choice. Please try again." << endl;
            }
          }while(profitChoice < '1' || profitChoice > '3');

          switch(profitChoice){
            case '1':
              // Price Analysis
              // Do while loop for user multiple price analysis
              do {
               // Show the price of the bakery items
                employees[employeeID].accessMenuList();
                cout << "Press (0) to exit....\n";
                cout << "Enter the choice of the bakery item to compare cost vs price: ";
                cin >> index;

                while(cin.fail()) {
                  cin.clear(); // clear the error state
                  cin.ignore(10, '\n'); // ignore the next 10 characters...
                  cout << "Invalid input. Please enter a valid choice: ";
                  cin >> index;
                }

                if (index == 0){ // Allow user to exit
                  break;
                }
                
                employees[employeeID].compareCostVsPrice(index - 1);
                cout << endl;
                do {
                  cout << "Do you want to compare another bakery item? (Y/N): ";
                  cin >> cont;
                } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

                cout << endl;

                if (cont == 'N' && cont != 'n'){
                  break;
                }
              } while (cont == 'Y' || cont == 'y');
              break;

            case '2':
              // Profit Analysis
              // Do while loop for user multiple profit analysis
              do {
                // Show the profit of the bakery items
                employees[employeeID].accessMenuList();
                cout << "Press (0) to exit....\n";
                cout << "Enter the choice of the bakery item to compare cost vs profit: ";
                cin >> index;

                while(cin.fail()) {
                  cin.clear(); // clear the error state
                  cin.ignore(10, '\n'); // ignore the next 10 characters...
                  cout << "Invalid input. Please enter a valid choice: ";
                  cin >> index;
                }

                if (index == 0){ // Allow user to exit
                  break;
                }

                employees[employeeID].compareCostVsProfit(index - 1);
                cout << endl;
                do {
                  cout << "Do you want to compare another bakery item? (Y/N): ";
                  cin >> cont;
                } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

                cout << endl;

                if (cont == 'N' && cont != 'n'){
                  break;
                }
              } while (cont == 'Y' || cont == 'y');
              break;

            case '3':
              // Exit
              exit = true;
              break;
          }
          if (exit != true){
            cout << "Do you want to continue in Profit and Cost Analysis Menu? " << endl;
            cout << "Press 'y' or any key to exit: ";
            cin >> profitChoice;
          }
        }while(exit != true && (profitChoice == 'Y' || profitChoice == 'y'));
        break;

      case '5':
        // Exit
        exit = true;
        break;
    }
    if (exit != true){
      cout << endl;
      cout << "Do you want to continue in Reporting and Analytics Menu? " << endl;
      cout << "Press 'y' or any key to exit: ";
      cin >> reportingChoice;
    }
  }while (exit != true && (reportingChoice == 'Y' || reportingChoice == 'y'));
}

void BakeCookieCake(Employee* employees, int employeeID){
  int index, quantity;
  char cont;
  cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
  cout << "|             Bake New Cakes and Cookies           |\n";
  cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
  employees[employeeID].accessMenuList();

  // Do while loop for user multiple create bakery item
  do{
    cout << "Press (0) to exit....\n";
    cout << "Enter the choice for the baking item: ";
    cin >> index;

    while(cin.fail()) {
      cin.clear(); // clear the error state
      cin.ignore(10, '\n'); // ignore the next 10 characters...
      cout << "Invalid input. Please enter a valid choice: ";
      cin >> index;
      }

    if (index == 0){ // Allow user to exit
      break;
    }

    cin.ignore();
    cout << "Enter the quantity to bake: "; // Bug: will show quantity negative for cookies
    cin >> quantity;
    employees[employeeID].bakeNewBakeryItem(index - 1, quantity);

    cout << endl;
    do {
      cout << "Do you want to add another baking item? (Y/N): ";
      cin >> cont;
    } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

    cout << endl;

    if (cont == 'N' && cont == 'n'){
      break;
    }
  }while(cont == 'Y' || cont == 'y');
}

void processOrder(Employee* employees, int employeeID, int employeeCount){
  // For index of cashier when transfer cart
  int cashierIndex[MAX_EMPLOYEES]; 
  int count = 0;

  bool exit = false;
  char cashierChoice;
  int quantity;
  double weight;
  char cont;
  int index;
  string date;

  do {
    cout << "==========================================================\n";
    cout << "||                 Cashier Order Processing             ||\n";
    cout << "==========================================================\n";
    cout << "| 1. Add Cakes/ Cookies                                  |\n";
    cout << "| 2. Add Cakes by Weight                                 |\n";
    cout << "| 3. Edit Item                                           |\n";
    cout << "| 4. Display Cart                                        |\n";
    cout << "| 5. Transfer Cart                                       |\n";
    cout << "| 6. Checkout                                            |\n";
    cout << "| 7. Show receipt                                        |\n";
    cout << "| 8. Exit                                                |\n";
    cout << "==========================================================\n";

    do {
        cout << "Enter your choice: ";
        cin >> cashierChoice;
        if (cashierChoice < '1' || cashierChoice > '8'){
            cout << "Invalid choice. Please try again." << endl;
        }
    } while(cashierChoice < '1' || cashierChoice > '8');

    bool addMoreItems = true;
    // Switch case for Cashier Order Processing
    switch(cashierChoice){
      case '1':
      // employees[1].bakeNewBakeryItem(2, 2); // Check
      char itemType;
      while(addMoreItems){
        employees[employeeID].accessMenuList();
        cout << "Enter the choice of the item: ";
        cin >> index;

        while(cin.fail()) { // Input Validation
          cin.clear(); // clear the error state
          cin.ignore(10, '\n'); // ignore the next 10 characters...
          cout << "Invalid input. Please enter a valid choice: ";
          cin >> index;
        }

        if (index == 0){ // Allow user to exit
          break;
        }

        cout << "Enter the quantity: ";
        cin >> quantity;
        employees[employeeID].addBakeryItemToCart(index - 1, quantity);
        cout << endl;

        cout << "Do you want to add more items ?"  << endl;
        cout << "Press 'Y' or any key to stop adding items: ";
        cin >> cont;
        cout << endl;
        if (cont != 'Y' && cont != 'y') {
          char display;
          addMoreItems = false;
          cout << "Do you want to display cart details (Y/N): ";
          cin >> display;
          if (display == 'Y' || display == 'y') {
            employees[employeeID].displayCartDetails();
            cout << endl;
          }

          cout << "Press 0 to checkout/ any key to back to Cashier Order Processing: ";
          cin >> cont;
          if (cont == '0') {
            cout << endl;
            checkout(employees, employeeID);
          }
          break;
        }
      }

      break;

      case '2':
        // Add Cake by Weight
        // employees[1].bakeNewBakeryItem(2, 2); // Check
        employees[employeeID].accessMenuList();
        do {
          do {
            cout << "Press (0) to exit....\n";
            cout << "Enter the choice of the cake: ";
            cin >> index;

            while(cin.fail()) {
              cin.clear(); // clear the error state
              cin.ignore(10, '\n'); // ignore the next 10 characters...
              cout << "Invalid input. Please enter a valid choice: ";
              cin >> index;
            }

            if (index == 0) {
              break;
            }
          } while (index < 0 || index > employees[employeeID].getAllBakeryItemCount());

          cout << "Enter the weight of the cake in gram(s): ";
          cin >> weight;

          employees[employeeID].addCakeByWeightToCart(index - 1, weight);

          cout << endl;
          cout << "Do you want to add more cakes by weight? (Y/N): ";
          cin >> cont;

          if (cont != 'Y' && cont != 'y') {
            char display;
            addMoreItems = false;
            cout << "Do you want to display cart details ?" << endl;
            cout << "Press 'Y' or any key to exit: ";
            cin >> display;
            if (display == 'Y' || display == 'y') {
              employees[employeeID].displayCartDetails();
              cout << endl;
            }
            cout << "Press 0 to checkout/ any key to back to Cashier Order Processing: ";
            cin >> cont;
            if (cont == '0') {
              cout << endl;
              checkout(employees, employeeID);
            }
            break;
          }
          break;
        } while (cont == 'Y' || cont == 'y');
        break;

      case '3':
        // Edit Item
        // Ask whether delete or edit
        char editOrDelete;
        do {
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

                while(cin.fail()) {
                  cin.clear(); // clear the error state
                  cin.ignore(10, '\n'); // ignore the next 10 characters...
                  cout << "Invalid input. Please enter a valid choice: ";
                  cin >> index;
                }

                if (index == 0) {
                  break;
                }

                cout << "Enter the new quantity: ";
                cin >> quantity;
                employees[employeeID].updateBakeryItemQuantityInCart(index - 1, quantity);

                cout << endl;

                do {
                  cout << "Do you want to edit another item? (Y/N) " << endl;
                  cin >> cont;
                  } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');
                  if (cont == 'N' && cont != 'n') {
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

                while(cin.fail()) {
                  cin.clear(); // clear the error state
                  cin.ignore(10, '\n'); // ignore the next 10 characters...
                  cout << "Invalid input. Please enter a valid choice: ";
                  cin >> index;
                }

                if (index == 0) {
                  break;
                }

                employees[employeeID].removeBakeryItemFromCart(index - 1);

                cout << endl;

                do {
                  cout << "Do you want to delete another item? (Y/N): ";
                  cin >> cont;
                } while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n');

                if (cont == 'N' && cont == 'n') {
                  break;
                }
              } while (cont == 'Y' || cont == 'y');
              break;

            case '3':
              // Exit
              break;
          }        
        } while (editOrDelete != '3');

      case '4':
        // Display Cart
        employees[employeeID].displayCartDetails();
        cout << "Press any key to EXIT....";
        cin >> cont;
        break;

      case '5':
        // Transfer Cart
        char transferChoice;
        int transferIndex;
        int selectedCashierIndex;

        // employees[1].bakeNewBakeryItem(2,2);
        // employees[2].addBakeryItemToCart(2,2);
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
        cout << "|                 Transfer Cart                    |" << endl;
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
        cout << "| 1. Select Cashier To Transfer                    |" << endl;
        cout << "| 2. Cancel Transfer and Return to Menu            |" << endl;
        cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
        do {
          cout << "Enter your choice: ";
          cin >>transferChoice;
          if (transferChoice < '1' ||transferChoice > '2') {
            cout << "Invalid choice. Please try again." << endl;
          }
        } while (transferChoice < '1' ||transferChoice > '2');

        switch(transferChoice){
          case '1':
            // Select Cashier To Transfer
            // Display all cashier
            cout << "+-----+--------------------------+" << endl;
            cout << "| No. | Cashier Name             |" << endl;
            cout << "+-----+--------------------------+" << endl;
            for (int i = 0; i < employeeCount; i++) {
                if (employees[i].getRole() == "Cashier") {
                  cashierIndex[count] = i; // Store index of cashier
                  cout << "| " << setw(3) << ++count << " | " << setw(24) << employees[i].getName() << " |" << endl;
                }
            }
            cout << "+-----+--------------------------+" << endl;
            cout << "Press (0) to exit....\n";
            cout << "Enter the number of the cashier you want to transfer the cart to: ";
            cin >> transferIndex;

            while(cin.fail()) {
              cin.clear(); // clear the error state
              cin.ignore(10, '\n'); // ignore the next 10 characters...
              cout << "Invalid input. Please enter a valid choice: ";
              cin >> transferIndex;
            }

            if (transferIndex == 0) {
              break;
            }
            // Validate transferIndex
            while (transferIndex < 1 || transferIndex > count) {
              cout << "Invalid index. Please try again." << endl;
              cout << "Enter the number of the cashier you want to transfer the cart to: ";
              cin >> transferIndex;
            }

            selectedCashierIndex = cashierIndex[transferIndex - 1]; // Get index of selected cashier
            cout << "Current Cart: " << endl;
            employees[employeeID].displayCartDetails();

            cout << endl;
            cout << "You have chosen to transfer the cart to cashier " << employees[selectedCashierIndex].getName() << "." << endl;
            cout << "Please note that once the cart is transferred, it will be removed from the current cashier." << endl;
            cout << "Are you sure you want to proceed with the transfer? (Y/N): ";
            cin >> cont;
            employees[employeeID].moveCartFromThisCashierToAnotherCashier(employees + selectedCashierIndex);
            cout << "Press any key to EXIT....";
            cin >> cont;
            break;

          case '2':
            // Cancel Transfer and Return to Menu
            break;
        }
        break;

      case '6':
        // Checkout
        checkout(employees, employeeID);
        break;

      case '7':
        // Display receipt for previous transaction (Allow user choose date and transaction to view receipt)
        cout << "Enter the date to show receipt (YYYYMMDD): ";
        cin >> date;
        
        // Date Input validation
        do {
          if (date.length() != 8) {
            cout << "Invalid date. Please try again." << endl;
            cout << "Enter the date to show receipt (YYYYMMDD): ";
            cin >> date;
          }
        } while (date.length() != 8);

        cout << "Enter the order number to show receipt: ";
        cin >> index; // Use for order number

        while(cin.fail()) {
          cin.clear(); // clear the error state
          cin.ignore(10, '\n'); // ignore the next 10 characters...
          cout << "Invalid input. Please enter a valid choice: ";
          cin >> index;
        }

        cout << endl;
        employees[employeeID].showReceipt(date, index);
        break;

      case '8':
        // Exit
        // Check if cart is empty
        // if (employees[employeeID].getCartItemCount() > 0) {
        //   cout << "Cart is not empty. Do you want to checkout? (Y/N): ";
        //   cin >> cont;
        //   if (cont == 'Y' || cont == 'y') {
        //     employees[employeeID].checkout(convertTimeToYYYYMMDD());
        //   }
        // }
        exit = true;
        break;

      if (exit != true) {
        cout << endl;
        cout << "Press 0 to checkout/ any key to back to Cashier menu: ";
        cin >> cashierChoice;
        if (cashierChoice == '0') {
          cout << endl;
          checkout(employees, employeeID);
          break;
        }
      }
    }
  } while (exit != true && cashierChoice != '0');
}

void checkout (Employee* employees, int employeeID){
  char show;
  employees[employeeID].checkout(convertTimeTOYYYY_MM__DD());
  // Display current transaction receipt
  cout << "Do you want to show receipt? (Y/N): ";
  cin >> show;
  if (show == 'Y' || show == 'y') {
    employees[employeeID].showReceipt(convertTimeToYYYYMMDD(), employees[employeeID].getOrderNo());
  }
}