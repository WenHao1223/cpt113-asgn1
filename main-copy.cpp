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

int login (Employee employees[]) {
  cout << endl;
  cout << "==========================================================\n";
  cout << "                    Employee Login Page                   \n";
  cout << "==========================================================\n";
  cout << "Please select your name..." << endl;
  cout << "Enter your employee id and password..." << endl;
  cout << endl;

  cout << "Employee list: " << endl;
  cout << "---------------------------------\n";
  cout << "| No. | Employee Name           |\n";
  cout << "---------------------------------\n";
  for (int i = 0; i < MAX_EMPLOYEES; i++) {
    if (employees[i].getName() != "") {
        cout << "| " << setw(3) << left << i+1 << " | " << setw(23) << left << employees[i].getName() << " |\n";
    }
  }
  cout << "---------------------------------\n";

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
    if (employees[employeeChoice-1].login(employeeID, password)) {
      break;
    } else {
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

  cout << "==========================================================\n";
  cout << "||                                                      ||\n";
  cout << "||                   Eid Delights Bakery                ||\n";
  cout << "||                                                      ||\n";
  cout << "==========================================================\n";
  cout << "Today's Date: " << DATE_YYYYMMDD << endl;
  cout << "Please login to continue...." << endl;
  // Done: login
  int employeeID = login(employees);
  employees[employeeID].getEmployeeID();
  return 0;
}