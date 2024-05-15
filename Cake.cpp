#include "Cake.h" // Include the header file for the Cake class.

/**
 * @file Cake.cpp
 * @brief Implementation file for the Cake class.
 */

/**
 * @class Cake
 * @brief Represents a cake object.
 */

/**
 * @brief Default constructor for the Cake class.
 * 
 * This constructor initializes the total weight of the cake to 0.
 */
Cake::Cake() {
  totalWeight = 0;
}

/**
 * @brief Constructs a Cake object with the specified total weight.
 * @param totalWeight The total weight of the cake.
 */
Cake::Cake(int totalWeight) {
  // Check if the total weight is zero or negative.
  if (totalWeight <= 0) {
    cout << "Total weight cannot be zero or negative." << endl;
    cout << "Total weight: " << totalWeight << endl;
    exit(EXIT_FAILURE); // Exit the program.
    return;
  }
  
  this->totalWeight = totalWeight; // Set the total weight of the cake.
}

/**
 * Returns the total weight of the cake.
 *
 * @return The total weight of the cake.
 */
int Cake::getTotalWeight() const {
  return totalWeight;
}