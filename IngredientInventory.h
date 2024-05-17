#ifndef INGREDIENTINVENTORY_H
#define INGREDIENTINVENTORY_H

#include <iostream> // for input/output
#include <string> // for string

#include "Ingredient.h" // Include the Ingredient class.

using namespace std;

/**
 * @file IngredientInventory.h
 * @brief This file contains the declaration of the IngredientInventory class.
 */

/**
 * @class IngredientInventory
 * @brief Represents the inventory of ingredients in the bakery.
 * 
 * The IngredientInventory class stores information about the ingredients in the bakery, including their name, cost, and quantity.
 * It provides functionality to add new ingredients to the inventory, restock ingredients, and display the list of ingredients.
 * The class is implemented as a singleton to ensure that there is only one instance of the ingredient inventory.
 * 
 * The IngredientInventory class is derived from the Ingredient class, as each item in the inventory is an ingredient.
 * 
 * The class also contains static member variables to keep track of the count of ingredients in the inventory and the ingredient inventory itself.
 * 
 * The IngredientInventory class interacts with the Ingredient class to access and modify the details of the ingredients.
 * 
 * The IngredientInventory class is responsible for managing the inventory of ingredients in the bakery.
 * 
 */
class IngredientInventory : public Ingredient {
  private:
    static int ingredientInventoryCount; // The count of ingredients in the inventory.
    static IngredientInventory * ingredientInventory; // The ingredient inventory.
  public:
    /**
     * @brief Default constructor for IngredientInventory.
     */
    IngredientInventory();

    /**
     * @brief Constructor for uncountable items in IngredientInventory.
     * @param name The name of the ingredient.
     * @param cost The cost of the ingredient.
     * @param weight The weight of the ingredient.
     */
    IngredientInventory(string name, double cost, double weight);

    /**
     * @brief Constructor for countable items in IngredientInventory.
     * @param name The name of the ingredient.
     * @param cost The cost of the ingredient.
     * @param piece The number of pieces of the ingredient.
     */
    IngredientInventory(string name, double cost, int piece);
    
    // member functions
    /**
     * @brief Display the list of ingredients in the inventory.
     */
    void displayIngredientInventoryList() const;

    /**
     * @brief Access the details of a specific ingredient in the inventory.
     * @param index The index of the ingredient in the inventory.
     */
    void accessIngredientInventoryDetails(int index) const;

    /**
     * @brief Check the current inventory of ingredients.
     */
    void checkIngredientInventory() const;

    /**
     * @brief Add a new ingredient to the inventory with weight information.
     * @param name The name of the ingredient.
     * @param cost The cost of the ingredient.
     * @param weight The weight of the ingredient.
     */
    void addNewInventoryIngredientWeight(string name, double cost, double weight);

    /**
     * @brief Add a new ingredient to the inventory with piece information.
     * @param name The name of the ingredient.
     * @param cost The cost of the ingredient.
     * @param piece The number of pieces of the ingredient.
     */
    void addNewInventoryIngredientPiece(string name, double cost, int piece);

    /**
     * @brief Restock a specific ingredient in the inventory.
     * @param index The index of the ingredient in the inventory.
     * @param quantity The quantity of the ingredient to restock.
     * @return The remaining quantity of the ingredient after restocking.
     */
    double restockIngredientInventory(int index, double quantity);

    // mutator
    /**
     * @brief Change the cost of a specific ingredient in the inventory.
     * @param index The index of the ingredient in the inventory.
     * @param cost The new cost of the ingredient.
     */
    void changeIngredientCost(int index, double cost);

    /**
     * @brief Set the ingredient inventory.
     * @param ingredientInventory The ingredient inventory to set.
     */
    void setIngredientInventory(IngredientInventory * ingredientInventory);

    /**
     * @brief Set the number of pieces of a specific ingredient in the inventory.
     * @param index The index of the ingredient in the inventory.
     * @param piece The new number of pieces of the ingredient.
     */
    void setIngredientInventoryPiece(int index, int piece);

    /**
     * @brief Set the weight of a specific ingredient in the inventory.
     * @param index The index of the ingredient in the inventory.
     * @param weight The new weight of the ingredient.
     */
    void setIngredientInventoryWeight(int index, double weight);

    // accessor
    /**
     * @brief Get the ingredient inventory.
     * @return A pointer to the ingredient inventory.
     */
    static IngredientInventory * getIngredientInventory();

    /**
     * @brief Get the count of ingredients in the inventory.
     * @return The count of ingredients in the inventory.
     */
    int getIngredientInventoryCount() const;

    // /**
    //  * @brief Get the ingredient.
    //  * @return The ingredient.
    //  */
    // Ingredient getIngredient();

    /**
     * @brief Get a specific ingredient in the inventory.
     * @param index The index of the ingredient in the inventory.
     * @return A pointer to the specific ingredient in the inventory.
     */
    IngredientInventory * getIngredientInventory(int) const;

    /**
     * @brief Get the name of a specific ingredient in the inventory.
     * @param index The index of the ingredient in the inventory.
     * @return The name of the specific ingredient in the inventory.
     */
    string getIngredientInventoryName(int) const;

    /**
     * @brief Get the cost of a specific ingredient in the inventory.
     * @param index The index of the ingredient in the inventory.
     * @return The cost of the specific ingredient in the inventory.
     */
    double getIngredientInventoryCost(int) const;

    /**
     * @brief Get the number of pieces of a specific ingredient in the inventory.
     * @param index The index of the ingredient in the inventory.
     * @return The number of pieces of the specific ingredient in the inventory.
     */
    int getIngredientInventoryPiece(int) const;

    /**
     * @brief Get the weight of a specific ingredient in the inventory.
     * @param index The index of the ingredient in the inventory.
     * @return The weight of the specific ingredient in the inventory.
     */
    double getIngredientInventoryWeight(int) const;

    // destructor
    /**
     * @brief Destructor for IngredientInventory.
     */
    ~IngredientInventory();
};

#endif