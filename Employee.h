#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string> // for string
#include <iostream> // for input/output

#include "Constant.h" // Include the header file for the Constant class.
#include "Discount.h" // Include the header file for the Discount class.
#include "Supervisor.h" // Include the header file for the Supervisor class.
#include "Baker.h" // Include the header file for the Baker class.
#include "Cashier.h" // Include the header file for the Cashier class.
#include "BakeryItem.h" // Include the header file for the BakeryItem class.
#include "IngredientInventory.h" // Include the header file for the IngredientInventory class.

using namespace std;

// Forward declaration
class BakeryItem;

/**
 * @file Employee.h
 * @brief Contains the declaration of the Employee class.
 */

/**
 * @class Employee
 * @brief Represents an employee in a bakery.
 */
class Employee {
  private:
    string employeeID; // The ID of the employee.
    string name; // The name of the employee.
    string role; // The role of the employee.
    string password; // The password of the employee.
    Supervisor * supervisor = nullptr; // Pointer to the supervisor object associated with the employee.
    Baker * baker = nullptr; // Pointer to the baker object associated with the employee.
    Cashier * cashier = nullptr; // Pointer to the cashier object associated with the employee.

    static BakeryItem * bakeryItems; // Pointer to the array of bakery items.
    static IngredientInventory * ingredientInventory; // Pointer to the ingredient inventory object.
    static Discount * discounts; // Pointer to the array of discounts.

    static int orderNo; // The order number for the bakery.

    static double totalBalance; // The total balance of the bakery.
    static double totalCredit; // The total credit of the bakery.
    static double totalDebit; // The total debit of the bakery.
    static double totalProfitPerDay; // The total profit per day of the bakery.
        
  public:
    /**
     * @brief Default constructor for the Employee class.
     */
    Employee();

    /**
     * @brief Parameterized constructor for the Employee class.
     * @param employeeID The ID of the employee.
     * @param name The name of the employee.
     * @param role The role of the employee.
     * @param password The password of the employee.
     */
    Employee(string employeeID, string name, string role, string password);

    /** 
     * @note The following funtions are accessible by all employees.
     */

    /**
     * @brief Displays the details of the employee.
     * 
     * This function displays the employee ID, name, and role.
     * 
     * @param None.
     * @return None.
     * 
     */
    void displayEmployeeDetails() const;

    /**
     * @brief Logs in the employee.
     * 
     * This function logs in the employee by checking the employee ID and password.
     * 
     * @param employeeID The ID of the employee.
     * @param password The password of the employee.
     * @return True if the employee is logged in, false otherwise.
     * 
     */
    bool login(string employeeID, string password);

    /**
     * @brief Logs out the employee.
     * 
     * This function logs out the employee.
     * 
     * @param None.
     * @return None.
     * 
     */
    void setIngredientCostToInventoryIngredientCost();

    /**
     * @brief Starts the bakery operation on the specified date.
     * 
     * @param date The date on which the bakery operation will start.
     * @note The date format is "YYYY-MM-DD".
     * @return None.
     * 
     */
    void startBakery(string date);

    /**
     * @brief Accesses the menu list.
     *
     * This function allows the user to access the menu list.
     *
     * @param None.
     * @return None.
     * 
     */
    void accessMenuList() const;

    /**
     * @brief Accesses the menu item.
     *
     * This function allows the user to access the menu item.
     *
     * @param index The index of the menu item.
     * @return None.
     * 
     */
    void accessMenuItem(int index);

    /**
     * @brief Access the discount list.
     * 
     * This function allows the user to access the discount list.
     * 
     * @param None.
     * @return None.
     * 
     */
    void accessDiscountList() const;

    /**
     * @brief Access the discount details.
     * 
     * This function allows the user to access the discount details.
     * 
     * @param index The index of the discount in the discount list.
     * @return None.
     * 
     */
    void accessDiscountDetails(int index) const;

    /**
     * @brief Get the number of discount available to apply according to the total purchase.
     * 
     * @param None.
     * @return int 
     */
    int getAvailableDiscountCount() const;

