#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;


class Ingredient {
  private:
    string name;
    double cost;
    double weight = 0;
    int piece = 0;
    
  public:
    // Constructor
    // uncountable items
    Ingredient(string name, double cost, double weight) {
      this->name = name;
      this->cost = cost;
      this->weight = weight;
      cout << "Ingredient " << name << " has been added." << endl;
    }
    // countable items
    Ingredient(string name, double cost, int piece) {
      this->name = name;
      this->cost = cost;
      this->piece = piece;
      // cout << "Ingredient " << name << " has been added." << endl;
    }

    // member functions
    void displayIngredientDetails() const {
      cout << "Name: " << name << endl;
      cout << "Cost: " << cost << endl;
      cout << "Weight: " << weight << endl;
      cout << "Piece: " << piece << endl;
      cout << endl;
    }
};

class BakeryItem {
  private:
    string name;
    string description;
    double pricePerUnit;
    Ingredient * ingredient = nullptr;
    int ingredientCount = 0;
    string recipe;
    bool disabled = false;
        
  public:
    // Constructor
    BakeryItem(string name, string description, double pricePerUnit, Ingredient * ingredient, int ingredientCount, string recipe) {
      this->name = name;
      this->description = description;
      this->pricePerUnit = pricePerUnit;
      this->ingredient = ingredient;
      this->ingredientCount = ingredientCount;
      this->recipe = recipe;
      // cout << "Bakery Item " << name << " has been added." << endl;
    }

    // member functions
    void displayBakeryItemDetails() const {
      cout << "Name: " << name << endl;
      cout << "Description: " << description << endl;
      cout << "Price per unit: " << pricePerUnit << endl;
      cout << "Recipe: " << recipe << endl;

      for (int i = 0; i < ingredientCount; i++) {
        cout << "Ingredient " << i + 1 << ":" << endl;
        ingredient[i].displayIngredientDetails();
      }

      cout << "Out of stock: " << disabled << endl;
      cout << endl;
    }

    // destructor
    ~BakeryItem() {
      delete ingredient;
      // cout << "Bakery Item " << name << " has been removed." << endl;
    }

};

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
  // Employee supervisor1("S1", "Supervisor 1", "Supervisor");
  // Employee baker1("B1", "Baker 1", "Baker");
  // Employee cashier1("C1", "Cashier 1", "Cashier");

  cout << endl;

  // Display employee details
  // supervisor1.displayEmployeeDetails();
  // baker1.displayEmployeeDetails();
  // cashier1.displayEmployeeDetails();

  // Create bakery items
  const int INGREDIENT1_COUNT = 1;
  const int INGREDIENT2_COUNT = 3;
  Ingredient ingredient1[INGREDIENT1_COUNT] = {
    Ingredient("Ingredient 1 of Item 1", 10.0, 100.0)
  };
  Ingredient ingredient2[INGREDIENT2_COUNT] = {
    Ingredient("Ingredient 1 of Item 1", 20.0, 200.0),
    Ingredient("Ingredient 2 of Item 2", 30.0, 300.0),
    Ingredient("Ingredient 3 of Item 3", 40.0, 400.0)
  };
  BakeryItem item1("Item 1", "Description 1", 10.0, ingredient1, INGREDIENT1_COUNT, "Recipe 1");
  BakeryItem item2("Item 2", "Description 2", 20.0, ingredient2, INGREDIENT2_COUNT, "Recipe 2");

  cout << endl;

  // Display bakery item details
  item1.displayBakeryItemDetails();
  item2.displayBakeryItemDetails();
  
  return 0;
}