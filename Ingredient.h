#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <iostream> // for input/output
#include <string> // for string

using namespace std;

/**
 * @file Ingredient.h
 * @brief This file contains the declaration of the Ingredient class.
 */

/**
 * @class Ingredient
 * @brief The Ingredient class represents an ingredient used in a recipe.
 */
class Ingredient {
  private:
    string name; // The name of the ingredient.
    double costPerUnit; // The cost per unit of the ingredient.
    double weight; // The weight of the ingredient.
    int piece; // The number of pieces of the ingredient.
    bool countable; // Indicates whether the ingredient is countable or not.
    
  public:
    /**
     * @brief Default constructor for the Ingredient class.
     */
    Ingredient();

    /**
     * @brief Constructor for uncountable items.
     * @param name The name of the ingredient.
     * @param costPerUnit The cost per unit of the ingredient.
     * @param weight The weight of the ingredient.
     */
    Ingredient(string name, double costPerUnit, double weight);

    /**
     * @brief Constructor for countable items.
     * @param name The name of the ingredient.
     * @param costPerUnit The cost per unit of the ingredient.
     * @param piece The number of pieces of the ingredient.
     */
    Ingredient(string name, double costPerUnit, int piece);

    /**
     * @brief Displays the details of the ingredient.
     */
    void displayIngredientDetails() const;

    /**
     * @brief Accessor for the name of the ingredient.
     * @return The name of the ingredient.
     */
    string getName() const;

    /**
     * @brief Accessor for the cost per unit of the ingredient.
     * @return The cost per unit of the ingredient.
     */
    double getCostPerUnit() const;

    /**
     * @brief Accessor for the weight of the ingredient.
     * @return The weight of the ingredient.
     */
    double getWeight() const;

    /**
     * @brief Accessor for the number of pieces of the ingredient.
     * @return The number of pieces of the ingredient.
     */
    int getPiece() const;

    /**
     * @brief Accessor for the countable status of the ingredient.
     * @return True if the ingredient is countable, false otherwise.
     */
    bool getCountable() const;

    /**
     * @brief Mutator for the cost per unit of the ingredient.
     * @param costPerUnit The new cost per unit of the ingredient.
     */
    void setCostPerUnit(double costPerUnit);

    /**
     * @brief Mutator for the weight of the ingredient.
     * @param weight The new weight of the ingredient.
     */
    void setWeight(double weight);

    /**
     * @brief Mutator for the number of pieces of the ingredient.
     * @param piece The new number of pieces of the ingredient.
     */
    void setPiece(int piece);
};

#endif