    /**
     * @brief Show the total debit of the bakery.
     * 
     * @param None.
     * @return None.
     * 
     */
    void showTotalDebit() const;

    /**
     * @brief Show the total credit of the bakery.
     * 
     * @param None.
     * @return None.
     * 
     */
    void showTotalCredit() const;

    /**
     * @brief Show the total profit per day of the bakery.
     * 
     * @param None.
     * @return None.
     * 
     */
    void showTotalProfitPerDay() const;

    /**
     * @brief Show the total balance of the bakery.
     * 
     * @param None.
     * @return None.
     * 
     */
    void showTotalBalance() const;

    /**
     * @brief Close the bakery operation on the specified date.
     * 
     * @param date The date on which the bakery operation will close.
     * @note The date format is "YYYY-MM-DD".
     * @return None.
     * 
     */
    void closeBakery(string date);

    /**
     * @note The following functions are accessible by the supervisor and baker only.
     * 
     */

    /**
     * @brief Display the ingredient inventory list.
     * 
     * @param None.
     * @return None.
     * 
     */
    void displayIngredientInventoryList() const;

    /**
     * @brief Access the ingredient inventory details.
     * 
     * @param index The index of the ingredient inventory.
     * @return None.
     * 
     */
    void accessIngredientInventoryDetails(int) const;

    /**
     * @brief Check the ingredient inventory.
     * 
     * @param None.
     * @return None.
     * 
     */
    void checkIngredientInventory() const;

    /**
     * @note The following functions are accessible by the supervisor only.
     * 
     */

    /**
     * @brief Accesses the ingredient inventory file and performs a search based on the specified field and value.
     * 
     * @param index The index of the ingredient in the inventory file.
     * @param field The field to search for in the inventory file.
     * @param value The value to match in the specified field.
     * 
     * @return None.
     */
    void accessIngredientInventoryFile(int index, string field, string value);

    /**
     * @brief Restocks the ingredient inventory.
     * 
     * @param index The index of the ingredient in the inventory.
     * @param quantity The quantity to restock.
     * 
     * @return None.
     */
    void restockIngredientInventory(int index, double quantity);

    /**
     * @brief Changes the cost of the ingredient in the inventory.
     * 
     * @param index The index of the ingredient in the inventory.
     * @param cost The new cost of the ingredient.
     * 
     * @return None.
     */
    void changeIngredientCost(int index, double cost);

    /**
     * @brief Adds a new ingredient to the inventory with the specified cost and weight.
     * 
     * @param name The name of the ingredient.
     * @param cost The cost of the ingredient.
     * @param weight The weight of the ingredient.
     * 
     * @return None.
     */
    void addNewInventoryIngredientWeight(string name, double cost, double weight);

    /**
     * @brief Adds a new ingredient to the inventory with the specified cost and piece.
     * 
     * @param name The name of the ingredient.
     * @param cost The cost of the ingredient.
     * @param piece The piece of the ingredient.
     * 
     * @return None.
     */
    void addNewInventoryIngredientPiece(string name, double cost, int piece);

    /**
     * @brief Get the All Inventory Ingredient Name
     * 
     * This function gets the name of all the inventory ingredients.
     * 
     * @param None.
     * @return None.
     * 
     */
    void getAllInventoryIngredientName() const;

    /**
     * @brief Create a Bakery Item object
     * 
     * This function creates a new bakery item object either a cake or a cookie.
     * 
     * @param None.
     * @return None.
     * 
     */
    void createBakeryItem();

    /**
     * @brief Accesses the bakery item file and performs a search based on the specified field and value.
     * 
     * @param index The index of the bakery item.
     * @param field The field to search for in the bakery item file.
     * @param value The value to match in the specified field.
     * 
     * @return None.
     */
    void accessBakeryItemFile(int index, string field, string value);

    /**
     * @brief Withdraws the ingredient from the inventory.
     * 
     * @param index The index of the ingredient in the inventory.
     * @param quantity The quantity to withdraw.
     * 
     * @return None.
     */
    void withdrawBakeryItem(int index);

