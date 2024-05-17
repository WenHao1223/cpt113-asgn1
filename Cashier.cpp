#include "Cashier.h" // Include the header file that contains the declaration of the Cashier class.

/**
 * @file Cashier.cpp
 * @brief Implementation file for the Cashier class.
 */

/**
 * @brief Constructs a Cashier object with the given employee ID and name.
 * 
 * @param employeeID The ID of the cashier employee.
 * @param name The name of the cashier employee.
 */
Cashier::Cashier(string employeeID, string name) {
  this->employeeID = employeeID; // Set the employee ID of the cashier.
  this->name = name; // Set the name of the cashier.
  this->cart = new Cart(); // Create a new cart object for the cashier.
}

/**
 * @brief Starts the bakery for the cashier.
 * 
 * This function prints a message indicating that the cashier has started the bakery.
 */
void Cashier::startBakery() {
  cout << "Cashier " << name << " (" << employeeID << ") starts the bakery." << endl;
}

/**
 * @brief Closes the bakery.
 * 
 * This function prints a message indicating that the cashier is closing the bakery.
 */
void Cashier::closeBakery() {
  cout << "Cashier " << name << " (" << employeeID << ") closes the bakery." << endl;
}

/**
 * @brief Retrieves the cart associated with the cashier.
 *
 * @return A pointer to the cart object.
 */
Cart * Cashier::getCart() {
  return cart;
}

/**
 * @brief Overloaded assignment operator for the Cashier class.
 * 
 * This operator assigns the cart of the given cashier to the current cashier.
 * 
 * @param c The cashier object to copy the cart from.
 * @return A reference to the current cashier object.
 */
Cashier & Cashier::operator=(const Cashier & c) {
  // cout << "Assignment operator called." << endl;
  this->cart = new Cart(*(c.cart)); // deep copy cart

  // clear cart
  c.cart->clearCart();

  return *this;
}

/**
 * @brief Destructor for the Cashier class.
 * 
 * Deletes the dynamically allocated cart object.
 */
Cashier::~Cashier() {
  delete cart;
}