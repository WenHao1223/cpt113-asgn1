#ifndef CAKE_H
#define CAKE_H

#include <iostream>
#include <string>

using namespace std;

class Cake {
  private:
    int totalWeight;
    static int weightLeft;

  public:
    // Constructor
    Cake();
    Cake(int totalWeight);

    // member functions
    // accessor
    int getTotalWeight() const;
    int getWeightLeft();

    // mutator
    void setWeightLeft(int);
};

#endif