    /**
     * @brief Enable the bakery item.
     * 
     * @param index The index of the bakery item.
     * @return None.
     */
    void enableBakeryItem(int index);
    
    /**
     * @brief Change the bakery item price based on the index.
     * 
     * @param index The index of the bakery item.
     * @param newPrice The new price of the bakery item.
     */
    void changeBakeryItemPrice(int index, double newPrice);

    /**
     * @brief Calculates the cost of a bakery item at the specified index.
     * 
     * This function calculates the cost of a bakery item based on the index provided.
     * The index should be a valid index within the bakery item list.
     * 
     * @param index The index of the bakery item.
     * 
     * @return None.
     */
    void calculateBakeryItemCost(int index) const;

    /**
     * @brief Calculates the profit of a bakery item at the specified index.
     * 
     * This function calculates the profit of a bakery item based on the index provided.
     * The index should be a valid index within the bakery item list.
     * 
     * @param index The index of the bakery item.
     * 
     * @return None.
     */
    void calculateBakeryItemProfit(int index) const;

    /**
     * @brief Compares the cost and profit of a bakery item at the specified index.
     * 
     * This function compares the cost and profit of a bakery item based on the index provided.
     * The index should be a valid index within the bakery item list.
     * 
     * @param index The index of the bakery item.
     * 
     * @return None.
     */
    void compareCostVsProfit(int index) const;

    /**
     * @brief Compares the cost and price of a bakery item at the specified index.
     * 
     * This function compares the cost and price of a bakery item based on the index provided.
     * The index should be a valid index within the bakery item list.
     * 
     * @param index The index of the bakery item.
     * 
     * @return None.
     */
    void compareCostVsPrice(int index) const;

    /**
     * @brief Creates a new employee with the given details.
     * 
     * @param employees An array of Employee objects.
     * @param employeeID The ID of the employee.
     * @param name The name of the employee.
     * @param role The role of the employee.
     * @param password The password of the employee.
     * 
     * @return None.
     */
    void createNewEmployee(Employee * employees, string employeeID, string name, string role, string password);

    /**
     * @brief Accesses the employee data file and performs a search based on the specified field and value.
     * 
     * @param index The index of the employee in the employee data file.
     * @param field The field to search for in the employee data file.
     * @param value The value to match in the specified field.
     * 
     * @return None.
     */
    void accessEmployeeDataFile(int index, string field, string value);

    /**
     * @brief Changes the role of the employee at the specified index.
     * 
     * This function changes the role of the employee based on the index provided.
     * The index should be a valid index within the employee list.
     * 
     * @param employees An array of Employee objects.
     * @param index The index of the employee.
     * @param role The new role of the employee.
     * 
     * @return None.
     */
    void changeEmployeeRole(Employee employees [], int index, string role);
    
    /**
     * @brief Display all employee details in the employee list.
     * 
     * This function displays all the employee details in the employee list.
     * 
     * @param employees An array of Employee objects.
     * 
     * @return None.
     * 
     */
    void displayAllEmployeeDetails(Employee employees []) const;

    /**
     * @brief Delete the employee at the specified index.
     * 
     * This function deletes the employee based on the index provided.
     * The index should be a valid index within the employee list.
     * 
     * @param employees An array of Employee objects.
     * @param index The index of the employee.
     * 
     * @return None.
     */
    void deleteEmployee(Employee employees [], int index);

    /**
     * @brief Access the discount file and perform a search based on the specified field and value.
     * 
     * @param index The index of the discount in the discount file.
     * @param field The field to search for in the discount file.
     * @param value The value to match in the specified field.
     * 
     * @return None.
     */
    void addNewDiscount();
    
    /**
     * @brief Access the discount file and perform a search based on the specified field and value.
     * 
     * @param index The index of the discount in the discount file.
     * @param field The field to search for in the discount file.
     * @param value The value to match in the specified field.
     * 
     * @return None.
     */
    void accessDiscountFile(int index, string field, string value);

