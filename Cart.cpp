#include "Cart.h" // Include the header file that contains the declaration of the Cart class.

#include <iomanip> // for input/output manipulators

/**
 * @file Cart.cpp
 * @brief Implementation file for the Cart class.
 */

/**
 * @class Cart
 * @brief Represents a shopping cart for bakery items.
 */

/**
 * @brief Default constructor for the Cart class.
 * @param None
 * @return None
 */
Cart::Cart() {
  bakeryItems = new BakeryItem[Constant::MAX_BAKERY_ITEMS]; // Allocate memory for the bakery items array with the maximum number of bakery items
  quantity = new double[Constant::MAX_BAKERY_ITEMS]; // Allocate memory for the quantity array with the same size as the bakery items array
}

/**
 * @brief Displays the details of the items in the cart.
 * 
 * This function prints a table showing the item number, name, quantity, price per unit, and amount for each item in the cart.
 * It also calculates and displays the total price of all items in the cart.
 */
void Cart::displayCartDetails() {
  this->totalPrice = 0; // Reset the total price to zero

  // Display the header of the table
  cout << "+----+--------------------------+--------------------------+------------+------------------+" << endl;
  cout << "| " << setw(3) << left << "No" << "| " << setw(25) << left << "Name" << "| " << setw(25) << left << "Quantity" << "| " << setw(11) << left << "Price (RM)" << "| " << setw(16) << left << "Amount (RM)" << " |" << endl;
  cout << "+----+--------------------------+--------------------------+------------+------------------+" << endl;

  // Display the details of each item in the cart
  for (int i = 0; i < cartItemCount; i++) {
    cout << setprecision(2) << fixed;
    // check if quantity is a whole number
    if (quantity[i] == (int)quantity[i]) {
      // display quantity as a whole number
      string displayedQuantity = to_string((int)quantity[i]) + "x";
      cout << "| " << setw(3) << left << i+1 << "| " << setw(25) << left << bakeryItems[i].getBakeryItemName() << "| " << setw(25) << left << displayedQuantity << "| " << setw(11) << left << bakeryItems[i].getPricePerUnit() << "| " << setw(16) << left << bakeryItems[i].getPricePerUnit() * quantity[i] << " |" << endl;
    } else {
      // display quantity as a mixed number
      string displayedQuantity = (((int)quantity[i] != 0) ? (to_string((int)quantity[i]) + "x  +  ") : "") + to_string(((int)(quantity[i] * 1000) - ((int)quantity[i] * 1000))) + " g";
      cout << "| " << setw(3) << left << i+1 << "| " << setw(25) << left << bakeryItems[i].getBakeryItemName() << "| " << setw(25) << left << displayedQuantity << "| " << setw(11) << left << bakeryItems[i].getPricePerUnit() << "| " << setw(16) << left << bakeryItems[i].getPricePerUnit() * quantity[i] << " |" << endl;
    }
  }
  cout << "+----+--------------------------+--------------------------+------------+------------------+" << endl;
  // Display the total price of all items in the cart
  cout << "Total Price: RM " << setprecision(2) << fixed << this->calculateTotalPrice() << endl;
}

/**
 * @brief Adds a bakery item to the cart with the specified quantity.
 * 
 * @param item The bakery item to be added to the cart.
 * @param quantity The quantity of the bakery item to be added.
 * 
 * @return None.
 */
void Cart::addBakeryItemToCart(BakeryItem & item, int quantity) {
  // Check if the cart is full
  if (cartItemCount >= Constant::MAX_BAKERY_ITEMS) {
    cout << "Cart is full." << endl;
    return;
  }

  // Add the bakery item to the cart
  // Set the bakery item at the current cart item count to the specified item
  // Set the quantity at the current cart item count to the specified quantity
  // Increment the cart item count
  bakeryItems[cartItemCount] = item;
  this->quantity[cartItemCount] = quantity;
  cartItemCount++;

  // Display a message indicating that the item has been added to the cart
  // cout << item.getBakeryItemName() << " added to cart." << endl; // already display in employee.cpp
}

