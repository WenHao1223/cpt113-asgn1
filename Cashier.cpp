#include "Cashier.h"

Cashier::Cashier(string employeeID, string name) {
  this->employeeID = employeeID;
  this->name = name;
  this->cart = new Cart();
  // cout << "Cashier " << name << " has been added." << endl;
}

void Cashier::startBakery() {
  cout << "Cashier " << name << " (" << employeeID << ") starts the bakery." << endl;
}

void Cashier::closeBakery() {
  cout << "Cashier " << name << " (" << employeeID << ") closes the bakery." << endl;
}

Cart * Cashier::getCart() {
  return cart;
}

Cashier::~Cashier() {
  delete cart;
}