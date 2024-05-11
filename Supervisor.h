#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <iostream>
#include <string>

using namespace std;

class Supervisor {
  private:
    string employeeID;
    string name;
        
  public:
    // Constructor
    Supervisor(string employeeID, string name);

    // member functions
    void startBakery();
};

#endif