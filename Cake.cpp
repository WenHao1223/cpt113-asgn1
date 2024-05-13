#include "Cake.h"

Cake::Cake() {
  totalWeight = 0;
}

Cake::Cake(int totalWeight) {
  this->totalWeight = totalWeight;
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