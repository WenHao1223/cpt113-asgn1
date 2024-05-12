#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <iostream>
#include <string>

#include "Constant.h"

using namespace std;

class Discount {
  private:
    string name;
    double discountPercentage;
    string description;
    bool disabled = false;
    static int discountCount;

  public:
    // Constructor
    Discount();
    Discount(string name, double discountPercentage, string description);
    Discount(string name, double discountPercentage, string description, bool disabled);

    // member functions
    void displayDiscountDetails() const;
    void enableDiscount();
    void disableDiscount();

    // accessor
    string getName() const;
    double getDiscountPercentage() const;
    string getDescription() const;
    bool getDisabled() const;
    int getDiscountCount() const;

    // mutator
    void setName(string);
    void setDiscountPercentage(double);
    void setDescription(string);
    void setDisabled(bool);

    // destructor
    ~Discount();
};

#endif