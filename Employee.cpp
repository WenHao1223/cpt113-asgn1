#include <iomanip>

#include "Constant.h"
#include "Employee.h"
#include "BakeryItem.h"

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

void Employee::startBakery() const {
  cout << "Bakery start operating now." << endl;

  ingredientInventory[0] = IngredientInventory("Ingredient 1", 0.0005, 100000.0);
  ingredientInventory[1] = IngredientInventory("Ingredient 2", 20.0, 200);
  ingredientInventory[2] = IngredientInventory("Ingredient 3", 30.0, 0.0);

  bakeryItems->setBakeryItems(bakeryItems);

  // print address of ingredientInventory
  cout << "Ingredient Inventory address (from employee): " << ingredientInventory << endl;

  int numberOfIngredients;
  Ingredient * ingredient;

  numberOfIngredients = 1;
  bakeryItems[0] = BakeryItem("Item 1", "Description 1", 10.0,
    new Ingredient[numberOfIngredients] {
      Ingredient("Ingredient 1", 1.0, 100.0)
    }, numberOfIngredients, "Recipe 1");
  numberOfIngredients = 3;
  bakeryItems[1] = BakeryItem("Item 2", "Description 2", 20.0,
    new Ingredient[numberOfIngredients] {
      Ingredient("Ingredient 1 of Item 2", 0.005, 200.0),
      Ingredient("Ingredient 2", 2.0, 3),
      Ingredient("Ingredient 3 of Item 2", 0.02, 400.0)
    }, numberOfIngredients, "Recipe 2");

  // cout << "Bakery Item Address (from employee): " << bakeryItems << endl;

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
    (ingredientInventory+index)->accessIngredientInventoryDetails();
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

void Employee::restockIngredientInventory(int index, int quantity) const {
  if (supervisor != nullptr) {
    cout << role << " - Restocking ingredient inventory..." << endl;
    if (quantity < 0) {
      cout << "Quantity cannot be negative." << endl;
      return;
    }
    ingredientInventory->restockIngredientInventory(index, quantity);
  } else {
    cout << "Only supervisor can restock ingredient inventory." << endl;
  }
}

void Employee::changeIngredientCost(int index, double cost) const {
  if (supervisor != nullptr) {
    cout << role << " - Changing ingredient cost..." << endl;
    if (cost < 0) {
      cout << "Cost cannot be negative." << endl;
      return;
    }
    ingredientInventory->changeIngredientCost(index, cost);
  } else {
    cout << "Only supervisor can change ingredient cost." << endl;
  }
};

void Employee::getAllInventoryIngredientName() const {
  cout << "Getting all ingredient inventory names..." << endl;
  for (int i = 0; i < ingredientInventory->getIngredientInventoryCount(); i++) {
    cout << i+1 << ". " << ingredientInventory->getIngredientInventoryName(i) << endl;
  }
}

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
          cout << "Ingredient found in inventory." << endl;
          cout << "Cost: RM " << ingredientInventory->getIngredientInventoryCost(j) << endl;
          cout << "Do you want to use this cost? (Y/N): ";
          char useCost;
          cin >> useCost;
          if (useCost == 'Y' || useCost == 'y') {
            ingredientCost = ingredientInventory->getIngredientInventoryCost(j);
          } else {
            cout << "Enter ingredient cost: RM ";
            cin >> ingredientCost;
          }

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
        } else {
          cout << "Enter ingredient weight in gram(s): ";
          cin >> ingredientWeight;
          ingredient[i] = Ingredient(ingredientName, ingredientCost, ingredientWeight);
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
  } else {
    cout << "Only supervisor can withdraw bakery item." << endl;
  }
}

void Employee::enableBakeryItem (int index) {
  if (supervisor != nullptr) {
    cout << role << " - Enabling " << bakeryItems[index].getBakeryItemName() << "..." << endl;
    bakeryItems[index].setDisabled(false);
  } else {
    cout << "Only supervisor can enable bakery item." << endl;
  }
}