    /**
     * @brief Edit the discount name at the specified index.
     * 
     * This function edits the discount name based on the index provided.
     * The index should be a valid index within the discount list.
     * 
     * @param index The index of the discount.
     * @param name The new name of the discount.
     * 
     * @return None.
     */
    void editDiscountName(int index, string name);

    /**
     * @brief Edit the discount minimum purchase at the specified index.
     * 
     * This function edits the discount minimum purchase based on the index provided.
     * The index should be a valid index within the discount list.
     * 
     * @param index The index of the discount.
     * @param minimumPurchase The new minimum purchase of the discount.
     * 
     * @return None.
     */
    void editDiscountMinimumPurchase(int index, double minimumPurchase);

    /**
     * @brief Edit the discount percentage at the specified index.
     * 
     * This function edits the discount percentage based on the index provided.
     * The index should be a valid index within the discount list.
     * 
     * @param index The index of the discount.
     * @param percentage The new percentage of the discount.
     * 
     * @return None.
     */
    void editDiscountPercentage(int index, double percentage);

    /**
     * @brief Edit the discount description at the specified index.
     * 
     * This function edits the discount description based on the index provided.
     * The index should be a valid index within the discount list.
     * 
     * @param index The index of the discount.
     * @param description The new description of the discount.
     * 
     * @return None.
     */
    void editDiscountDescription(int index, string description);

    /**
     * @brief Disable the discount at the specified index.
     * 
     * This function disables the discount based on the index provided.
     * The index should be a valid index within the discount list.
     * 
     * @param index The index of the discount.
     * 
     * @return None.
     */
    void disableDiscount(int index);

    /**
     * @brief Enable the discount at the specified index.
     * 
     * This function enables the discount based on the index provided.
     * The index should be a valid index within the discount list.
     * 
     * @param index The index of the discount.
     * 
     * @return None.
     */
    void enableDiscount(int index);

    /**
     * @brief Delete the discount at the specified index.
     * 
     * This function deletes the discount based on the index provided.
     * The index should be a valid index within the discount list.
     * 
     * @param index The index of the discount.
     * 
     * @return None.
     */
    void deleteDiscount(int index);

    /**
     * @brief Display the balance sheet of the bakery.
     * 
     * @param None.
     * @return None.
     */
    void displayBalanceSheet() const;

    /**
     * @brief Access the transaction history.
     * 
     * @param date The date of the transaction history.
     * @note The date format is "YYYYMMDD".
     * 
     * @return None.
     */
    void accessTransactionHistory(string date) const;

    /**
     * @note The following functions are accessible by the baker only.
     * 
     */
    void bakeNewBakeryItem(int index, int quantity);

    /**
     * @note The following functions are accessible by the cashier only.
     * 
     */

    /**
     * @brief Add a bakery item to the cart.
     * 
     * This function adds a bakery item to the cart based on the index and quantity provided.
     * The index should be a valid index within the bakery item list.
     * 
     * @param index The index of the bakery item.
     * @param quantity The quantity of the bakery item.
     * 
     * @return None.
    */
    void addBakeryItemToCart(int index, int quantity);

    /**
     * @brief Add a cake by weight to the cart.
     * 
     * This function adds a cake by weight to the cart based on the index and weight provided.
     * The index should be a valid index within the bakery item list.
     * 
     * @param index The index of the bakery item.
     * @param weight The weight of the cake.
     * 
     * @return None.
    */
    void addCakeByWeightToCart(int index, int weight);

    /**
     * @brief Display the cart details of the cashier.
     * 
     * This function displays the cart details of the cashier.
     * 
     * @param None.
     * @return None.
     * 
     */
    void displayCartDetails() const;

    /**
     * @brief Calculate the total cost of the cart.
     * 
     * This function calculates the total cost of the cart.
     * 
     * @param None.
     * @return None.
     * 
     */
    void calculateCartTotalCost() const;

    /**
     * @brief Calculate the total price of the cart.
     * 
     * This function calculates the total price of the cart.
     * 
     * @param None.
     * @return None.
     * 
     */
    void calculateCartTotalPrice() const;

    /**
     * @brief Calculate the total profit of the cart.
     * 
     * This function calculates the total profit of the cart.
     * 
     * @param None.
     * @return None.
     * 
     */
    void calculateCartTotalProfit() const;

