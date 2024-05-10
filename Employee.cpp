#include "Employee.h"
#include "BakeryItem.h"

const int MAX_INGREDIENTS_INVENTORY = 20;

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
    supervisor = new Supervisor(name);
  } else if (position == "Baker") {
    baker = new Baker(name);
  } else {
    cashier = new Cashier(name);
  }
}

IngredientInventory * Employee::startBakery() const {
  cout << "Bakery start operating now." << endl;

  // Create ingredient inventory
  IngredientInventory * ingredientInventory = new IngredientInventory[MAX_INGREDIENTS_INVENTORY] {
    IngredientInventory("Ingredient 1", 10.0, 100000.0),
    IngredientInventory("Ingredient 2", 20.0, 200)
  };

  // print address of ingredientInventory
  cout << "Ingredient Inventory address: " << ingredientInventory << endl;

  cout << "Selling " << ingredientInventory[0].getIngredientInventoryCount() << " items today." << endl;

  return ingredientInventory;
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

Employee::~Employee() {
  delete supervisor;
  delete baker;
  delete cashier;

  // cout << "Employee " << name << " has been removed." << endl;
}

IngredientInventory * Employee::ingredientInventory = IngredientInventory::getIngredientInventory();