/**
 * @brief Adds a cake to the cart by weight.
 * 
 * This function adds a cake to the cart based on the specified weight. If the cart is already full, it displays a message and returns.
 * 
 * @param item The BakeryItem object representing the cake to be added.
 * @param weight The weight of the cake to be added.
 * 
 * @return None.
 * 
 * @note The function assumes that the BakeryItem object passed as a parameter is valid and has a valid Cake object associated with it.
 */
void Cart::addCakeByWeightToCart(BakeryItem & item, double weight) {
  // Check if the cart is full
  if (cartItemCount >= Constant::MAX_BAKERY_ITEMS) {
    cout << "Cart is full." << endl;
    return;
  }

  // Add the cake to the cart
  // Set the bakery item at the current cart item count to the specified item
  // Set the quantity at the current cart item count to the specified weight divided by the total weight of the cake
  // Increment the cart item count
  bakeryItems[cartItemCount] = item;
  this->quantity[cartItemCount] = weight / item.getCake()->getTotalWeight();
  cartItemCount++;

  // Display a message indicating that the item has been added to the cart
  cout << item.getBakeryItemName() << " added to cart." << endl;
}

/**
 * @brief Removes a bakery item from the cart at the specified index.
 * 
 * @param index The index of the bakery item to be removed.
 * @return None.
 * 
 * @note If the index is invalid (less than 0 or greater than or equal to the cart item count),
 *       an error message will be displayed and no item will be removed.
 */
void Cart::removeBakeryItemFromCart(int index) {
  // Check if the index is valid
  if (index < 0 || index >= cartItemCount) {
    cout << "Invalid index." << endl;
    return;
  }

  // Remove the bakery item at the specified index
  // Shift all items after the specified index to the left by one position
  for (int i = index; i < cartItemCount - 1; i++) {
    bakeryItems[i] = bakeryItems[i + 1];
    quantity[i] = quantity[i + 1];
  }

  // Decrement the cart item count
  cartItemCount--;
}

/**
 * @brief Updates the quantity of a bakery item in the cart.
 * 
 * This function updates the quantity of a bakery item at the specified index in the cart.
 * 
 * @param index The index of the bakery item in the cart.
 * @param quantity The new quantity of the bakery item.
 * 
 * @return None.
 */
void Cart::updateBakeryItemQuantity(int index, int quantity) {
  // Check if the index is valid
  if (index < 0 || index >= cartItemCount) {
    cout << "Invalid index." << endl;
    return;
  }

  // Update the quantity of the bakery item at the specified index
  this->quantity[index] = quantity;
}

/**
 * @brief Clears the cart by resetting all variables.
 * 
 * @param None.
 * @return None.
 */
void Cart::clearCart() {
  cartItemCount = 0;
  totalCost = 0;
  totalPrice = 0;
  totalProfit = 0;
  totalDiscount = 0;
}

/**
 * @brief Calculates the total cost of all items in the cart.
 * 
 * This function iterates through each item in the cart and calculates the cost
 * by multiplying the cost of the item with its quantity. The total cost is then
 * updated and returned.
 * 
 * @return The total cost of all items in the cart.
 */
double Cart::calculateTotalCost() {
  // Reset the total cost to zero
  totalCost = 0;

  // Calculate the total cost of all items in the cart
  for (int i = 0; i < cartItemCount; i++) {
    // Calculate the cost of the item by multiplying the cost per unit with the quantity
    totalCost += bakeryItems[i].calculateCost() * quantity[i];
  }

  // Return the total cost
  return totalCost;
}

/**
 * @brief Calculates the total price of all items in the cart.
 * 
 * This function iterates through each item in the cart and multiplies the price per unit
 * with the quantity of each item. The total price is then calculated by summing up the individual
 * prices of all items.
 * 
 * @return The total price of all items in the cart.
 */
double Cart::calculateTotalPrice() {
  // Reset the total price to zero
  totalPrice = 0;

  // Calculate the total price of all items in the cart
  for (int i = 0; i < cartItemCount; i++) {
    // Calculate the price of the item by multiplying the price per unit with the quantity
    totalPrice += bakeryItems[i].getPricePerUnit() * quantity[i];
  }
  
  // Return the total price
  return totalPrice;
}

