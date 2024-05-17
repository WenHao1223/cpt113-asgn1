#ifndef BAKERYITEM_H
#define BAKERYITEM_H

#include <iostream> // for input/output
#include <string> // for string

#include "Constant.h" // Include the Constant header file
#include "Cake.h" // Include the Cake header file
#include "Ingredient.h" // Include the Ingredient header file
#include "IngredientInventory.h" // Include the IngredientInventory header file

using namespace std;

const int MAX_INGREDIENTS = Constant::MAX_BAKERY_ITEMS; // Define the maximum number of ingredients for a bakery item

/**
 * @file BakeryItem.h
 * @brief Contains the declaration of the BakeryItem class.
 */

/**
 * @class BakeryItem
 * @brief Represents a bakery item.
 * 
 * This class contains information about a bakery item, such as its name, category, description, price, ingredients, quantity, recipe, and status.
 * It also provides member functions to display the details, calculate the cost and profit, and set the ingredient cost to the inventory ingredient cost.
 */
class BakeryItem {
  private:
    string name; // Name of the bakery item
    string category; // Category of the bakery item
    string description; // Description of the bakery item
    double pricePerUnit; // Price per unit of the bakery item
    Ingredient * ingredient = new Ingredient[MAX_INGREDIENTS]; // Array of ingredients for the bakery item
    int ingredientCount = 0; // Number of ingredients in the bakery item
    double quantity = 0; // Quantity of the bakery item (can be weight)
    string recipe; // Recipe of the bakery item
    bool disabled = false; // Flag to indicate if the bakery item is disabled
    Cake cake; // Cake object to store the total weight of the cake
    static int bakeryItemCount; // Static variable to keep track of the number of bakery items
    static BakeryItem * bakeryItems; // Pointer to an array of BakeryItem objects
        
  public:
    // Constructors
    BakeryItem(); // Default constructor
    BakeryItem(string name, string category, string description, double pricePerUnit, Ingredient * ingredient, int ingredientCount, string recipe, bool disabled); // Constructor with parameters
    BakeryItem(string name, string category, string description, double pricePerUnit, Ingredient * ingredient, int ingredientCount, string recipe, bool disabled, int totalWeight); // Constructor with additional parameter

    // Member functions
    /**
     * @brief Display the details of the bakery item.
     */
    void displayBakeryItemDetails() const;
    
    /**
     * @brief Calculate the cost of the bakery item.
     * @return The cost of the bakery item.
     */
    double calculateCost() const;
    
    /**
     * @brief Calculate the profit of the bakery item.
     * @return The profit of the bakery item.
     */
    double calculateProfit() const;
    
    /**
     * @brief Set the ingredient cost to the inventory ingredient cost.
     * @param inventory The IngredientInventory object containing the ingredient cost information.
     */
    void setIngredientCostToInventoryIngredientCost(IngredientInventory *);

    // Accessors
    /**
     * @brief Get the name of the bakery item.
     * @return The name of the bakery item.
     */
    string getBakeryItemName() const;
    
    /**
     * @brief Get the category of the bakery item.
     * @return The category of the bakery item.
     */
    string getBakeryItemCategory() const;
    
    /**
 * @brief 
     * @return The description of the bakery item.
     */
    string getBakeryItemDescription() const;
    
    /**
     * @brief 
     * @return The price per unit of the bakery item.
     */
    double getPricePerUnit() const;
    
    /**
     * @brief Get a specific ingredient of the bakery item.
     * @param index The index of the ingredient.
     * @return A pointer to the Ingredient object.
     */
    Ingredient * getIngredient(int) const;
    
    /**
     * @brief 
     * @param index The index of the ingredient.
     * @return The name of the ingredient.
     */
    string getIngredientName(int) const;
    
    /**
     * @brief Get the cake object
     * @param None.
     * @return Cake object.
     */
    Cake getCake() const;
    
    /**
     * @brief Get the number of ingredients in the bakery item.
     * @return The number of ingredients.
     */
    int getIngredientCount() const;
    
    /**
     * @brief Get the quantity of the bakery item.
     * @return The quantity of the bakery item.
     */
    double getBakeryItemQuantity() const;
    
    /**
     * @brief Get the recipe of the bakery item.
     * @return The recipe of the bakery item.
     */
    string getRecipe() const;
    
    /**
     * @brief Check if the bakery item is disabled.
     * @return True if the bakery item is disabled, false otherwise.
     */
    bool getDisabled() const;
    
    /**
     * @brief Get the total count of bakery items.
     * @return The total count of bakery items.
     */
    int getBakeryItemCount() const;

    // Mutators
    /**
     * @brief Set the bakery items.
     * @param items The array of BakeryItem objects.
     */
    void setBakeryItems(BakeryItem *);
    
    /**
     * @brief Set the price per unit of the bakery item.
     * @param price The price per unit.
     */
    void setPricePerUnit(double);
    
    /**
     * @brief Set the quantity of the bakery item.
     * @param quantity The quantity of the bakery item.
     */
    void setBakeryItemQuantity(double);
    
    /**
     * @brief Set the recipe of the bakery item.
     * @param recipe The recipe of the bakery item.
     */
    void setRecipe(string);
    
    /**
     * @brief Set the disabled flag of the bakery item.
     * @param disabled The disabled flag.
     */
    void setDisabled(bool);

    // Friend function to be used by main.cpp
    /**
     * @brief Friend function declaration to access menu details of a BakeryItem object.
     * 
     * This friend function allows access to the private members of the BakeryItem class
     * in order to retrieve and display the menu details.
     * 
     * @param item The BakeryItem object to access the menu details of.
     */
    friend void accessMenuDetails(const BakeryItem *);

    // Destructor
    ~BakeryItem();
};

#endif