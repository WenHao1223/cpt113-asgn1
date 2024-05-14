#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <iostream> // for input/output
#include <string> // for string

using namespace std;

/**
 * @file Supervisor.h
 * @brief Contains the declaration of the Supervisor class.
 */

/**
 * @class Supervisor
 * @brief Represents a supervisor in a bakery.
 * 
 * The Supervisor class contains information about a supervisor, such as their employee ID and name,
 * and provides functionality to start and close the bakery operations.
 * The Supervisor class is responsible for managing the overall operations of the bakery.
 * 
 * The Supervisor class interacts with the Cashier, Baker, and Inventory classes to perform these operations.
 * 
 * The Supervisor class is responsible for managing the bakery operations.
 * 
 */
class Supervisor {
  private:
    string employeeID; // The employee ID of the supervisor.
    string name; // The name of the supervisor.
        
  public:
    /**
     * @brief Constructor for the Supervisor class.
     * @param employeeID The employee ID of the supervisor.
     * @param name The name of the supervisor.
     */
    Supervisor(string employeeID, string name);

    /**
     * @brief Starts the bakery operations.
     */
    void startBakery();

    /**
     * @brief Closes the bakery operations.
     */
    void closeBakery();
};

#endif