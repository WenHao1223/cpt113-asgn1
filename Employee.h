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

    static int orderNo;

    static double totalBalance;
    static double totalCredit;
    static double totalDebit;
    static double totalProfitPerDay;
        
  public:
    // Constructor
    Employee();
    Employee(string employeeID, string name, string role);

    // member functions
    // accessible by all roles
    void displayEmployeeDetails() const;
    void setIngredientCostToInventoryIngredientCost();
    void startBakery();
    void accessMenuList() const;
    void accessMenuItem(int index) const;
    void accessDiscountList() const;
    void accessDiscountDetails(int index) const;
    void showTotalDebit() const;
    void showTotalCredit() const;
    void showTotalProfitPerDay() const;
    void showTotalBalance() const;
    void closeBakery(string date);

    // accessible by supervisor or baker only
    void displayIngredientInventoryList() const;
    void accessIngredientInventoryDetails(int) const;
    void checkIngredientInventory() const;

    // accessibly by supervisor role only
    void restockIngredientInventory(int index, double quantity) const;
    void changeIngredientCost(int index, double cost);
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
    void accessDiscountFile(int index, string field, string value);
    void editDiscountName(int index, string name);
    void editDiscountMinimumPurchase(int index, double minimumPurchase);
    void editDiscountPercentage(int index, double percentage);
    void editDiscountDescription(int index, string description);
    void disableDiscount(int index);
    void enableDiscount(int index);
    void deleteDiscount(int index);

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
    void checkout();
    void showDiscountBasedOnCartTotalPrice() const;
    void applyDiscount(int choice);
    double calculateDiscountedTotalPrice() const;

    // accessible by supervisor or cashier only
    void showReceipt(string date, int oderNo = orderNo) const;

    // accessor
    string getEmployeeID() const;
    string getName() const;
    string getRole() const;
    int getOrderNo() const;
    double getTotalBalance() const;
    double getTotalCredit() const;
    double getTotalDebit() const;
    double getTotalProfitPerDay() const;

    // friend function
    friend int findEmployeeIndex(Employee employees [], string employeeID);

    // Destructor
    ~Employee();
};

#endif