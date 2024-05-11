#include "Cashier.h"

Cashier::Cashier(string employeeID, string name) {
  this->employeeID = employeeID;
  this->name = name;
  // cout << "Cashier " << name << " has been added." << endl;
}

void Cashier::startBakery() {
  cout << "Cashier " << name << " (" << employeeID << ") starts the bakery." << endl;
}