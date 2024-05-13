#ifndef CASHIER_H
#define CASHIER_H

#include <iostream>
#include <string>

#include "Cart.h"

using namespace std;

class Cashier {
  private:
    string employeeID;
    string name;
    Cart * cart = nullptr;
  public:
    // Constructor
    Cashier(string employeeID, string name);

    // member functions
    void startBakery();
    void closeBakery();

    // accessor
    Cart * getCart();

    // destructor
    ~Cashier();
};

#endif