    /**
     * @brief Get the cart item count.
     * 
     * This function gets the cart item count.
     * 
     * @param None.
     * @return None.
     * 
     */
    void getCartItemCount() const;

    /**
     * @brief Remove a bakery item from the cart.
     * 
     * This function removes a bakery item from the cart based on the index provided.
     * The index should be a valid index within the cart.
     * 
     * @param index The index of the bakery item.
     * 
     * @return None.
     */
    void removeBakeryItemFromCart(int index);

    /**
     * @brief Update the quantity of a bakery item in the cart.
     * 
     * This function updates the quantity of a bakery item in the cart based on the index and quantity provided.
     * The index should be a valid index within the cart.
     * 
     * @param index The index of the bakery item.
     * @param quantity The quantity of the bakery item.
     * 
     * @return None.
     */
    void updateBakeryItemQuantityInCart(int index, int quantity);

    /**
     * @brief Clear the cart.
     * 
     * This function clears the cart.
     * 
     * @param None.
     * @return None.
     */
    void clearCart();

    /**
     * @brief Checkout the cart.
     * 
     * This function checks out the cart.
     * 
     * @param dateTime The date and time of the checkout.
     * @note The date and time format is "YYYY-MM-DD HH:MM:SS".
     * 
     * @return None.
     */
    void checkout(string dateTime);

    /**
     * @brief Show the available discount based on the cart total price.
     * 
     * This function shows the available discount based on the cart total price.
     * 
     * @param None.
     * @return None.
     */
    void showDiscountBasedOnCartTotalPrice() const;

    /**
     * @brief Apply the discount based on the choice.
     * 
     * This function applies the discount based on the choice provided.
     * The choice should be a valid choice within the available discount list.
     * 
     * @param choice The choice of the discount.
     * 
     * @return None.
     */
    void applyDiscount(int choice);

    /**
     * @brief Get the available discount based on the choice.
     * 
     * This function gets the available discount based on the choice provided.
     * The choice should be a valid choice within the available discount list.
     * 
     * @param choice The choice of the discount.
     * 
     * @return The available discount.
     */
    Discount * getAvailableDiscount(int choice) const;

    /**
     * @brief Calculate the discounted total price of the cart.
     * 
     * This function calculates the discounted total price of the cart.
     * 
     * @param None.
     * @return The discounted total price of the cart.
     */
    double calculateDiscountedTotalPrice() const;

    /**
     * @note The following functions are accessible by the supervisor and cashier only.
     * 
     */
    void showReceipt(string date, int oderNo = orderNo) const;

    /**
     * @note The folloowing functions are accessor and mutator functions for the Employee class.
     * 
     */

    /**
     * @brief Accessor for the employee ID.
     * @return The employee ID.
     */
    string getEmployeeID() const;

    /**
     * @brief Accessor for the employee name.
     * @return The employee name.
     */
    string getName() const;

    /**
     * @brief Accessor for the employee role.
     * @return The employee role.
     */
    string getRole() const;

    /**
     * @brief Accessor for the order number.
     * @return The order number.
     */
    int getOrderNo() const;

    /**
     * @brief Accessor for the total credit of the bakery.
     * @return The total credit.
     */
    double getTotalCredit() const;

    /**
     * @brief Accessor for the total debit of the bakery.
     * @return The total debit.
     */
    double getTotalDebit() const;

    /**
     * @brief Mutator for the employee ID.
     * @param employeeID The employee ID to set.
     */
    void setEmployeeID(string employeeID);

    /**
     * @brief Mutator for the employee name.
     * @param name The employee name to set.
     */
    void setName(string name);

    /**
     * @brief Mutator for the employee role.
     * @param role The employee role to set.
     */
    void setRole(string role);

    /**
     * @brief Mutator for the employee password.
     * @param password The employee password to set.
     */
    void setPassword(string password);

    // ... (rest of the member functions)

    /**
     * @brief Destructor for the Employee class.
     */
    ~Employee();
};

#endif