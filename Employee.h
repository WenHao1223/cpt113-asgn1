#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>
#include "Supervisor.h"
#include "Baker.h"
#include "Cashier.h"
#include "BakeryItem.h"

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
        
  public:
    // Constructor
    Employee(string employeeID, string name, string position);

    // member functions
    void startBakery();
    void displayEmployeeDetails() const;

    // Friend function
    // void Employee::accessMenuList(BakeryItem * items) const;
    // void BakeryItem::accessMenuDetails() const;
    void accessBakeryName(BakeryItem & item);

    // Destructor
    ~Employee();
};

#endif