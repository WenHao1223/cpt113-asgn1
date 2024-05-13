#include "Baker.h"

Baker::Baker(string employeeID, string name) {
  this->employeeID = employeeID;
  this->name = name;
  // cout << "Baker " << name << " has been added." << endl;
}

void Baker::startBakery() {
  cout << "Baker " << name << " (" << employeeID << ") starts the bakery." << endl;
}

void Baker::closeBakery() {
  cout << "Baker " << name << " (" << employeeID << ") closes the bakery." << endl;
}