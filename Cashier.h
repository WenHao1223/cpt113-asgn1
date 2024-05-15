#ifndef CASHIER_H
#define CASHIER_H

#include <iostream> // for input/output
#include <string> // for string

#include "Cart.h" // Include the Cart header file.

using namespace std;

/**
 * @file Cashier.h
 * @brief Defines the Cashier class, which represents a cashier in a bakery.
 */

/**
 * 
 * @class Cashier
 * @brief  Represents a cashier in a bakery.
 * 
 * The Cashier class contains information about a cashier, such as their employee ID and name,
 * and provides functionality to start and close the bakery operations.
 * The Cashier class also contains a pointer to the Cart object, which represents the shopping cart
 * used by the cashier to add bakery items.
 * 
 * The Cashier class is responsible for managing the cart and performing operations such as adding
 * items to the cart, displaying cart details, and calculating the total cost of the items in the cart.
 * 
 * The Cashier class interacts with the Cart class to perform these operations.
 * 
 */
class Cashier {
  private:
    string employeeID; // The ID of the cashier.
    string name; // The name of the cashier.
    Cart * cart = nullptr; // A pointer to the Cart object.
  public:
    /**
     * @brief Constructor for the Cashier class.
     * 
     * @param employeeID The ID of the cashier.
     * @param name The name of the cashier.
     */
    Cashier(string employeeID, string name);

    /**
     * @brief Starts the bakery operations.
     */
    void startBakery();

    /**
     * @brief Closes the bakery operations.
     */
    void closeBakery();

    /**
     * @brief Accessor method to get the cart.
     * 
     * @return A pointer to the Cart object.
     */
    Cart * getCart();

    /**
      * @brief Overloaded assignment operator for the Cashier class.
      * 
      * This operator assigns the cart of the given cashier to the current cashier.
      * 
      * @param c The cashier object to copy the cart from.
      * @return A reference to the current cashier object.
      */
    Cashier & operator=(const Cashier & c);

    /**
     * @brief Destructor for the Cashier class.
     */
    ~Cashier();
};

#endif