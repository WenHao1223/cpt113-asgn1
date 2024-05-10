#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Supervisor {
  private:
    string name;
  public:
    // Constructor
    Supervisor(string name) {
      this->name = name;
      cout << "Supervisor " << name << " has been added." << endl;
    }
};

class Baker {
  private:
    string name;
  public:
    // Constructor
    Baker(string name) {
      this->name = name;
      cout << "Baker " << name << " has been added." << endl;
    }
};

class Cashier {
  private:
    string name;
  public:
    // Constructor
    Cashier(string name) {
      this->name = name;
      cout << "Cashier " << name << " has been added." << endl;
    }
};

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
    Employee(string employeeID, string name, string position) {
      if (employeeID == "") {
        cout << "Employee ID cannot be empty." << endl;
        exit(EXIT_FAILURE);
        return;
      }

      if (name == "") {
        cout << "Name cannot be empty." << endl;
        exit(EXIT_FAILURE);
        return;
      }

      if (position == "") {
        cout << "Position cannot be empty." << endl;
        exit(EXIT_FAILURE);
        return;
      }

      this->employeeID = employeeID;
      this->name = name;
      this->position = position;
      // cout << "Employee " << name << " has been added." << endl;

      if (position == "Supervisor") {
        supervisor = new Supervisor(name);
      } else if (position == "Baker") {
        baker = new Baker(name);
      } else {
        cashier = new Cashier(name);
      }
    }

    // member functions
    void displayEmployeeDetails() const {
      cout << "Employee ID: " << employeeID << endl;
      cout << "Name: " << name << endl;
      cout << "Position: " << position << endl;

      // hide after done testing
      cout << "Supervisor: " << supervisor << endl;
      cout << "Baker: " << baker << endl;
      cout << "Cashier: " << cashier << endl;

      cout << endl;
    }

    // Friend function
    // friend void accessMenuList();
    // friend void accessMenuDetails();

    // Destructor
    ~Employee() {
      delete supervisor;
      delete baker;
      delete cashier;

      cout << "Employee " << name << " has been removed." << endl;
    }
};

int main () {
  // Create employees
  Employee supervisor1("S1", "Supervisor 1", "Supervisor");
  Employee baker1("B1", "Baker 1", "Baker");
  Employee cashier1("C1", "Cashier 1", "Cashier");

  cout << endl;

  // Display employee details
  supervisor1.displayEmployeeDetails();
  baker1.displayEmployeeDetails();
  cashier1.displayEmployeeDetails();
  
  return 0;
}