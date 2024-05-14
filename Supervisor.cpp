#include "Supervisor.h" // Include the header file that contains the declaration of the Supervisor class.

/**
 * @file Supervisor.cpp
 * @brief Implementation file for the Supervisor class.
 */

/**
 * @class Supervisor
 * @brief Represents a supervisor in the organization.
 */
 
/**
 * @brief Constructor for the Supervisor class.
 * @param employeeID The ID of the supervisor.
 * @param name The name of the supervisor.
 */
Supervisor::Supervisor(string employeeID, string name) {
  this->employeeID = employeeID;
  this->name = name;
  // cout << "Supervisor " << name << " has been added." << endl;
}

/**
 * @brief Starts the bakery.
 * 
 * This function prints a message indicating that the supervisor has started the bakery.
 */
void Supervisor::startBakery() {
  cout << "Supervisor " << name << " (" << employeeID << ") starts the bakery." << endl;
}

/**
 * @brief Closes the bakery.
 * This function prints a message indicating that the supervisor is closing the bakery.
 */
void Supervisor::closeBakery() {
  cout << "Supervisor " << name << " (" << employeeID << ") closes the bakery." << endl;
}