#include "Cake.h"

Cake::Cake() {
  totalWeight = 0;

  cout << "Cake object created." << endl;
}

Cake::Cake(int totalWeight) {
  if (totalWeight <= 0) {
    cout << "Total weight cannot be zero or negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }
  
  this->totalWeight = totalWeight;

  cout << "Cake object with total weight created." << endl;
}

int Cake::getTotalWeight() const {
  return totalWeight;
}

int Cake::getWeightLeft() {
  return weightLeft;
}

void Cake::setWeightLeft(int weightLeft) {
  this->weightLeft = weightLeft;
}

int Cake::weightLeft = 0;