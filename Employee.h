#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>

#include "Constant.h"
#include "Discount.h"
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
    string role;
    Supervisor * supervisor = nullptr;
    Baker * baker = nullptr;
    Cashier * cashier = nullptr;

    static BakeryItem * bakeryItems;
    static IngredientInventory * ingredientInventory;
    static Discount * discounts;
        
  public:
    // Constructor
    Employee();
    Employee(string employeeID, string name, string role);

    // member functions
    void displayEmployeeDetails() const;
    void startBakery() const;
    void accessMenuList() const;
    void accessMenuItem(int index) const;
    void accessDiscountList() const;
    void accessDiscountDetails(int index) const;

    // accessible by supervisor or baker only
    void displayIngredientInventoryList() const;
    void accessIngredientInventoryDetails(int) const;
    void checkIngredientInventory() const;

    // accessibly by supervisor role only
    void restockIngredientInventory(int index, int quantity) const;
    void changeIngredientCost(int index, double cost) const;
    void addNewInventoryIngredientWeight(string name, double cost, double weight) const;
    void addNewInventoryIngredientPiece(string name, double cost, int piece) const;
    void getAllInventoryIngredientName() const;
    void createBakeryItem();
    void withdrawBakeryItem(int index);
    void enableBakeryItem(int index);
    void changeBakeryItemPrice(int index, double newPrice);
    void calculateBakeryItemCost(int index) const;
    void calculateBakeryItemProfit(int index) const;
    void compareCostVsProfit(int index) const;
    void compareCostVsPrice(int index) const;
    void createNewEmployee(Employee * employees, string employeeID, string name, string role);
    void changeEmployeeRole(Employee employees [], int index, string role);
    void displayAllEmployeeDetails(Employee employees []) const;
    void deleteEmployee(Employee employees [], int index);
    void addNewDiscount();

    // accessible by baker role only
    void bakeNewBakeryItem(int index, int quantity);

    // accessible by cashier only
    void addBakeryItemToCart(int index, int quantity);
    void displayCartDetails() const;
    void calculateCartTotalCost() const;
    void calculateCartTotalPrice() const;
    void calculateCartTotalProfit() const;
    void getCartItemCount() const;
    void removeBakeryItemFromCart(int index);
    void updateBakeryItemQuantityInCart(int index, int quantity);
    void clearCart();

    // accessor
    void getBakeryItems(BakeryItem *) const;

    // Destructor
    ~Employee();
};

#endif