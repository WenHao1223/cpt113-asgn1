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
    static Cart * cart;

  public:
    // Constructor
    Cart();
    Cart(BakeryItem * bakeryItems, int * quantity, int cartItemCount, double totalCost, double totalProfit);

    // member functions
    void displayCartDetails() const;
    void addBakeryItemToCart(BakeryItem & item, int quantity);
    void removeBakeryItemFromCart(int index);
    void calculateTotalCost();
    void calculateTotalProfit();
    void compareCostVsProfit(int index) const;
    void compareCostVsPrice(int index) const;

    // accessor
    int getCartItemCount() const;
    BakeryItem * getBakeryItems() const;
    int * getQuantity() const;
    double getTotalCost() const;
    double getTotalProfit() const;

    // mutator
    void setBakeryItems(BakeryItem *);
    void setQuantity(int *);
    void setCartItemCount(int);
    void setTotalCost(double);
    void setTotalProfit(double);

    // destructor
    ~Cart();
};

#endif