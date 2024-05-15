#ifndef CONSTANT_H
#define CONSTANT_H

#include <iostream> // for input/output
#include <string> // for string

using namespace std;

/**
 * @file Constant.h
 * @brief Contains constants used in the program.
 */


/**
 * @namespace Constant
 * @brief  Contains constants used in the program.
 * 
 * This namespace contains constants that are used in the program, such as the maximum number of employees, bakery items, ingredients, and discounts.
 */
namespace Constant {
  /**
   * @brief Maximum number of employees.
   */
  static int MAX_EMPLOYEES = 10;

  /**
   * @brief Maximum number of bakery items.
   */
  static int MAX_BAKERY_ITEMS = 10;

  /**
   * @brief Maximum number of ingredients in the inventory.
   */
  static int MAX_INGREDIENTS_INVENTORY = 25;

  /**
   * @brief Maximum number of ingredients in a bakery item.
   */
  static int MAX_INGREDIENTS = 10;

  /**
   * @brief Maximum number of discounts.
   */
  static int MAX_DISCOUNTS = 5;
};

#endif