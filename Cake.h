#ifndef CAKE_H
#define CAKE_H

#include <iostream> // for cout and cin
#include <string> // for string

using namespace std;

/**
 * @file Cake.h
 * @brief This file contains the declaration of the Cake class.
 */

/**
 * @class Cake
 * @brief Represents a cake object.
 * 
 * The Cake class stores information about a cake, including its total weight.
 */
class Cake {
  private:
    int totalWeight; /**< The total weight of the cake. */

  public:
    /**
     * @brief Default constructor for the Cake class.
     * 
     * Initializes the total weight of the cake to 0.
     */
    Cake();

    /**
     * @brief Parameterized constructor for the Cake class.
     * 
     * @param totalWeight The total weight of the cake.
     */
    Cake(int totalWeight);

    /**
     * @brief Accessor method to get the total weight of the cake.
     * 
     * @return The total weight of the cake.
     */
    int getTotalWeight() const;
};

#endif