#include <iomanip>
#include <cmath>

#include "Discount.h"
#include "Employee.h"

const int MAX_BAKERY_ITEMS = Constant::MAX_BAKERY_ITEMS;
const int MAX_INGREDIENTS_INVENTORY = Constant::MAX_INGREDIENTS_INVENTORY;

Employee::Employee() {
  employeeID = "";
  name = "";
  role = "";
}

Employee::Employee(string employeeID, string name, string role) {
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

  if (role == "") {
    cout << "Position cannot be empty." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  this->employeeID = employeeID;
  this->name = name;
  this->role = role;
  // cout << "Employee " << name << " has been added." << endl;

  if (role == "Supervisor") {
    supervisor = new Supervisor(employeeID, name);
  } else if (role == "Baker") {
    baker = new Baker(employeeID, name);
  } else {
    cashier = new Cashier(employeeID, name);
  }
}

void Employee::displayEmployeeDetails() const {
  cout << "Employee ID: " << employeeID << endl;
  cout << "Name: " << name << endl;
  cout << "Position: " << role << endl;

  // hide after done testing
  cout << "Supervisor: " << supervisor << endl;
  cout << "Baker: " << baker << endl;
  cout << "Cashier: " << cashier << endl;

  cout << endl;
}

void Employee::setIngredientCostToInventoryIngredientCost() {
  cout << role << " - Setting ingredient cost to inventory ingredient cost..." << endl;
  for (int i = 0; i < bakeryItems[0].getBakeryItemCount(); i++) {
    for (int j = 0; j < bakeryItems[i].getIngredientCount(); j++) {
      for (int k = 0; k < ingredientInventory[0].getIngredientInventoryCount(); k++) {
        if(bakeryItems[i].getIngredient(j)->getName() == ingredientInventory[k].getIngredient().getName()) {
          cout << "Ingredient " << bakeryItems[i].getIngredient(j)->getName() << "'s cost of " << bakeryItems[i].getBakeryItemName() << " has been set to RM " << ingredientInventory->getIngredientInventoryCost(k) << endl;
          bakeryItems[i].getIngredient(j)->setCostPerUnit(ingredientInventory->getIngredientInventoryCost(k));
        }
      }
    }
  }
}

void Employee::startBakery() {
  cout << "Bakery start operating now." << endl;

  orderNo = 0;

  // @TjeEwe fetch balance from balanceSheet.csv

  ingredientInventory[0] = IngredientInventory("Ingredient 1", 0.0005, 100000.0);
  ingredientInventory[1] = IngredientInventory("Ingredient 2", 20.0, 200);
  ingredientInventory[2] = IngredientInventory("Ingredient 3", 30.0, 0.0);

  bakeryItems->setBakeryItems(bakeryItems);

  // print address of ingredientInventory
  // cout << "Ingredient Inventory address (from employee): " << ingredientInventory << endl;

  int numberOfIngredients;
  Ingredient * ingredient;

  numberOfIngredients = 1;
  bakeryItems[0] = BakeryItem("Item 1", "Description 1", 10.0,
    new Ingredient[numberOfIngredients] {
      Ingredient("Ingredient 1", 0.08, 100.0)
    }, numberOfIngredients, "Recipe 1");
  numberOfIngredients = 3;
  bakeryItems[1] = BakeryItem("Item 2", "Description 2", 20.0,
    new Ingredient[numberOfIngredients] {
      Ingredient("Ingredient 1 of Item 2", 0.005, 200.0),
      Ingredient("Ingredient 2", 2.0, 3),
      Ingredient("Ingredient 3 of Item 2", 0.02, 400.0)
    }, numberOfIngredients, "Recipe 2");
  numberOfIngredients = 1;
  bakeryItems[2] = BakeryItem("Item 3", "Description 3", 30.0,
    new Ingredient[numberOfIngredients] {
      Ingredient("Ingredient 2", 2.0, 3),
    }, numberOfIngredients, "Recipe 3");

  // cout << "Bakery Item Address (from employee): " << bakeryItems << endl;

  discounts = new Discount[Constant::MAX_DISCOUNTS];

  // cout << "Address of discounts (from employee): " << discounts << endl;

  // @TjeEwe need fetch this from file instead
  discounts[0] = Discount("Over RM30 Oasis: Enjoy 5\% Off", 30.0, 5.0, "Description 1", false);
  discounts[1] = Discount("Fifty-Fiver Flourish: 10\% Discount", 50.0, 10.0, "Description 2", false);

  if (supervisor != nullptr) {
    supervisor->startBakery();
  } else if (baker != nullptr) {
    baker->startBakery();
  } else if (cashier != nullptr) {
    cashier->startBakery();
  } else {
    cout << "Not a valid role to start the bakery." << endl;
    exit(EXIT_FAILURE);
  }

  cout << endl;
  this->setIngredientCostToInventoryIngredientCost();
  cout << endl;

  cout << "Selling " << ingredientInventory[0].getIngredientInventoryCount() << " items today." << endl;
}

void Employee::accessMenuList() const {
  cout << role << " - Accessing menu list..." << endl;
  for (int i = 0; i < bakeryItems[0].getBakeryItemCount(); i++) {
    // cout << "Item address: " << &items[i] << endl;
    cout << i+1 << ". " << bakeryItems[i].getBakeryItemName() << endl;
  }
}

void Employee::accessMenuItem(int index) const {
  cout << role << " - Accessing menu details..." << endl;
  accessMenuDetails(bakeryItems[index]);
}

void Employee::accessDiscountList() const {
  // cout << "Address of discounts (from employee): " << discounts << endl;

  cout << role << " - Accessing discount list..." << endl;
  for (int i = 0; i < discounts[0].getDiscountCount(); i++) {
    cout << i+1 << ". " << discounts[i].getName() << endl;
  }
}

void Employee::accessDiscountDetails(int index) const {
  cout << role << " - Accessing discount details..." << endl;
  cout << "Name: " << discounts[index].getName() << endl;
  cout << "Amount: " << discounts[index].getDiscountPercentage() << "%" << endl;
  cout << "Description: " << discounts[index].getDescription() << endl;
  cout << "Active: " << (!discounts[index].getDisabled() ? "Yes" : "No") << endl;
}

void Employee::showTotalDebit() const {
  cout << role << " - Showing total debit..." << endl;
  cout << "Total debit: RM " << totalDebit << endl;
}

void Employee::showTotalCredit() const {
  cout << role << " - Showing total credit..." << endl;
  cout << "Total credit: RM " << totalCredit << endl;
}

void Employee::showTotalProfitPerDay() const {
  cout << role << " - Showing total profit per day..." << endl;
  totalProfitPerDay = getTotalProfitPerDay();
  cout << "Total profit per day: RM " << totalProfitPerDay << endl;
}

void Employee::showTotalBalance() const {
  cout << role << " - Showing total balance..." << endl;
  cout << "Total balance: RM " << totalBalance << endl;
}

void Employee::displayIngredientInventoryList() const {
  if (supervisor != nullptr || baker != nullptr) {
    cout << role << " - Displaying ingredient inventory list..." << endl;
    ingredientInventory->displayIngredientInventoryList();
  } else {
    cout << "Only supervisor or baker can display ingredient inventory list." << endl;
  }
}

void Employee::accessIngredientInventoryDetails(int index) const {
  if (supervisor != nullptr || baker != nullptr) {
    cout << role << " - Accessing ingredient inventory details..." << endl;
    ingredientInventory->accessIngredientInventoryDetails(index); 
  } else {
    cout << "Only supervisor or baker can access ingredient inventory details." << endl;
  }
}

void Employee::checkIngredientInventory() const {
  if (supervisor != nullptr || baker != nullptr) {
    cout << role << " - Checking ingredient inventory..." << endl;
    ingredientInventory->checkIngredientInventory();
  } else {
    cout << "Only supervisor or baker can check ingredient inventory." << endl;
  }
}

void Employee::restockIngredientInventory(int index, double quantity) const {
  if (supervisor != nullptr) {
    cout << role << " - Restocking ingredient inventory..." << endl;
    if (quantity < 0) {
      cout << "Quantity cannot be negative." << endl;
      return;
    }
    double totalCost = ingredientInventory->restockIngredientInventory(index, quantity);
    cout << "Cost of restock: RM " << totalCost << endl;

    // update total credit
    totalCredit += totalCost;

    // cout << "Total credit: RM " << totalCredit << endl;
  } else {
    cout << "Only supervisor can restock ingredient inventory." << endl;
  }
}

void Employee::changeIngredientCost(int index, double cost) {
  if (supervisor != nullptr) {
    cout << role << " - Changing ingredient cost..." << endl;
    if (cost < 0) {
      cout << "Cost cannot be negative." << endl;
      return;
    }
    ingredientInventory->changeIngredientCost(index, cost);

    // update all bakery items ingredient cost
    this->setIngredientCostToInventoryIngredientCost();
  } else {
    cout << "Only supervisor can change ingredient cost." << endl;
  }
};

void Employee::addNewInventoryIngredientWeight(string name, double cost, double weight) const {
  if (supervisor != nullptr) {
    cout << role << " - Adding new inventory ingredient (weight)..." << endl;
    // name cannot be empty
    if (name == "") {
      cout << "Name cannot be empty." << endl;
      return;
    }
    // cost cannot be negative
    if (cost < 0) {
      cout << "Cost cannot be negative." << endl;
      return;
    }
    // weight cannot be negative
    if (weight < 0) {
      cout << "Weight cannot be negative." << endl;
      return;
    }
    ingredientInventory->addNewInventoryIngredientWeight(name, cost, weight);
  } else {
    cout << "Only supervisor can add new inventory ingredient." << endl;
  }
}

void Employee::addNewInventoryIngredientPiece(string name, double cost, int piece) const {
  if (supervisor != nullptr) {
    cout << role << " - Adding new inventory ingredient (piece)..." << endl;
    // name cannot be empty
    if (name == "") {
      cout << "Name cannot be empty." << endl;
      return;
    }
    // cost cannot be negative
    if (cost < 0) {
      cout << "Cost cannot be negative." << endl;
      return;
    }
    // piece cannot be negative
    if (piece < 0) {
      cout << "Piece cannot be negative." << endl;
      return;
    }
    ingredientInventory->addNewInventoryIngredientPiece(name, cost, piece);
  } else {
    cout << "Only supervisor can add new inventory ingredient." << endl;
  }
}

void Employee::getAllInventoryIngredientName() const {
  cout << "Getting all ingredient inventory names..." << endl;
  for (int i = 0; i < ingredientInventory->getIngredientInventoryCount(); i++) {
    cout << i+1 << ". " << ingredientInventory->getIngredientInventoryName(i) << endl;
  }
}

// @AeroRin input validation
void Employee::createBakeryItem() {
  // show address of bakeryItems
  // cout << "Bakery Item Address (from employee): " << bakeryItems << endl;

  if (supervisor != nullptr) {
    cout << role << " - Creating bakery item..." << endl;

    // create bakery items from user input
    string bakeryItemName;
    string bakeryItemDescription;
    double bakeryItemPricePerUnit;
    int numberOfIngredients;
    Ingredient * ingredient;
    string recipe;

    cout << "Enter bakery item name: ";
    getline(cin, bakeryItemName);
    cout << "Enter bakery item description: ";
    getline(cin, bakeryItemDescription);
    cout << "Enter bakery item price per unit: RM ";
    cin >> bakeryItemPricePerUnit;
    cin.ignore();
    cout << "Enter number of ingredients: ";
    cin >> numberOfIngredients;

    ingredient = new Ingredient[numberOfIngredients];
    for (int i = 0; i < numberOfIngredients; i++) {
      string ingredientName;
      double ingredientCost = 0;
      double ingredientWeight;
      int ingredientPiece;
      bool countable;

      char countableInput;

      cout << "--- Ingredient " << i+1 << " ---" << endl;

      cin.ignore();
      cout << "Enter ingredient name: ";
      getline(cin, ingredientName);


      // find ingredient name from ingredient inventory, if found, use the cost
      for (int j = 0; j < ingredientInventory->getIngredientInventoryCount(); j++) {
        if (ingredientName ==  ingredientInventory->getIngredientInventoryName(j)) {
          cout << ingredientName << " found in inventory." << endl;
          cout << "Cost: RM " << ingredientInventory->getIngredientInventoryCost(j);
          if (ingredientInventory[j].getIngredient().getCountable()) {
            cout << " / piece(s)." << endl;
          } else {
            cout << " / gram(s)." << endl;
          }
          ingredientCost = ingredientInventory->getIngredientInventoryCost(j);

          if (ingredientInventory[j].getCountable()) {
            cout << "Enter ingredient piece: ";
            cin >> ingredientPiece;
            ingredient[i] = Ingredient(ingredientName, ingredientCost, ingredientPiece);
          } else {
            cout << "Enter ingredient weight in gram(s): ";
            cin >> ingredientWeight;
            ingredient[i] = Ingredient(ingredientName, ingredientCost, ingredientWeight);
          }
        }
      }

      // if ingredient name not found in inventory, ask user to input cost
      if (ingredientCost == 0) {
        cout << "Enter ingredient cost: RM ";
        cin >> ingredientCost;

        // ask user is the ingredient in piece or weight
        do {
          cout << "Enter ingredient piece or weight (0 for weight, 1 for piece): ";
          cin >> countableInput;
        } while (countableInput != '0' && countableInput != '1');

        countable = (countableInput == '1');

        if (countable) {
          cout << "Enter ingredient piece: ";
          cin >> ingredientPiece;
          ingredient[i] = Ingredient(ingredientName, ingredientCost, ingredientPiece);

          // add new ingredient to ingredient inventory
          ingredientInventory->addNewInventoryIngredientPiece(ingredientName, ingredientCost, ingredientPiece);
        } else {
          cout << "Enter ingredient weight in gram(s): ";
          cin >> ingredientWeight;
          ingredient[i] = Ingredient(ingredientName, ingredientCost, ingredientWeight);

          // add new ingredient to ingredient inventory
          ingredientInventory->addNewInventoryIngredientWeight(ingredientName, ingredientCost, ingredientWeight);
        }
      }
    }

    // enable user to type multiline recipe
    cout << "Enter recipe (press CTRL+Z then Enter on Windows, or CTRL+D on Unix, to exit): " << endl;
    cin.ignore();
    string line;
    while (getline(cin, line)) {
      if (cin.eof()) {
        break;
      }
      recipe += line + "\n";
    }

    bakeryItems[bakeryItems->getBakeryItemCount()] = BakeryItem(bakeryItemName, bakeryItemDescription, bakeryItemPricePerUnit, ingredient, numberOfIngredients, recipe);
    // @TjeEwe file handling for new bakery item

    // cout << "Bakery Item Address (from employee): " << bakeryItems << endl;
    
  } else {
    cout << "Only supervisor can create bakery item." << endl;
  }
}

void Employee::withdrawBakeryItem (int index) {
  if (supervisor != nullptr) {
    cout << role << " - Withdrawing " << bakeryItems[index].getBakeryItemName() << "..." << endl;
    bakeryItems[index].setDisabled(true);
    cout << bakeryItems[index].getBakeryItemName() << " has been withdrawn." << endl;
  } else {
    cout << "Only supervisor can withdraw bakery item." << endl;
  }
}

void Employee::enableBakeryItem (int index) {
  if (supervisor != nullptr) {
    cout << role << " - Enabling " << bakeryItems[index].getBakeryItemName() << "..." << endl;
    bakeryItems[index].setDisabled(false);
    cout << bakeryItems[index].getBakeryItemName() << " has been enabled." << endl;
  } else {
    cout << "Only supervisor can enable bakery item." << endl;
  }
}

void Employee::changeBakeryItemPrice(int index, double newPrice) {
  if (supervisor != nullptr) {
    cout << role << " - Changing " << bakeryItems[index].getBakeryItemName() << " price..." << endl;
    bakeryItems[index].setPricePerUnit(newPrice);
    cout << setprecision(2) << fixed;
    cout << bakeryItems[index].getBakeryItemName() << " price has been changed to RM " << newPrice << "." << endl;
  } else {
    cout << "Only supervisor can change bakery item price." << endl;
  }
}

void Employee::calculateBakeryItemCost(int index) const {
  cout << role << " - Calculating " << bakeryItems[index].getBakeryItemName() << " cost..." << endl;
  cout << setprecision(2) << fixed;
  cout << "Total cost: RM " << bakeryItems[index].calculateCost() << endl;
}

void Employee::calculateBakeryItemProfit(int index) const {
  cout << role << " - Calculating " << bakeryItems[index].getBakeryItemName() << " profit..." << endl;
  cout << setprecision(2) << fixed;
  cout << "Total profit: RM " << bakeryItems[index].calculateProfit() << endl;
}

void Employee::compareCostVsProfit(int index) const {
  cout << role << " - Comparing " << bakeryItems[index].getBakeryItemName() << " cost vs profit..." << endl;
  cout << setprecision(2) << fixed;
  cout << "Total cost: RM " << bakeryItems[index].calculateCost() << endl;
  cout << "Total profit: RM " << bakeryItems[index].calculateProfit() << endl;

  // percentage
  cout << setprecision(2) << fixed;
  cout << "Profit percentage: " << (bakeryItems[index].calculateProfit() / bakeryItems[index].calculateCost()) * 100 << "%" << endl;
}

void Employee::compareCostVsPrice(int index) const {
  cout << role << " - Comparing " << bakeryItems[index].getBakeryItemName() << " cost vs price..." << endl;
  cout << setprecision(2) << fixed;
  cout << "Total cost: RM " << bakeryItems[index].calculateCost() << endl;
  cout << "Price per unit: RM " << bakeryItems[index].getPricePerUnit() << endl;

  // percentage
  cout << setprecision(2) << fixed;
  cout << "Price percentage: " << (bakeryItems[index].getPricePerUnit() / bakeryItems[index].calculateCost()) * 100 << "%" << endl;
}

// @TjeEwe file handling if new employee is created
// update employeeData.csv
void Employee::createNewEmployee(Employee * employees, string employeeID, string name, string role) {
  if (supervisor != nullptr) {
    cout << this->role << " - Creating new employee..." << endl;

    // check if name is empty
    if (name == "") {
      cout << "Name cannot be empty." << endl;
      return;
    }

    // check if employee id is empty
    if (employeeID == "") {
      cout << "Employee ID cannot be empty." << endl;
      return;
    }

    // check if role is empty
    if (role == "") {
      cout << "Role cannot be empty." << endl;
      return;
    }

    bool employeeCreated = false;
    for (int i = 0; i < Constant::MAX_EMPLOYEES; i++) {
      // employee id is not unique
      if (employees[i].employeeID == employeeID) {
        cout << "Warning: Employee ID is not unique." << endl;
        return;
      }

      if (employees[i].employeeID == "") {
        cout << role << " " << name << " created successfully." << endl;
        cout << "at index " << i << " of " << &employees[i] << endl;
        // employees[i] = Employee(employeeID, name, role);

        employees[i].employeeID = employeeID;
        employees[i].name = name;
        employees[i].role = role;

        if (role == "Supervisor") {
          employees[i].supervisor = new Supervisor(employeeID, name);
        } else if (role == "Baker") {
          employees[i].baker = new Baker(employeeID, name);
        } else {
          employees[i].cashier = new Cashier(employeeID, name);
        }

        employeeCreated = true;

        employees[i].displayEmployeeDetails();
        break;
      }
    }

    if (!employeeCreated) {
      cout << "Warning: Maximum number of employees reached." << endl;
    }

  } else {
    cout << "Only supervisor can create new employee." << endl;
  }
}

// @TjeEwe file handling if employee role is changed
void Employee::changeEmployeeRole (Employee employees [], int index, string role) {
  if (supervisor != nullptr) {
    cout << this->role << " - Changing employee role..." << endl;

    // check if role is empty
    if (role == "") {
      cout << "Role cannot be empty." << endl;
      return;
    }

    // check if employee id is empty
    if (employees[index].employeeID == "") {
      cout << "Employee ID cannot be empty." << endl;
      return;
    }

    // check if name is empty
    if (employees[index].name == "") {
      cout << "Name cannot be empty." << endl;
      return;
    }

    // cannot change own role
    if (employeeID == employees[index].employeeID) {
      cout << "Warning: Cannot change own role." << endl;
      return;
    }

    // cannot change supervisor role
    if (employees[index].role == "Supervisor") {
      cout << "Warning: Cannot change supervisor role." << endl;
      return;
    }

    // role is the same
    if (employees[index].role == role) {
      cout << employees[index].name << "'s role is already " << role << "." << endl;
      return;
    }

    employees[index].role = role;
    cout << employees[index].name << "'s role has been changed to " << role << "." << endl;
  } else {
    cout << "Only supervisor can change employee role." << endl;
  }
}

void Employee::displayAllEmployeeDetails(Employee employees []) const {
  if (supervisor != nullptr) {
    cout << role << " - Displaying all employee details..." << endl;
    cout << "+---+--------------------+--------------------+--------------------+" << endl;
    cout << "| " << left << setw(2) << "No" << "| ";
    cout << left << setw(19) << "Name" << "| ";
    cout << left << setw(19) << "Position" << "| ";
    cout << left << setw(19) << "Employee ID" << "|" << endl;
    cout << "+---+--------------------+--------------------+--------------------+" << endl;
    for (int i = 0; i < Constant::MAX_EMPLOYEES; i++) {
      if (employees[i].employeeID != "") {
        cout << "| " << left << setw(2) << i+1 << "| ";
        cout << left << setw(19) << employees[i].name << "| ";
        cout << left << setw(19) << employees[i].role << "| ";
        cout << left << setw(19) << employees[i].employeeID << "|" << endl;
      }
    }
    cout << "+---+--------------------+--------------------+--------------------+" << endl;
  } else {
    cout << "Only supervisor can display all employee details." << endl;
  }
}

// @TjeEwe file handling if employee is deleted
void Employee::deleteEmployee(Employee employees [], int index) {
  if (supervisor != nullptr) {
    cout << role << " - Deleting employee..." << endl;

    // check if employee id is empty
    if (employees[index].employeeID == "") {
      cout << "Employee ID cannot be empty." << endl;
      return;
    }

    // check if name is empty
    if (employees[index].name == "") {
      cout << "Name cannot be empty." << endl;
      return;
    }

    // cannot delete own account
    if (employeeID == employees[index].employeeID) {
      cout << "Warning: Cannot delete own account." << endl;
      return;
    }

    // cannot delete supervisor account
    if (employees[index].role == "Supervisor") {
      cout << "Warning: Cannot delete supervisor account." << endl;
      return;
    }

    cout << employees[index].role << " " << employees[index].name << " has been deleted." << endl;

    employees[index].name = "";
    employees[index].role = "";
    employees[index].employeeID = "";
    employees[index].supervisor = nullptr;
    employees[index].baker = nullptr;
    employees[index].cashier = nullptr;
  } else {
    cout << "Only supervisor can delete employee." << endl;
  }
}

// @TjeEwe file handling if new discount is created
// @AeroRin input validation
void Employee::addNewDiscount() {
  if (supervisor != nullptr) {
    cout << role << " - Adding new discount..." << endl;

    // create discounts from user input
    string discountName;
    double minimumPurchase;
    double discountPercentage;
    string discountDescription;
    bool disabled;

    cout << "Enter discount name: ";
    getline(cin, discountName);
    cout << "Enter minimum purchase amount: RM ";
    cin >> minimumPurchase;
    cout << "Enter discount percentage (%): ";
    cin >> discountPercentage;
    cin.ignore();
    cout << "Enter discount description: ";
    getline(cin, discountDescription);
    cout << "Is the discount available now? (Y/N): ";
    char available;
    cin >> available;
    disabled = (available == 'N' || available == 'n');  

    for (int i = 0; i < Constant::MAX_DISCOUNTS; i++) {
      if (discounts[i].getName() == "") {
        discounts[i] = Discount(discountName, minimumPurchase, discountPercentage, discountDescription, disabled);
        cout << "Discount '" << discountName << "' has been added." << endl;
        return;
      }
    }

    cout << "Warning: Maximum number of discounts reached." << endl;
  } else {
    cout << "Only supervisor can add new discount." << endl;
  }
}

void Employee::editDiscountName(int index, string newName) {
  if (supervisor != nullptr) {
    cout << role << " - Editing discount name..." << endl;
    discounts[index].setName(newName);
    cout << "Name has been updated to '" << discounts[index].getName() << "'" << endl;
  } else {
    cout << "Only supervisor can edit discount name." << endl;
  }
}

void Employee::editDiscountPercentage(int index, double newPercentage) {
  if (supervisor != nullptr) {
    cout << role << " - Editing discount percentage..." << endl;
    discounts[index].setDiscountPercentage(newPercentage);
    cout << "Percentage has been updated for discount '" << discounts[index].getName() << "'." << endl;
  } else {
    cout << "Only supervisor can edit discount percentage." << endl;
  }
}

void Employee::editDiscountDescription(int index, string newDescription) {
  if (supervisor != nullptr) {
    cout << role << " - Editing discount description..." << endl;
    discounts[index].setDescription(newDescription);
    cout << "Description has been updated for '" << discounts[index].getName() << "'." << endl;
  } else {
    cout << "Only supervisor can edit discount description." << endl;
  }
}

void Employee::disableDiscount(int index) {
  if (supervisor != nullptr) {
    cout << role << " - Disabling discount..." << endl;
    discounts[index].setDisabled(true);
    cout << "'" << discounts[index].getName() << "' has been disabled." << endl;
  } else {
    cout << "Only supervisor can disable discount." << endl;
  }
}

void Employee::enableDiscount(int index) {
  if (supervisor != nullptr) {
    cout << role << " - Enabling discount..." << endl;
    discounts[index].setDisabled(false);
    cout << "'" << discounts[index].getName() << "' has been enabled." << endl;
  } else {
    cout << "Only supervisor can enable discount." << endl;
  }
}

// @TjeEwe file handling if new bakery item is created
// deduct ingredients from inventory
void Employee::bakeNewBakeryItem(int index, int quantity) {
  if (baker != nullptr) {
    cout << role << " - Baking " << quantity << "x " << bakeryItems[index].getBakeryItemName() << "..." << endl;
    // check if bakery item is disabled
    if (bakeryItems[index].getDisabled()) {
      cout << "Warning: " << bakeryItems[index].getBakeryItemName() << " is withdrawn." << endl;
      return;
    }

    // check if ingredient is enough
    bool foundIngredient;
    int * ingredientInventoryIndex = new int[MAX_INGREDIENTS];
    for (int i = 0; i < bakeryItems[index].getIngredientCount(); i++) {
      foundIngredient = false;
      for (int j = 0; j < ingredientInventory->getIngredientInventoryCount(); j++) {
        // cout << bakeryItems[index].getIngredient(i)->getName() << " " << ingredientInventory->getIngredientInventoryName(j) << endl;
        if (bakeryItems[index].getIngredient(i)->getName() == ingredientInventory->getIngredientInventoryName(j)) {
          cout << "Ingredient " << bakeryItems[index].getIngredient(i)->getName() << " found in inventory." << endl;
          if (bakeryItems[index].getIngredient(i)->getCountable()) {
            if (bakeryItems[index].getIngredient(i)->getPiece() * quantity > ingredientInventory->getIngredientInventoryPiece(j)) {
              cout << "Not enough " << bakeryItems[index].getIngredient(i)->getName() << " in inventory." << endl;
              cout << "Available: " << ingredientInventory->getIngredientInventoryPiece(j) << " piece(s)." << endl;
              cout << "Require " << bakeryItems[index].getIngredient(i)->getPiece() * quantity << " piece(s)." << endl;
              return;
            } else {
              cout << "Enough " << bakeryItems[index].getIngredient(i)->getName() << " in inventory." << endl;
              ingredientInventoryIndex[i] = j;
              foundIngredient = true;
              break;
            }
          } else {
            if (bakeryItems[index].getIngredient(i)->getWeight() * quantity > ingredientInventory->getIngredientInventoryWeight(j)) {
              cout << "Not enough " << bakeryItems[index].getIngredient(i)->getName() << " in inventory." << endl;
              cout << "Available: " << ingredientInventory->getIngredientInventoryWeight(j) << " gram(s)." << endl;
              cout << "Require " << bakeryItems[index].getIngredient(i)->getWeight() * quantity << " gram(s)." << endl;
              return;
            } else {
              cout << "Enough " << bakeryItems[index].getIngredient(i)->getName() << " in inventory." << endl;
              ingredientInventoryIndex[i] = j;
              foundIngredient = true;
              break;
            }
          }
        }
      }

      // check if ingredient is not found in inventory
      if (!foundIngredient) {
        cout << "Warning: Ingredient " << bakeryItems[index].getIngredient(i)->getName() << " not found in inventory." << endl;
        cout << "Please restock ingredient " << bakeryItems[index].getIngredient(i)->getName() << " before baking." << endl;
        return;
      }

      // check if ingredient is not found in inventory
      // if ((i == bakeryItems[index].getIngredientCount() - 1) && (bakeryItems[index].getIngredient(i)->getName() != ingredientInventory->getIngredientInventoryName(i))){
      //   cout << "Warning: Ingredient " << bakeryItems[index].getIngredient(i)->getName() << " not found in inventory." << endl;
      //   cout << "Please restock ingredient " << bakeryItems[index].getIngredient(i)->getName() << " before baking." << endl;
      //   return;
      // }

      // deduct ingredients from inventory
      if (i == bakeryItems[index].getIngredientCount() - 1) {
        for (int i = 0; i < bakeryItems[index].getIngredientCount(); i++) {
          if (bakeryItems[index].getIngredient(i)->getCountable()) {
            ingredientInventory->setIngredientInventoryPiece(ingredientInventoryIndex[i], ingredientInventory->getIngredientInventoryPiece(ingredientInventoryIndex[i]) - bakeryItems[index].getIngredient(i)->getPiece() * quantity);
            cout << bakeryItems[index].getIngredient(i)->getPiece() * quantity << " pieces of ingredient " << bakeryItems[index].getIngredient(i)->getName() << " has been used." << endl;
            cout << "Remaining: " << ingredientInventory->getIngredientInventoryPiece(ingredientInventoryIndex[i]) << " pieces." << endl;
          } else {
            ingredientInventory->setIngredientInventoryWeight(ingredientInventoryIndex[i], ingredientInventory->getIngredientInventoryWeight(ingredientInventoryIndex[i]) - bakeryItems[index].getIngredient(i)->getWeight() * quantity);
            cout << bakeryItems[index].getIngredient(i)->getWeight() * quantity << " gram(s) of ingredient " << bakeryItems[index].getIngredient(i)->getName() << " has been used." << endl;
            cout << "Remaining: " << ingredientInventory->getIngredientInventoryWeight(ingredientInventoryIndex[i]) << " gram(s)." << endl;
          }
        }
      }

      // add bakery item quantity
      bakeryItems[index].setBakeryItemQuantity(bakeryItems[index].getBakeryItemQuantity() + quantity);

    }
    cout << quantity << "x bakery item " << bakeryItems[index].getBakeryItemName() << " has been baked." << endl;
  } else {
    cout << "Only baker can bake bakery item." << endl;
  }
}

void Employee::addBakeryItemToCart (int index, int quantity) {
  cout << role << " - Adding " << quantity << "x " << bakeryItems[index].getBakeryItemName() << " to cart..." << endl;
  if (cashier != nullptr) {
    // check if bakery item is disabled
    if (bakeryItems[index].getDisabled()) {
      cout << "Warning: " << bakeryItems[index].getBakeryItemName() << " is withdrawn." << endl;
      return;
    }

    // check if bakery item is enough
    if (bakeryItems[index].getBakeryItemQuantity() < quantity) {
      cout << "Warning: Not enough " << bakeryItems[index].getBakeryItemName() << " in inventory." << endl;
      cout << "Available: " << bakeryItems[index].getBakeryItemQuantity() << " item(s)." << endl;
      cout << "Require " << quantity << " item(s)." << endl;
      return;
    }

    cashier->getCart()->addBakeryItemToCart(bakeryItems[index], quantity);
    cout << quantity << "x " << bakeryItems[index].getBakeryItemName() << " has been added to cart." << endl;
  } else {
    cout << "Only cashier can add bakery item to cart." << endl;
  }
}

void Employee::displayCartDetails () const {
  if (cashier != nullptr) {
    cout << "Cashier " << name << " (" << employeeID << ") - Displaying cart details..." << endl;
    cashier->getCart()->displayCartDetails();
  } else {
    cout << "Only cashier can display cart details." << endl;
  }
}

void Employee::calculateCartTotalCost () const {
  if (cashier != nullptr) {
    cout << "Cashier " << name << " (" << employeeID << ") - Calculating total cost..." << endl;
    cout << setprecision(2) << fixed;
    cout << "Total cost: RM " << cashier->getCart()->calculateTotalCost() << endl;
  } else {
    cout << "Only cashier can calculate total cost." << endl;
  }
}

void Employee::calculateCartTotalPrice () const {
  if (cashier != nullptr) {
    cout << "Cashier " << name << " (" << employeeID << ") - Calculating total price..." << endl;
    cout << setprecision(2) << fixed;
    cout << "Total price: RM " << cashier->getCart()->calculateTotalPrice() << endl;
  } else {
    cout << "Only cashier can calculate total price." << endl;
  }
}

void Employee::calculateCartTotalProfit () const {
  if (cashier != nullptr) {
    cout << "Cashier " << name << " (" << employeeID << ") - Calculating total profit..." << endl;
    cout << setprecision(2) << fixed;
    cout << "Total profit: RM " << cashier->getCart()->calculateTotalProfit() << endl;
  } else {
    cout << "Only cashier can calculate total profit." << endl;
  }
}

void Employee::getCartItemCount() const {
  if (cashier != nullptr) {
    cout << "Cashier " << name << " (" << employeeID << ") - Getting cart item count..." << endl;
    cout << "Cart item count: " << cashier->getCart()->getCartItemCount() << endl;
  } else {
    cout << "Only cashier can get cart item count." << endl;
  }
}

void Employee::removeBakeryItemFromCart (int index) {
  if (cashier != nullptr) {
    cout << "Removing " << cashier->getCart()->getBakeryItems()[index].getBakeryItemName() << " from cart..." << endl;
    cashier->getCart()->removeBakeryItemFromCart(index);
    cout << cashier->getCart()->getBakeryItems()[index].getBakeryItemName() << " removed from cart." << endl;
  } else {
    cout << "Only cashier can remove bakery item from cart." << endl;
  }
}

void Employee::updateBakeryItemQuantityInCart(int index, int quantity) {
  if (cashier != nullptr) {
    cout << "Editing " << cashier->getCart()->getBakeryItems()[index].getBakeryItemName() << " quantity in cart..." << endl;
    cashier->getCart()->updateBakeryItemQuantity(index, quantity);
    cout << cashier->getCart()->getBakeryItems()[index].getBakeryItemName() << " quantity in cart has been changed to " << quantity << "." << endl;
  } else {
    cout << "Only cashier can edit bakery item quantity in cart." << endl;
  }
}

void Employee::clearCart() {
  if (cashier != nullptr) {
    cout << "Clearing cart..." << endl;
    cashier->getCart()->clearCart();
    cout << "Cart has been cleared." << endl;
  } else {
    cout << "Only cashier can clear cart." << endl;
  }
}

void Employee::showDiscountBasedOnCartTotalPrice() const {
  if (cashier != nullptr) {
    cout << "Cashier " << name << " (" << employeeID << ") - Showing available discount based on cart total price..." << endl;
    bool isDiscountAvailable = false;
    for (int i = 0; i < discounts->getDiscountCount(); i++) {
      if (cashier->getCart()->calculateTotalPrice() >= discounts[i].getMinimumPurchase()) {
        cout << i+1 << ". " << discounts[i].getName() << endl;
        isDiscountAvailable = true;
      }
    }
    // check if no discount available
    if (!isDiscountAvailable) {
      cout << "- Purchase doesn't qualify for discount. -" << endl;
    }
    if (discounts->getDiscountCount() == 0) {
      cout << "No discount available." << endl;
    }
  } else {
    cout << "Only cashier can show discount based on cart total price." << endl;
  }
}

void Employee::applyDiscount(int choice) {
  // find the index corresponding to the choice according to option in showDiscountBasedOnCartTotalPrice()
  bool isDiscountAvailable = false;
  Discount* availableDiscounts[discounts->getDiscountCount()];
  int count = 0;
  for (int i = 0; i < discounts->getDiscountCount(); i++) {
    if (cashier->getCart()->calculateTotalPrice() >= discounts[i].getMinimumPurchase()) {
      isDiscountAvailable = true;
      if (count < discounts->getDiscountCount()) {
        availableDiscounts[count++] = &discounts[i];
      }
    }
  }

  if (choice > count) {
    cout << "Invalid choice." << endl;
    return;
  }

  if (cashier != nullptr) {
    cout << "Applying discount..." << endl;
    if (cashier->getCart()->calculateTotalPrice() >= availableDiscounts[choice - 1]->getMinimumPurchase()) {
      cout << "Discount applied: " << availableDiscounts[choice - 1]->getName() << endl;
      cout << "Discount amount: " << availableDiscounts[choice - 1]->getDiscountPercentage() << "%" << endl;
      cashier->getCart()->setTotalDiscount(cashier->getCart()->calculateTotalPrice() * (availableDiscounts[choice - 1]->getDiscountPercentage() / 100));
      cout << "Discount amount: RM " << cashier->getCart()->getTotalDiscount() << endl;
    } else {
      cout << "Warning: Purchase doesn't qualify for discount." << endl;
    }
    cout << endl;
  } else {
    cout << "Only cashier can apply discount." << endl;
  }
}

double Employee::calculateDiscountedTotalPrice () const {
  if (cashier != nullptr) {
    cout << "Calculating discounted price..." << endl;
    cout << setprecision(2) << fixed;
    cout << "Discounted price: RM " << cashier->getCart()->calculateTotalPrice() - cashier->getCart()->getTotalDiscount() << endl;
    return cashier->getCart()->calculateTotalPrice() - cashier->getCart()->getTotalDiscount();
  } else {
    cout << "Only cashier can calculate discounted price." << endl;
    return 0;
  }
}

// @TjeEwe store the transaction details to csv file
// and create receipt txt file
void Employee::checkout() {
  if (cashier != nullptr) {
    cout << "Checking out..." << endl;

    // deduct bakery items in cart from bakery
    for (int i = 0; i < cashier->getCart()->getCartItemCount(); i++) {
      for (int j = 0; j < bakeryItems->getBakeryItemCount(); j++) {
        if (cashier->getCart()->getBakeryItems()[i].getBakeryItemName() == bakeryItems[j].getBakeryItemName()) {
          cout << endl;
          cout << "Checking out " << cashier->getCart()->getQuantity()[i] << "x " << cashier->getCart()->getBakeryItems()[i].getBakeryItemName() << "..." << endl;
          // check if bakery item is enough
          if (bakeryItems[j].getBakeryItemQuantity() < cashier->getCart()->getQuantity()[i]) {
            cout << "Warning: Not enough " << bakeryItems[j].getBakeryItemName() << " in bakery." << endl;
            cout << "Available: " << bakeryItems[j].getBakeryItemQuantity() << " bakery item(s)." << endl;
            cout << "Require " << cashier->getCart()->getQuantity()[i] << " bakery item(s)." << endl;

            // ask user to skip buying
            cout << "Do you want to skip buying this item? (Y/N): ";
            char skip;
            cin >> skip;
            if (skip == 'Y' || skip == 'y') {
              // remove this item from cart
              cashier->getCart()->removeBakeryItemFromCart(i);
              cout << bakeryItems[j].getBakeryItemQuantity() << "x " << bakeryItems[j].getBakeryItemName() << " has been removed from cart." << endl;
              continue;
            } else {
              cout << "Please inform supervisor to restock bakery item " << bakeryItems[j].getBakeryItemName() << " before checkout." << endl;
              return;
            }
          }

          cout << "Total price: RM " << cashier->getCart()->calculateTotalPrice() << endl;

          // deduct bakery item quantity from bakery
          bakeryItems[j].setBakeryItemQuantity(bakeryItems[j].getBakeryItemQuantity() - cashier->getCart()->getQuantity()[i]);
          cout << cashier->getCart()->getQuantity()[i] << "x " << cashier->getCart()->getBakeryItems()[i].getBakeryItemName() << " has been deducted from bakery." << endl;
        }
      }
    }
    orderNo++;

    cout << "Order No: " << orderNo << endl;

    cout << "Please reconfirm your cart: " << endl;
    this->displayCartDetails();
    cout << endl;

    // exit from empty cart
    if (cashier->getCart()->getCartItemCount() == 0) {
      cout << "Cart is empty. Please add bakery items to cart before checkout." << endl;
      return;
    }

    // @AeroRin input validation
    // exit from checking out if want to cancel
    cout << "Do you want to proceed? (Y/N): ";
    char proceed;
    cin >> proceed;
    if (proceed == 'N' || proceed == 'n') {
      cout << "Checkout has been cancelled." << endl;
      return;
    }

    // apply discount
    this->showDiscountBasedOnCartTotalPrice();
    cout << endl;
    cout << "Enter discount choice (0 to skip): ";
    int choice;
    cin >> choice;
    cout << endl;
    if (choice != 0) {
      this->applyDiscount(choice);
    }

    // calculate total price
    double totalPrice = this->calculateDiscountedTotalPrice();
    totalPrice = round(totalPrice * 100) / 100;
    cout << "Total price: RM " << totalPrice << endl;
    cout << endl;

    // update total debit
    // total price is after discount
    totalDebit += totalPrice;
    // cout << "Total debit: RM " << totalDebit << endl;

    // WIP: update total profit per day, total credit, total debit

    cout << "Thank you for shopping with us!" << endl;

    // @TjeEwe store transaction details to csv file
    // store transaction details to csv file
    // generate receipt txt file

    cashier->getCart()->clearCart();
  } else {
    cout << "Only cashier can checkout." << endl;
  }
}

void Employee::showReceipt(int orderNo) const {
  // read from receipts/receipt-20240510-1.txt
  // string receiptFileName = "receipts/receipt-" + to_string(Constant::CURRENT_DATE) + "-" + to_string(orderNo) + ".txt";

}

string Employee::getEmployeeID() const {
  return employeeID;
}

string Employee::getName() const {
  return name;
}

string Employee::getRole() const {
  return role;
}

int Employee::getOrderNo() const {
  return orderNo;
}

double Employee::getTotalBalance() const {
  return totalBalance;
}

double Employee::getTotalCredit() const {
  return totalCredit;
}

double Employee::getTotalDebit() const {
  return totalDebit;
}

double Employee::getTotalProfitPerDay() const {
  return totalDebit - totalCredit;
}

Employee::~Employee() {
  delete discounts;

  delete supervisor;
  delete baker;
  delete cashier;
  // cout << "Employee " << name << " has been removed." << endl;
}

IngredientInventory * Employee::ingredientInventory = new IngredientInventory[MAX_INGREDIENTS_INVENTORY];
BakeryItem * Employee::bakeryItems = new BakeryItem[MAX_BAKERY_ITEMS];
// Discount * Employee::discounts = new Discount[Constant::MAX_DISCOUNTS];
Discount * Employee::discounts = nullptr;
int Employee::orderNo = 0;
double Employee::totalBalance = 5000;
double Employee::totalCredit = 0;
double Employee::totalDebit = 0;
double Employee::totalProfitPerDay = 0;