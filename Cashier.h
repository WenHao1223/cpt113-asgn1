#ifndef CASHIER_H
#define CASHIER_H

#include <iostream>
#include <string>

using namespace std;

class Cashier {
  private:
    string employeeID;
    string name;
        
  public:
    // Constructor
    Cashier(string employeeID, string name);

    // member functions
    void startBakery();
};

#endif