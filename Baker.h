#ifndef BAKER_H
#define BAKER_H

#include <string> // for input/output
#include <iostream> // for cout and cin

using namespace std;

/**
 * @file Baker.h
 * @brief Contains the declaration of the Baker class.
 */

/**
 * @class Baker
 * @brief Represents a baker in a bakery.
 * 
 * The Baker class contains information about a baker, such as their employee ID and name,
 * and provides functionality to start and close the bakery.
 */
class Baker {
  private:
    string employeeID; // The employee ID of the baker.
    string name; // The name of the baker.
        
  public:
    /**
     * @brief Constructor for the Baker class.
     * @param employeeID The employee ID of the baker.
     * @param name The name of the baker.
     */
    Baker(string employeeID, string name);

    /**
     * @brief Starts the bakery.
     * 
     * This function performs the necessary actions to start the bakery, such as turning on
     * the ovens and preparing the ingredients.
     */
    void startBakery();

    /**
     * @brief Closes the bakery.
     * 
     * This function performs the necessary actions to close the bakery, such as turning off
     * the ovens and cleaning up the workspace.
     */
    void closeBakery();
};

#endif