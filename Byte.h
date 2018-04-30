#pragma once // include guard: ensure the compiler only includes this file once
#include "ofMain.h"
#include "DNA.h"

class Byte{

	public:
		Byte();
		void setup(DNA _dna, int _bitNum);
		void setup(int _numOfGenes, int _bitNum);
		void draw();
        void calcPhenotype();
        void draw(int x, int y, vector<bool> _bitStates);
        void branch(float b_length, float theta, float b_width, int depthRemaining,vector<bool> _bitStates);
        void mutate(float mutationRate);
        float getFitness();
        Byte crossover(Byte partner);


		int numOfGenes, geneSize;
        float fitness;
		DNA dna;
    
        float startLength;
        float startTheta;
        int startWidth;
        float minLength;
        float branchReduce;
        float thetaVariance;
        float reduceVariance;
        float startAngle;
        float erosionFactor;
        int leafSize;
        float leafColorB;
        float leafColorA;
        float seed = 0;
        int bitCount = 0;

        int bitNum;

};
