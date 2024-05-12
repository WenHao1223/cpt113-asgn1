#include "Discount.h"

#include <iostream>

Discount::Discount() {
  // cout << "Discount object created at " << this << endl;
}

Discount::Discount(string name, double minimumPurchase, double discountPercentage, string description) {
  this->name = name;
  this->minimumPurchase = minimumPurchase;
  this->discountPercentage = discountPercentage;
  this->description = description;

  discountCount++;
}

Discount::Discount(string name, double minimumPurchase, double discountPercentage, string description, bool disabled) {
  this->name = name;
  this->minimumPurchase = minimumPurchase;
  this->discountPercentage = discountPercentage;
  this->description = description;
  this->disabled = disabled;

  discountCount++;
}

void Discount::displayDiscountDetails() const {
  cout << "Discount Name: " << this->name << endl;
  cout << "Discount Percentage: " << this->discountPercentage << "%" << endl;
  cout << "Description: " << this->description << endl;
  cout << "Disabled: " << (this->disabled ? "Yes" : "No") << endl;
}

void Discount::enableDiscount() {
  this->disabled = false;
}

void Discount::disableDiscount() {
  this->disabled = true;
}

string Discount::getName() const {
  return this->name;
}

double Discount::getMinimumPurchase() const {
  return this->minimumPurchase;
}

double Discount::getDiscountPercentage() const {
  return this->discountPercentage;
}

string Discount::getDescription() const {
  return this->description;
}

bool Discount::getDisabled() const {
  return this->disabled;
}

int Discount::getDiscountCount() const {
  return discountCount;
}

void Discount::setName(string name) {
  this->name = name;
}

void Discount::setMinimumPurchase(double minimumPurchase) {
  this->minimumPurchase = minimumPurchase;
}

void Discount::setDiscountPercentage(double discountPercentage) {
  this->discountPercentage = discountPercentage;
}

void Discount::setDescription(string description) {
  this->description = description;
}

void Discount::setDisabled(bool disabled) {
  this->disabled = disabled;
}

Discount::~Discount() {
  // cout << "Discount object destroyed." << endl;
}

int Discount::discountCount = 0;