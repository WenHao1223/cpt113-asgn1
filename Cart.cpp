#include "Cart.h"

#include <iomanip>

Cart::Cart() {
  bakeryItems = new BakeryItem[Constant::MAX_BAKERY_ITEMS];
  quantity = new int[Constant::MAX_BAKERY_ITEMS];
}

Cart::Cart(BakeryItem * bakeryItems, int * quantity, int cartItemCount, double totalCost, double totalProfit) {
  this->bakeryItems = bakeryItems;
  this->quantity = quantity;
  this->cartItemCount = cartItemCount;
  this->totalCost = totalCost;
  this->totalProfit = totalProfit;
}

void Cart::displayCartDetails() const {
  cout << "Cart Items: " << endl;
  // for (int i = 0; i < cartItemCount; i++) {
  //   cout << i + 1 << ". ";
  //   bakeryItems[i].displayBakeryItemDetails();
  //   cout << "Quantity: " << quantity[i] << endl;
  //   cout << "Total Cost: " << bakeryItems[i].calculateCost() * quantity[i] << endl;
  //   cout << "Total Profit: " << bakeryItems[i].calculateProfit() * quantity[i] << endl;
  // }
  // cout << "Total Cost: " << totalCost << endl;
  // cout << "Total Profit: " << totalProfit << endl;

  // only display the name, quantity, price, totalPrice in a table using iomanip
  cout << "+--------------------------+----------+------------+------------------+" << endl;
  cout << "| " << setw(25) << left << "Name" << "| " << setw(9) << left << "Quantity" << "| " << setw(11) << left << "Price (RM)" << "| " << setw(16) << left << "Total Price (RM)" << " |" << endl;
  cout << "+--------------------------+----------+------------+------------------+" << endl;
  for (int i = 0; i < cartItemCount; i++) {
    cout << setprecision(2) << fixed;
    cout << "| " << setw(25) << left << bakeryItems[i].getBakeryItemName() << "| " << setw(9) << left << quantity[i] << "| " << setw(11) << left << bakeryItems[i].getPricePerUnit() << "| " << setw(16) << left << bakeryItems[i].getPricePerUnit() * quantity[i] << " |" << endl;
  }
  cout << "+--------------------------+----------+------------+------------------+" << endl;
}

void Cart::addBakeryItemToCart(BakeryItem & item, int quantity) {
  if (cartItemCount >= Constant::MAX_BAKERY_ITEMS) {
    cout << "Cart is full." << endl;
    return;
  }

  bakeryItems[cartItemCount] = item;
  this->quantity[cartItemCount] = quantity;
  cartItemCount++;
}

void Cart::removeBakeryItemFromCart(int index) {
  if (index < 0 || index >= cartItemCount) {
    cout << "Invalid index." << endl;
    return;
  }

  for (int i = index; i < cartItemCount - 1; i++) {
    bakeryItems[i] = bakeryItems[i + 1];
    quantity[i] = quantity[i + 1];
  }

  cartItemCount--;
}

void Cart::calculateTotalCost() {
  totalCost = 0;
  for (int i = 0; i < cartItemCount; i++) {
    totalCost += bakeryItems[i].calculateCost() * quantity[i];
  }
}

void Cart::calculateTotalProfit() {
  totalProfit = 0;
  for (int i = 0; i < cartItemCount; i++) {
    totalProfit += bakeryItems[i].calculateProfit() * quantity[i];
  }
}

void Cart::compareCostVsProfit(int index) const {
  if (index < 0 || index >= cartItemCount) {
    cout << "Invalid index." << endl;
    return;
  }

  double cost = bakeryItems[index].calculateCost() * quantity[index];
  double profit = bakeryItems[index].calculateProfit() * quantity[index];

  cout << "Cost: " << cost << endl;
  cout << "Profit: " << profit << endl;
}

void Cart::compareCostVsPrice(int index) const {
  if (index < 0 || index >= cartItemCount) {
    cout << "Invalid index." << endl;
    return;
  }

  double cost = bakeryItems[index].calculateCost() * quantity[index];
  double price = bakeryItems[index].getPricePerUnit() * quantity[index];

  cout << "Cost: " << cost << endl;
  cout << "Price: " << price << endl;
}

int Cart::getCartItemCount() const {
  return cartItemCount;
}

BakeryItem * Cart::getBakeryItems() const {
  return bakeryItems;
}

int * Cart::getQuantity() const {
  return quantity;
}

double Cart::getTotalCost() const {
  return totalCost;
}

double Cart::getTotalProfit() const {
  return totalProfit;
}

void Cart::setBakeryItems(BakeryItem * bakeryItems) {
  this->bakeryItems = bakeryItems;
}

void Cart::setQuantity(int * quantity) {
  this->quantity = quantity;
}

void Cart::setCartItemCount(int cartItemCount) {
  this->cartItemCount = cartItemCount;
}

void Cart::setTotalCost(double totalCost) {
  this->totalCost = totalCost;
}

void Cart::setTotalProfit(double totalProfit) {
  this->totalProfit = totalProfit;
}

Cart::~Cart() {
  delete [] bakeryItems;
  delete [] quantity;
}