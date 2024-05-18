#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <iostream> // for input/output
#include <string> // for string

#include "Constant.h" // for Constant namespace

using namespace std;

/**
 * @file Discount.h
 * @brief Contains the declaration of the Discount class.
 */

/**
 * @class Discount
 * @brief Represents a discount that can be applied to a purchase.
 * 
 * The Discount class stores information about a discount, including its name, minimum purchase amount, discount percentage, and description.
 * It also provides functionality to enable or disable the discount.
 * 
 * The Discount class is used to create and manage discounts that can be applied to a purchase in a bakery.
 * Discounts can be applied based on the total purchase amount, and can help attract customers by offering them savings on their purchases.
 * 
 * The Discount class is used in conjunction with the Cart class to calculate the total price of items in the cart after applying any discounts.
 * 
 * The Discount class is also used in the Bakery class to manage the discounts available in the bakery.
 * 
 * The Discount class is part of the core functionality of the bakery management system. 
 */
class Discount {
  private:
    string name; // The name of the discount.
    double minimumPurchase = 0.0; // The minimum purchase amount required to apply the discount.
    double discountPercentage; // The percentage of discount to be applied.
    string description; // The description of the discount.
    bool disabled = false; // Indicates whether the discount is disabled or not.
    static int discountCount; // The count of total discounts created.

  public:
    /**
     * @brief Default constructor for the Discount class.
     */
    Discount();

    /**
     * @brief Parameterized constructor for the Discount class.
     * @param name The name of the discount.
     * @param minimumPurchase The minimum purchase amount required to apply the discount.
     * @param discountPercentage The percentage of discount to be applied.
     * @param description The description of the discount.
     */
    Discount(string name, double minimumPurchase, double discountPercentage, string description);

    /**
     * @brief Parameterized constructor for the Discount class.
     * @param name The name of the discount.
     * @param minimumPurchase The minimum purchase amount required to apply the discount.
     * @param discountPercentage The percentage of discount to be applied.
     * @param description The description of the discount.
     * @param disabled Indicates whether the discount is disabled or not.
     */
    Discount(string name, double minimumPurchase, double discountPercentage, string description, bool disabled);

    /**
     * @brief Displays the details of the discount.
     */
    void displayDiscountDetails() const;

    /**
     * @brief Enables the discount.
     */
    void enableDiscount();

    /**
     * @brief Disables the discount.
     */
    void disableDiscount();

    /**
     * @brief Accessor for the name of the discount.
     * @return The name of the discount.
     */
    string getName() const;

    /**
     * @brief Accessor for the minimum purchase amount required to apply the discount.
     * @return The minimum purchase amount required to apply the discount.
     */
    double getMinimumPurchase() const;

    /**
     * @brief Accessor for the percentage of discount to be applied.
     * @return The percentage of discount to be applied.
     */
    double getDiscountPercentage() const;

    /**
     * @brief Accessor for the description of the discount.
     * @return The description of the discount.
     */
    string getDescription() const;

    /**
     * @brief Accessor for the disabled status of the discount.
     * @return True if the discount is disabled, false otherwise.
     */
    bool getDisabled() const;

    /**
     * @brief Accessor for the count of total discounts created.
     * @return The count of total discounts created.
     */
    int getDiscountCount() const;

    /**
     * @brief Mutator for the name of the discount.
     * @param name The new name of the discount.
     */
    void setName(string name);

    /**
     * @brief Mutator for the minimum purchase amount required to apply the discount.
     * @param minimumPurchase The new minimum purchase amount required to apply the discount.
     */
    void setMinimumPurchase(double minimumPurchase);

    /**
     * @brief Mutator for the percentage of discount to be applied.
     * @param discountPercentage The new percentage of discount to be applied.
     */
    void setDiscountPercentage(double discountPercentage);

    /**
     * @brief Mutator for the description of the discount.
     * @param description The new description of the discount.
     */
    void setDescription(string description);

    /**
     * @brief Mutator for the disabled status of the discount.
     * @param disabled The new disabled status of the discount.
     */
    void setDisabled(bool disabled);

    /**
     * @brief Destructor for the Discount class.
     */
    ~Discount();
};

#endif