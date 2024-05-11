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
    IngredientInventory("Ingredient 2", 20.0, 200),
    IngredientInventory("Ingredient 3", 30.0, 0.0),
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

void Employee::displayIngredientInventoryList() const {
  if (supervisor != nullptr || baker != nullptr) {
    cout << position << " - Displaying ingredient inventory list..." << endl;
    ingredientInventory->displayIngredientInventoryList();
  } else {
    cout << "Only supervisor or baker can display ingredient inventory list." << endl;
  }
}

void Employee::accessIngredientInventoryDetails(int choice) const {
  if (supervisor != nullptr || baker != nullptr) {
    cout << position << " - Accessing ingredient inventory details..." << endl;
    (ingredientInventory+choice)->accessIngredientInventoryDetails();
  } else {
    cout << "Only supervisor or baker can access ingredient inventory details." << endl;
  }
}

void Employee::checkIngredientInventory() const {
  if (supervisor != nullptr || baker != nullptr) {
    cout << position << " - Checking ingredient inventory..." << endl;
    ingredientInventory->checkIngredientInventory();
  } else {
    cout << "Only supervisor or baker can check ingredient inventory." << endl;
  }
}

void Employee::restockIngredientInventory(int choice, int quantity) const {
  if (supervisor != nullptr) {
    cout << position << " - Restocking ingredient inventory..." << endl;
    if (quantity < 0) {
      cout << "Quantity cannot be negative." << endl;
      return;
    }
    ingredientInventory->restockIngredientInventory(choice, quantity);
  } else {
    cout << "Only supervisor can restock ingredient inventory." << endl;
  }
}

Employee::~Employee() {
  delete supervisor;
  delete baker;
  delete cashier;

  // cout << "Employee " << name << " has been removed." << endl;
}

IngredientInventory * Employee::ingredientInventory = IngredientInventory::getIngredientInventory();