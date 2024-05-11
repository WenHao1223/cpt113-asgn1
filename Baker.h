#ifndef BAKER_H
#define BAKER_H

#include <string>
#include <iostream>

using namespace std;

class Baker {
  private:
    string employeeID;
    string name;
        
  public:
    // Constructor
    Baker(string employeeID, string name);

    // member functions
    void startBakery();
};

#endif