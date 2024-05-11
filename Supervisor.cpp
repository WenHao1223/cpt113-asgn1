#include "Supervisor.h"

Supervisor::Supervisor(string employeeID, string name) {
  this->employeeID = employeeID;
  this->name = name;
  // cout << "Supervisor " << name << " has been added." << endl;
}

void Supervisor::startBakery() {
  cout << "Supervisor " << name << " (" << employeeID << ") starts the bakery." << endl;
}