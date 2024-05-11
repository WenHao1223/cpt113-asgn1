#include "Employee.h"
#include "BakeryItem.h"

const int MAX_INGREDIENTS_INVENTORY = 20;

Employee::Employee() {
  employeeID = "";
  name = "";
  position = "";
}

Employee::Employee(string employeeID, string name, string position) {
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
    supervisor = new Supervisor(employeeID, name);
  } else if (position == "Baker") {
    baker = new Baker(employeeID, name);
  } else {
    cashier = new Cashier(employeeID, name);
  }
}

void Employee::displayEmployeeDetails() const {
  cout << "Employee ID: " << employeeID << endl;
  cout << "Name: " << name << endl;
  cout << "Position: " << position << endl;

  // hide after done testing
  cout << "Supervisor: " << supervisor << endl;
  cout << "Baker: " << baker << endl;
  cout << "Cashier: " << cashier << endl;

  cout << endl;
}

void Employee::startBakery() const {
  cout << "Bakery start operating now." << endl;

  // Create ingredient inventory
  IngredientInventory * ingredientInventory = new IngredientInventory[MAX_INGREDIENTS_INVENTORY] {
    IngredientInventory("Ingredient 1", 10.0, 100000.0),
    IngredientInventory("Ingredient 2", 20.0, 200)
  };

  // print address of ingredientInventory
  // cout << "Ingredient Inventory address: " << ingredientInventory << endl;

  if (supervisor != nullptr) {
    supervisor->startBakery();
  } else if (baker != nullptr) {
    baker->startBakery();
  } else if (cashier != nullptr) {
    cashier->startBakery();
  } else {
    cout << "Not a valid position to start the bakery." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Selling " << ingredientInventory[0].getIngredientInventoryCount() << " items today." << endl;
}

void Employee::accessIngredientInventoryDetails() const {
  cout << "Accessing ingredient inventory details..." << endl;
  if (supervisor != nullptr || baker != nullptr) {
    ingredientInventory->accessIngredientInventoryDetails();
  } else {
    cout << "Only supervisor or baker can access ingredient inventory details." << endl;
  }
}

void Employee::checkIngredientInventory() {
  cout << "Checking ingredient inventory..." << endl;
  if (supervisor != nullptr) {
    ingredientInventory->checkIngredientInventory();
  } else {
    cout << "Only supervisor can check ingredient inventory." << endl;
  }
}

Employee::~Employee() {
  delete supervisor;
  delete baker;
  delete cashier;

  // cout << "Employee " << name << " has been removed." << endl;
}

IngredientInventory * Employee::ingredientInventory = IngredientInventory::getIngredientInventory();