#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>
#include "Supervisor.h"
#include "Baker.h"
#include "Cashier.h"
#include "BakeryItem.h"
#include "IngredientInventory.h"

using namespace std;

// forward declaration
class BakeryItem;

class Employee {
  private:
    string employeeID;
    string name;
    string position;
    Supervisor * supervisor = nullptr;
    Baker * baker = nullptr;
    Cashier * cashier = nullptr;

    static BakeryItem * bakeryItems;
    static Ingredient * ingredientBakeryItems;
    static IngredientInventory * ingredientInventory;
        
  public:
    // Constructor
    Employee();
    Employee(string employeeID, string name, string position);

    // member functions
    void displayEmployeeDetails() const;
    void startBakery() const;
    void accessMenuList() const;
    void accessMenuItem(int) const;

    // accessible by supervisor or baker only
    void displayIngredientInventoryList() const;
    void accessIngredientInventoryDetails(int) const;

    // accessibly by supervisor role only
    void checkIngredientInventory() const;
    void restockIngredientInventory(int, int) const;
    void changeIngredientCost(int, double) const;
    void createBakeryItem();

    // accessor
    void getBakeryItems(BakeryItem *) const;

    // Destructor
    ~Employee();
};

#endif