#pragma once
#include "ofMain.h"
#include "DNA.h"

class Bit {

	public:
		Bit();
		void setup(DNA _dna, int _bitNum);
		void setup(int _numOfGenes, int _bitNum);
		void draw();
        void calcPhenotype();
        void draw(int x, int y);
        void branch(float b_length, float theta, float b_width, int depthRemaining);
        void mutate(float mutationRate);
        float getFitness();
        Bit crossover(Bit partner);
    

		DNA dna;

		int numOfGenes, geneSize;
        float fitness;
    
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
