#include "Baker.h" // Include the header file that contains the declaration of the Baker class.

/**
 * @file Baker.cpp
 * @brief Implementation file for the Baker class.
 */

/**
 * @brief Constructs a new Baker object with the given employee ID and name.
 * 
 * @param employeeID The ID of the baker employee.
 * @param name The name of the baker employee.
 */
Baker::Baker(string employeeID, string name) {
  this->employeeID = employeeID;
  this->name = name;
}

/**
 * @brief Starts the bakery.
 * 
 * This function prints a message indicating that the baker has started the bakery.
 */
void Baker::startBakery() {
  cout << "Baker " << name << " (" << employeeID << ") starts the bakery." << endl;
}

/**
 * @brief Closes the bakery.
 * 
 * Prints a message indicating that the baker is closing the bakery.
 */
void Baker::closeBakery() {
  cout << "Baker " << name << " (" << employeeID << ") closes the bakery." << endl;
}