void Employee::changeBakeryItemPrice(int index, double newPrice) {
  if (supervisor != nullptr) {
    cout << role << " - Changing " << bakeryItems[index].getBakeryItemName() << " price..." << endl;
    bakeryItems[index].setPricePerUnit(newPrice);
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

// @TjeEwe file handling if new bakery item is created
// deduct ingredients from inventory
void Employee::bakeNewBakeryItem(int index, int quantity) {
  if (baker != nullptr) {
    cout << role << " - Baking " << quantity << "x " << bakeryItems[index].getBakeryItemName() << "..." << endl;
    // check if bakery item is disabled
    if (bakeryItems[index].getDisabled()) {
      cout << "Action unavailable. " << bakeryItems[index].getBakeryItemName() << " is withdrawn." << endl;
      return;
    }

    // check if ingredient is enough
    int * ingredientInventoryIndex = new int[MAX_INGREDIENTS];
    for (int i = 0; i < bakeryItems[index].getIngredientCount(); i++) {
      for (int j = 0; j < ingredientInventory->getIngredientInventoryCount(); j++) {
        // cout << bakeryItems[index].getIngredient(i)->getName() << " " << ingredientInventory->getIngredientInventoryName(j) << endl;
        if (bakeryItems[index].getIngredient(i)->getName() == ingredientInventory->getIngredientInventoryName(j)) {
          cout << "Ingredient " << bakeryItems[index].getIngredient(i)->getName() << " found in inventory." << endl;
          if (bakeryItems[index].getIngredient(i)->getCountable()) {
            if (bakeryItems[index].getIngredient(i)->getPiece() * quantity > ingredientInventory->getIngredientInventoryPiece(j)) {
              cout << "Not enough " << bakeryItems[index].getIngredient(i)->getName() << " in inventory." << endl;
              cout << "Available: " << ingredientInventory->getIngredientInventoryPiece(j) << " pieces." << endl;
              cout << "Require " << bakeryItems[index].getIngredient(i)->getPiece() * quantity << " pieces." << endl;
              return;
            } else {
              ingredientInventoryIndex[i] = j;
            }
          } else {
            if (bakeryItems[index].getIngredient(i)->getWeight() * quantity > ingredientInventory->getIngredientInventoryWeight(j)) {
              cout << "Not enough " << bakeryItems[index].getIngredient(i)->getName() << " in inventory." << endl;
              cout << "Available: " << ingredientInventory->getIngredientInventoryWeight(j) << " gram(s)." << endl;
              cout << "Require " << bakeryItems[index].getIngredient(i)->getWeight() * quantity << " gram(s)." << endl;
              return;
            } else {
              ingredientInventoryIndex[i] = j;            
            }
          }
        }
      }
      // check if ingredient is not found in inventory
      if ((i == bakeryItems[index].getIngredientCount() - 1) && (bakeryItems[index].getIngredient(i)->getName() != ingredientInventory->getIngredientInventoryName(i))){
        cout << "Action unavailable: Ingredient " << bakeryItems[index].getIngredient(i)->getName() << " not found in inventory." << endl;
        cout << "Please restock ingredient " << bakeryItems[index].getIngredient(i)->getName() << " before baking." << endl;
        return;
      }

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

    }
  } else {
    cout << "Only baker can bake bakery item." << endl;
  }
}

void Employee::getBakeryItems(BakeryItem * bakeryItems) const {
  this->bakeryItems = bakeryItems;
}

Employee::~Employee() {
  delete supervisor;
  delete baker;
  delete cashier;

  // cout << "Employee " << name << " has been removed." << endl;
}

IngredientInventory * Employee::ingredientInventory = new IngredientInventory[MAX_INGREDIENTS_INVENTORY];
BakeryItem * Employee::bakeryItems = new BakeryItem[MAX_BAKERY_ITEMS];