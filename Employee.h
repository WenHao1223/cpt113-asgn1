#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>
#include "Supervisor.h"
#include "Baker.h"
#include "Cashier.h"

using namespace std;

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
    void displayEmployeeDetails() const;

    // Friend function
    // friend void accessMenuList();
    // friend void accessMenuDetails();

    // Destructor
    ~Employee();
};

#endif