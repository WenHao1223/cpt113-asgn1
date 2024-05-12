#ifndef CART_H
#define CART_H

#include <iostream>
#include <string>
#include "BakeryItem.h"

using namespace std;

class Cart {
  private:
    BakeryItem * bakeryItems;
    int * quantity;
    int cartItemCount = 0;
    double totalCost = 0;
    double totalProfit = 0;
    double totalPrice = 0;
    static Cart * cart;

  public:
    // Constructor
    Cart();

    // member functions
    void displayCartDetails();
    void addBakeryItemToCart(BakeryItem & item, int quantity);
    void removeBakeryItemFromCart(int index);
    void updateBakeryItemQuantity(int index, int quantity);
    void clearCart();
    double calculateTotalCost();
    double calculateTotalPrice();
    double calculateTotalProfit();

    // accessor
    int getCartItemCount() const;
    BakeryItem * getBakeryItems() const;
    int * getQuantity() const;
    double getTotalCost() const;
    double getTotalPrice() const;
    double getTotalProfit() const;

    // mutator
    void setBakeryItems(BakeryItem *);
    void setQuantity(int *);
    void setCartItemCount(int);
    void setTotalCost(double);
    void setTotalPrice(double);
    void setTotalProfit(double);

    // destructor
    ~Cart();
};

#endif