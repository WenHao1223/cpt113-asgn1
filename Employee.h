#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>
#include "Supervisor.h"
#include "Baker.h"
#include "Cashier.h"
#include "BakeryItem.h"
#include "IngredientInventory.h"

using namespace std;

// forward declaration
class BakeryItem;

class Employee {
  private:
    string employeeID;
    string name;
    string position;
    Supervisor * supervisor = nullptr;
    Baker * baker = nullptr;
    Cashier * cashier = nullptr;

    static IngredientInventory * ingredientInventory;
        
  public:
    // Constructor
    Employee(string employeeID, string name, string position);

    // member functions
    static void startBakery();
    void displayEmployeeDetails() const;

    // Destructor
    ~Employee();
};

#endif