#ifndef CART_H
#define CART_H

#include <iostream> // for input/output
#include <string> // for string
#include "BakeryItem.h" // Include the BakeryItem header file

using namespace std;

/**
 * @file Cart.h
 * @brief This file contains the declaration of the Cart class.
 */

/**
 * @class Cart
 * @brief Represents a shopping cart for bakery items.
 * 
 * The Cart class stores information about the bakery items added to the cart,
 * such as the item details, quantity, and cost. It provides various member functions
 * to add, remove, and update items in the cart, as well as calculate the total cost,
 * price, and profit of the items in the cart.
 */
/**
 * @brief The Cart class represents a shopping cart for bakery items.
 */
class Cart {
  private:
    BakeryItem * bakeryItems; // Array of bakery items in the cart
    double * quantity; // Array of quantities corresponding to each bakery item
    int cartItemCount = 0; // Number of items in the cart
    double totalCost = 0; // Total cost of all items in the cart
    double totalProfit = 0; // Total profit from selling all items in the cart
    double totalPrice = 0; // Total price of all items in the cart (including discounts)
    double totalDiscount = 0; // Total discount applied to the cart
    static Cart * cart; // Singleton instance of the Cart class

  public:
    // Constructor
    Cart();

    // member functions
    /**
     * @brief Displays the details of all items in the cart.
     */
    void displayCartDetails();

    /**
     * @brief Adds a bakery item to the cart with the specified quantity.
     * @param item The bakery item to add.
     * @param quantity The quantity of the bakery item to add.
     */
    void addBakeryItemToCart(BakeryItem & item, int quantity);

    /**
     * @brief Adds a cake by weight to the cart.
     * @param item The bakery item (cake) to add.
     * @param weight The weight of the cake to add.
     */
    void addCakeByWeightToCart(BakeryItem & item, double weight);

    /**
     * @brief Removes a bakery item from the cart at the specified index.
     * @param index The index of the bakery item to remove.
     */
    void removeBakeryItemFromCart(int index);

    /**
     * @brief Updates the quantity of a bakery item in the cart at the specified index.
     * @param index The index of the bakery item to update.
     * @param quantity The new quantity of the bakery item.
     */
    void updateBakeryItemQuantity(int index, double quantity);

    /**
     * @brief Clears the cart by removing all items.
     */
    void clearCart();

    /**
     * @brief Calculates the total cost of all items in the cart.
     * @return The total cost of all items in the cart.
     */
    double calculateTotalCost();

    /**
     * @brief Calculates the total price of all items in the cart (including discounts).
     * @return The total price of all items in the cart.
     */
    double calculateTotalPrice();

    /**
     * @brief Calculates the total profit from selling all items in the cart.
     * @return The total profit from selling all items in the cart.
     */
    double calculateTotalProfit();

    // accessor
    /**
     * @brief Gets the number of items in the cart.
     * @return The number of items in the cart.
     */
    int getCartItemCount() const;

    /**
     * @brief Gets the array of bakery items in the cart.
     * @return The array of bakery items in the cart.
     */
    BakeryItem * getBakeryItems() const;

    /**
     * @brief Gets the array of quantities corresponding to each bakery item in the cart.
     * @return The array of quantities corresponding to each bakery item in the cart.
     */
    double * getQuantity() const;

    /**
     * @brief Gets the total cost of all items in the cart.
     * @return The total cost of all items in the cart.
     */
    double getTotalCost() const;

    /**
     * @brief Gets the total price of all items in the cart (including discounts).
     * @return The total price of all items in the cart.
     */
    double getTotalPrice() const;

    /**
     * @brief Gets the total profit from selling all items in the cart.
     * @return The total profit from selling all items in the cart.
     */
    double getTotalProfit() const;

    /**
     * @brief Gets the total discount applied to the cart.
     * @return The total discount applied to the cart.
     */
    double getTotalDiscount() const;

    // mutator
    /**
     * @brief Sets the array of bakery items in the cart.
     * @param bakeryItems The array of bakery items to set.
     */
    void setBakeryItems(BakeryItem * bakeryItems);

    /**
     * @brief Sets the array of quantities corresponding to each bakery item in the cart.
     * @param quantity The array of quantities to set.
     */
    void setQuantity(double * quantity);

    /**
     * @brief Sets the number of items in the cart.
     * @param cartItemCount The number of items to set.
     */
    void setCartItemCount(int cartItemCount);

    /**
     * @brief Sets the total cost of all items in the cart.
     * @param totalCost The total cost to set.
     */
    void setTotalCost(double totalCost);

    /**
     * @brief Sets the total price of all items in the cart (including discounts).
     * @param totalPrice The total price to set.
     */
    void setTotalPrice(double totalPrice);

    /**
     * @brief Sets the total profit from selling all items in the cart.
     * @param totalProfit The total profit to set.
     */
    void setTotalProfit(double totalProfit);

    /**
     * @brief Sets the total discount applied to the cart.
     * @param totalDiscount The total discount to set.
     */
    void setTotalDiscount(double totalDiscount);

    // destructor
    /**
     * @brief Destructor for the Cart class.
     */
    ~Cart();
};

#endif