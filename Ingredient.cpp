#include <iomanip> // for input/output manipulation

#include "Ingredient.h" // Include the header file that contains the declaration of the Ingredient class.

/**
 * @file Ingredient.cpp
 * @brief Implementation file for the Ingredient class.
 */

/**
 * @class Ingredient
 * @brief Represents an ingredient used in a recipe.
 */


/**
 * @brief Default constructor for the Ingredient class.
 * 
 * @param None.
 * @return None.
 */
Ingredient::Ingredient() {
  name = "";
  costPerUnit = 0;
  weight = 0;
  piece = 0;
}

/**
 * @brief Constructs an Ingredient object with the given name, cost per unit, and weight.
 * 
 * @param name The name of the ingredient.
 * @param costPerUnit The cost per unit of the ingredient.
 * @param weight The weight of the ingredient.
 * 
 * @return None.
 */
Ingredient::Ingredient(string name, double costPerUnit, double weight) {
  // Check if the name is empty.
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if the cost per unit is negative.
  if (costPerUnit < 0) {
    cout << "Cost cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if the weight is negative.
  if (weight < 0) {
    cout << "Weight cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  this->name = name;
  this->costPerUnit = costPerUnit;
  this->weight = weight;
  this->piece = 0;
  this->countable = false; // The ingredient is uncountable.
}

/**
 * @brief Constructs an Ingredient object with the given name, cost per unit, and number of pieces.
 * 
 * @param name The name of the ingredient.
 * @param costPerUnit The cost per unit of the ingredient.
 * @param piece The number of pieces of the ingredient.
 * 
 * @return None.
 */
Ingredient::Ingredient(string name, double costPerUnit, int piece) {
  // Check if the name is empty.
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if the cost per unit is negative.
  if (costPerUnit < 0) {
    cout << "Cost cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if the number of pieces is negative.
  if (piece < 0) {
    cout << "Piece cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  this->name = name;
  this->costPerUnit = costPerUnit;
  this->weight = 0;
  this->piece = piece;
  this->countable = true; // The ingredient is countable.
}

/**
 * @brief Displays the details of the ingredient.
 * 
 * @param None.
 * @return None.
 */
void Ingredient::displayIngredientDetails() const {
  cout << "Name: " << name << endl;
  cout << fixed << "Cost: RM " << costPerUnit;

  // Check if the ingredient is countable.
  if (countable) {
    cout << " / piece(s)" << endl;
    cout << "Piece: " << piece << " piece(s)" << endl;
  } else {
    cout << " / gram(s)" << endl;
    cout << "Weight: " << weight << " gram(s)" << endl;
  }
}

/**
 * @brief Accessor for the name of the ingredient.
 * 
 * @param None.
 * @return The name of the ingredient.
 */
string Ingredient::getName() const {
  return name;
}

/**
 * @brief Accessor for the cost per unit of the ingredient.
 * 
 * @param None.
 * @return The cost per unit of the ingredient.
 */
double Ingredient::getCostPerUnit() const {
  return costPerUnit;
}

/**
 * @brief Accessor for the weight of the ingredient.
 * 
 * @param None.
 * @return The weight of the ingredient.
 */
double Ingredient::getWeight() const {
  return weight;
}

/**
 * @brief Accessor for the number of pieces of the ingredient.
 * 
 * @param None.
 * @return The number of pieces of the ingredient.
 */
int Ingredient::getPiece() const {
  return piece;
}

/**
 * @brief Accessor for the countable attribute of the ingredient.
 * 
 * @param None.
 * @return The countable attribute of the ingredient.
 */
bool Ingredient::getCountable() const {
  return countable;
}

/**
 * @brief Mutator for the cost per unit of the ingredient.
 * 
 * @param costPerUnit The new cost per unit of the ingredient.
 * @return None.
 */
void Ingredient::setCostPerUnit(double costPerUnit) {
  // Check if the cost per unit is negative.
  if (costPerUnit < 0) {
    cout << "Cost cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  this->costPerUnit = costPerUnit;
}

/**
 * @brief Mutator for the weight of the ingredient.
 * 
 * @param weight The new weight of the ingredient.
 * @return None.
 */
void Ingredient::setWeight(double weight) {
  // Check if the weight is negative.
  if (weight < 0) {
    cout << "Weight cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  this->weight = weight;
}

/**
 * @brief Mutator for the number of pieces of the ingredient.
 * 
 * @param piece The new number of pieces of the ingredient.
 * @return None.
 */
void Ingredient::setPiece(int piece) {
  // Check if the number of pieces is negative.
  if (piece < 0) {
    cout << "Piece cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  this->piece = piece;
}