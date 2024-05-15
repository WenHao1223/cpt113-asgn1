#include "Discount.h" // Include the header file that contains the declaration of the Discount class.

#include <iostream> // for input/output

/**
 * @file Discount.cpp
 * @brief Implementation of the Discount class.
 */

/**
 * @class Discount
 * @brief Represents a discount for a purchase.
 */


/**
 * @brief Default constructor for the Discount class.
 */
Discount::Discount() {}

/**
 * @brief Constructs a Discount object with the specified parameters.
 * @param name The name of the discount.
 * @param minimumPurchase The minimum purchase amount required to apply the discount.
 * @param discountPercentage The percentage of discount to be applied.
 * @param description The description of the discount.
 * @return None.
 */
Discount::Discount(string name, double minimumPurchase, double discountPercentage, string description) {
  this->name = name;
  this->minimumPurchase = minimumPurchase;
  this->discountPercentage = discountPercentage;
  this->description = description;

  // Increment the discount count.
  discountCount++;
}

/**
 * @brief Constructs a Discount object with the specified parameters.
 * @param name The name of the discount.
 * @param minimumPurchase The minimum purchase amount required to apply the discount.
 * @param discountPercentage The percentage of discount to be applied.
 * @param description The description of the discount.
 * @param disabled Indicates whether the discount is disabled or not.
 * @return None.
 */
Discount::Discount(string name, double minimumPurchase, double discountPercentage, string description, bool disabled) {
  this->name = name;
  this->minimumPurchase = minimumPurchase;
  this->discountPercentage = discountPercentage;
  this->description = description;
  this->disabled = disabled;

  // Increment the discount count.
  discountCount++;
}

/**
 * @brief Displays the details of the discount.
 * @return None.
 */
void Discount::displayDiscountDetails() const {
  cout << "Discount Name: " << this->name << endl;
  cout << "Discount Percentage: " << this->discountPercentage << "%" << endl;
  cout << "Description: " << this->description << endl;
  cout << "Disabled: " << (this->disabled ? "Yes" : "No") << endl;
}

/**
 * @brief Enables the discount.
 * @return None.
 */
void Discount::enableDiscount() {
  this->disabled = false;
}

/**
 * @brief Disables the discount.
 * @return None.
 */
void Discount::disableDiscount() {
  this->disabled = true;
}

/**
 * @brief Returns the name of the discount.
 * @return The name of the discount.
 */
string Discount::getName() const {
  return this->name;
}

/**
 * @brief Returns the minimum purchase amount required to apply the discount.
 * @return The minimum purchase amount required to apply the discount.
 */
double Discount::getMinimumPurchase() const {
  return this->minimumPurchase;
}

/**
 * @brief Returns the percentage of discount to be applied.
 * @return The percentage of discount to be applied.
 */
double Discount::getDiscountPercentage() const {
  return this->discountPercentage;
}

/**
 * @brief Returns the description of the discount.
 * @return The description of the discount.
 */
string Discount::getDescription() const {
  return this->description;
}

/**
 * @brief Returns whether the discount is disabled or not.
 * @return True if the discount is disabled, false otherwise.
 */
bool Discount::getDisabled() const {
  return this->disabled;
}

/**
 * @brief Returns the total number of discounts.
 * @return The total number of discounts.
 */
int Discount::getDiscountCount() const {
  return discountCount;
}

/**
 * @brief Sets the name of the discount.
 * @param name The name of the discount.
 * @return None.
 */
void Discount::setName(string name) {
  this->name = name;
}

/**
 * @brief Sets the minimum purchase amount required to apply the discount.
 * @param minimumPurchase The minimum purchase amount required to apply the discount.
 * @return None.
 */
void Discount::setMinimumPurchase(double minimumPurchase) {
  this->minimumPurchase = minimumPurchase;
}

/**
 * @brief Sets the percentage of discount to be applied.
 * @param discountPercentage The percentage of discount to be applied.
 * @return None.
 */
void Discount::setDiscountPercentage(double discountPercentage) {
  this->discountPercentage = discountPercentage;
}

/**
 * @brief Sets the description of the discount.
 * @param description The description of the discount.
 * @return None.
 */
void Discount::setDescription(string description) {
  this->description = description;
}

/**
 * @brief Sets whether the discount is disabled or not.
 * @param disabled True if the discount is disabled, false otherwise.
 * @return None.
 */
void Discount::setDisabled(bool disabled) {
  this->disabled = disabled;
}

/**
 * @brief Destructor for the Discount class.
 */
Discount::~Discount() {
  // cout << "Discount object destroyed." << endl;
}

int Discount::discountCount = 0; // Initialize the static member variable discountCount.