/**
 * @brief Calculates the total profit of the items in the cart.
 * 
 * This function iterates through each item in the cart and calculates the profit
 * by multiplying the profit of each item with its quantity. The total profit is
 * then returned.
 * 
 * @return The total profit of the items in the cart.
 */
double Cart::calculateTotalProfit() {
  // Reset the total profit to zero
  totalProfit = 0;

  // Calculate the total profit of all items in the cart
  for (int i = 0; i < cartItemCount; i++) {
    // Calculate the profit of the item by multiplying the profit with the quantity
    totalProfit += bakeryItems[i].calculateProfit() * quantity[i];
  }

  // Return the total profit
  return totalProfit;
}

int Cart::getCartItemCount() const {
  return cartItemCount;
}

/**
 * @brief Get the array of BakeryItems in the Cart.
 * 
 * @return A pointer to the array of BakeryItems.
 */
BakeryItem * Cart::getBakeryItems() const {
  return bakeryItems;
}

/**
 * @brief Get the quantity of the cart.
 * 
 * @return A pointer to the quantity of the cart.
 */
double * Cart::getQuantity() const {
  return quantity;
}

/**
 * @brief Get the total cost of the cart.
 * 
 * @return The total cost of the cart as a double.
 */
double Cart::getTotalCost() const {
  return totalCost;
}

/**
 * @brief Get the total price of the cart.
 * 
 * @return The total price of the cart as a double.
 */
double Cart::getTotalPrice() const {
  return totalPrice;
}

/**
 * @brief Get the total profit of the cart.
 * 
 * @return The total profit of the cart as a double.
 */
double Cart::getTotalProfit() const {
  return totalProfit;
}

/**
 * @brief Get the total discount of the cart.
 *
 * @return The total discount of the cart as a double.
 */
double Cart::getTotalDiscount() const {
  return totalDiscount;
}

/**
 * @brief Sets the bakery items in the cart.
 * 
 * This function sets the bakery items in the cart to the specified array of BakeryItem objects.
 * 
 * @param bakeryItems The array of BakeryItem objects to be set in the cart.
 */
void Cart::setBakeryItems(BakeryItem * bakeryItems) {
  this->bakeryItems = bakeryItems;
}

/**
 * @brief Sets the quantity of the cart.
 * 
 * @param quantity A pointer to the quantity value to be set.
 */
void Cart::setQuantity(double * quantity) {
  this->quantity = quantity;
}

/**
 * @brief Sets the number of items in the cart.
 *
 * This function sets the number of items in the cart to the specified value.
 *
 * @param cartItemCount The number of items to set in the cart.
 *
 * @return None.
 */
void Cart::setCartItemCount(int cartItemCount) {
  this->cartItemCount = cartItemCount;
}

/**
 * @brief Sets the total cost of the cart.
 * 
 * @param totalCost The total cost of the cart.
 * 
 * @return None.
 */
void Cart::setTotalCost(double totalCost) {
  this->totalCost = totalCost;
}

/**
 * @brief Sets the total price of the cart.
 * 
 * @param totalPrice The total price to be set.
 */
void Cart::setTotalPrice(double totalPrice) {
  this->totalPrice = totalPrice;
}

/**
 * @brief Sets the total profit of the cart.
 * 
 * @param totalProfit The total profit to be set.
 */
void Cart::setTotalProfit(double totalProfit) {
  this->totalProfit = totalProfit;
}

/**
 * @brief Sets the total discount for the cart.
 * 
 * @param totalDiscount The total discount to be set.
 */
void Cart::setTotalDiscount(double totalDiscount) {
  this->totalDiscount = totalDiscount;
}

/**
 * @brief Destructor for the Cart class.
 * 
 * This destructor is responsible for freeing the memory allocated for the bakeryItems and quantity arrays.
 * 
 * @param None.
 * @return None.
 */
Cart::~Cart() {
  // Free the memory allocated for the bakeryItems and quantity arrays
  delete [] bakeryItems;
  delete [] quantity;
}