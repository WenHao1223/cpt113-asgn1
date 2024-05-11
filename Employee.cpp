#include <iomanip>

#include "Employee.h"
#include "BakeryItem.h"

const int MAX_BAKERY_ITEMS = 10;
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
      Ingredient("Ingredient 1 of Item 1", 1.0, 100.0)
    }, numberOfIngredients, "Recipe 1");
  numberOfIngredients = 3;
  bakeryItems[1] = BakeryItem("Item 2", "Description 2", 20.0,
    new Ingredient[numberOfIngredients] {
      Ingredient("Ingredient 1 of Item 2", 0.005, 200.0),
      Ingredient("Ingredient 2 of Item 2", 2.0, 3),
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
    cout << "Not a valid position to start the bakery." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Selling " << ingredientInventory[0].getIngredientInventoryCount() << " items today." << endl;
}

void Employee::accessMenuList() const {
  cout << position << " - Accessing menu list..." << endl;
  for (int i = 0; i < bakeryItems[0].getBakeryItemCount(); i++) {
    // cout << "Item address: " << &items[i] << endl;
    cout << i+1 << ". " << bakeryItems[i].getBakeryItemName() << endl;
  }
}

void Employee::accessMenuItem(int index) const {
  cout << position << " - Accessing menu details..." << endl;
  accessMenuDetails(bakeryItems[index]);
}

void Employee::displayIngredientInventoryList() const {
  if (supervisor != nullptr || baker != nullptr) {
    cout << position << " - Displaying ingredient inventory list..." << endl;
    ingredientInventory->displayIngredientInventoryList();
  } else {
    cout << "Only supervisor or baker can display ingredient inventory list." << endl;
  }
}

void Employee::accessIngredientInventoryDetails(int index) const {
  if (supervisor != nullptr || baker != nullptr) {
    cout << position << " - Accessing ingredient inventory details..." << endl;
    (ingredientInventory+index)->accessIngredientInventoryDetails();
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

void Employee::restockIngredientInventory(int index, int quantity) const {
  if (supervisor != nullptr) {
    cout << position << " - Restocking ingredient inventory..." << endl;
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
    cout << position << " - Changing ingredient cost..." << endl;
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
    cout << position << " - Creating bakery item..." << endl;

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
    cout << position << " - Withdrawing " << bakeryItems[index].getBakeryItemName() << "..." << endl;
    bakeryItems[index].setDisabled(true);
  } else {
    cout << "Only supervisor can withdraw bakery item." << endl;
  }
}

void Employee::enableBakeryItem (int index) {
  if (supervisor != nullptr) {
    cout << position << " - Enabling " << bakeryItems[index].getBakeryItemName() << "..." << endl;
    bakeryItems[index].setDisabled(false);
  } else {
    cout << "Only supervisor can enable bakery item." << endl;
  }
}

void Employee::changeBakeryItemPrice(int index, double newPrice) {
  if (supervisor != nullptr) {
    cout << position << " - Changing " << bakeryItems[index].getBakeryItemName() << " price..." << endl;
    bakeryItems[index].setPricePerUnit(newPrice);
  } else {
    cout << "Only supervisor can change bakery item price." << endl;
  }
}

void Employee::calculateBakeryItemCost(int index) const {
  cout << position << " - Calculating " << bakeryItems[index].getBakeryItemName() << " cost..." << endl;
  cout << setprecision(2) << fixed;
  cout << "Total cost: RM " << bakeryItems[index].calculateCost() << endl;
}

void Employee::calculateBakeryItemProfit(int index) const {
  cout << position << " - Calculating " << bakeryItems[index].getBakeryItemName() << " profit..." << endl;
  cout << setprecision(2) << fixed;
  cout << "Total profit: RM " << bakeryItems[index].calculateProfit() << endl;
}

void Employee::compareCostVsProfit(int index) const {
  cout << position << " - Comparing " << bakeryItems[index].getBakeryItemName() << " cost vs profit..." << endl;
  cout << setprecision(2) << fixed;
  cout << "Total cost: RM " << bakeryItems[index].calculateCost() << endl;
  cout << "Selling price: RM " << bakeryItems[index].getPricePerUnit() << endl; 
  cout << "Total profit: RM " << bakeryItems[index].calculateProfit() << endl;

  // percentage
  cout << setprecision(2) << fixed;
  cout << "Profit percentage: " << (bakeryItems[index].calculateProfit() / bakeryItems[index].calculateCost()) * 100 << "%" << endl;
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