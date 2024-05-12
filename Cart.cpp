#include "Cart.h"

#include <iomanip>

Cart::Cart() {
  bakeryItems = new BakeryItem[Constant::MAX_BAKERY_ITEMS];
  quantity = new int[Constant::MAX_BAKERY_ITEMS];
}

void Cart::displayCartDetails() {
  this->totalPrice = 0;
  cout << "+----+--------------------------+----------+------------+------------------+" << endl;
  cout << "| " << setw(3) << left << "No" << "| " << setw(25) << left << "Name" << "| " << setw(9) << left << "Quantity" << "| " << setw(11) << left << "Price (RM)" << "| " << setw(16) << left << "Amount (RM)" << " |" << endl;
  cout << "+----+--------------------------+----------+------------+------------------+" << endl;
  for (int i = 0; i < cartItemCount; i++) {
    cout << setprecision(2) << fixed;
    cout << "| " << setw(3) << left << i+1 << "| " << setw(25) << left << bakeryItems[i].getBakeryItemName() << "| " << setw(9) << left << quantity[i] << "| " << setw(11) << left << bakeryItems[i].getPricePerUnit() << "| " << setw(16) << left << bakeryItems[i].getPricePerUnit() * quantity[i] << " |" << endl;
  }
  cout << "+----+--------------------------+----------+------------+------------------+" << endl;
  cout << "Total Price: RM " << setprecision(2) << fixed << this->calculateTotalPrice() << endl;
}

void Cart::addBakeryItemToCart(BakeryItem & item, int quantity) {
  if (cartItemCount >= Constant::MAX_BAKERY_ITEMS) {
    cout << "Cart is full." << endl;
    return;
  }

  bakeryItems[cartItemCount] = item;
  this->quantity[cartItemCount] = quantity;
  cartItemCount++;

  cout << item.getBakeryItemName() << " added to cart." << endl;
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

double Cart::calculateTotalCost() {
  totalCost = 0;
  for (int i = 0; i < cartItemCount; i++) {
    totalCost += bakeryItems[i].calculateCost() * quantity[i];
  }
  return totalCost;
}

double Cart::calculateTotalPrice() {
  totalPrice = 0;
  for (int i = 0; i < cartItemCount; i++) {
    totalPrice += bakeryItems[i].getPricePerUnit() * quantity[i];
  }
  return totalPrice;
}

double Cart::calculateTotalProfit() {
  totalProfit = 0;
  for (int i = 0; i < cartItemCount; i++) {
    totalProfit += bakeryItems[i].calculateProfit() * quantity[i];
  }
  return totalProfit;
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

double Cart::getTotalPrice() const {
  return totalPrice;
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

void Cart::setTotalPrice(double totalPrice) {
  this->totalPrice = totalPrice;
}

void Cart::setTotalProfit(double totalProfit) {
  this->totalProfit = totalProfit;
}

Cart::~Cart() {
  delete [] bakeryItems;
  delete [] quantity;
}