#pragma once // include guard: ensure the compiler only includes this file once
#include "ofMain.h"
#include "Byte.h"

class BitSpace{

  public:
    BitSpace(); // constructor - initializes an object
    void setup(float m, int num);
    void flip(int n);
    void select();
    void generate();
    void draw();

    float mutationRate;
    
    // bit states for the bit space
    // (all bytes have the same 8 values for bit states)
    vector<bool> bitStates; 

    // general population and mating population of bytes
    vector<Byte> eightBytes;
    vector<Byte> matingBytes;
};
