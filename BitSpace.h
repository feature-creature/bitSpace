#pragma once
#include "ofMain.h"
#include "Bit.h"

class BitSpace{

  public:
    BitSpace();
    void setup(float m, int num);
    void flip(int n);
    void select();
    void generate();
    void draw();

    float mutationRate;  // Mutation rate
    vector<Bit> eightBit; // Vector for the current bitspace
    vector<Bit> matingBits; // Vector for the "mating pool" bits
};
