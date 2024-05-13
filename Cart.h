#ifndef CART_H
#define CART_H

#include <iostream>
#include <string>
#include "BakeryItem.h"

using namespace std;

class Cart {
  private:
    BakeryItem * bakeryItems;
    double * quantity; // double because user can choose to buy according to weight
    int cartItemCount = 0;
    double totalCost = 0;
    double totalProfit = 0;
    double totalPrice = 0;
    double totalDiscount = 0;
    static Cart * cart;

  public:
    // Constructor
    Cart();

    // member functions
    void displayCartDetails();
    void addBakeryItemToCart(BakeryItem & item, int quantity);
    void addCakeByWeightToCart(BakeryItem & item, double weight);
    void removeBakeryItemFromCart(int index);
    void updateBakeryItemQuantity(int index, int quantity);
    void clearCart();
    double calculateTotalCost();
    double calculateTotalPrice();
    double calculateTotalProfit();

    // accessor
    int getCartItemCount() const;
    BakeryItem * getBakeryItems() const;
    double * getQuantity() const;
    double getTotalCost() const;
    double getTotalPrice() const;
    double getTotalProfit() const;
    double getTotalDiscount() const;

    // mutator
    void setBakeryItems(BakeryItem *);
    void setQuantity(double *);
    void setCartItemCount(int);
    void setTotalCost(double);
    void setTotalPrice(double);
    void setTotalProfit(double);
    void setTotalDiscount(double);

    // destructor
    ~Cart();
};

#endif