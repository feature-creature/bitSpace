#pragma once
#include "ofMain.h"
#include "DNA.h"

class Bit {

	public:
		Bit();
		void setup(DNA _dna);
		void setup(int _numOfGenes);
		void draw();
        void calcPhenotype();
        void draw(int x, int y);
        float getFitness ();
        Bit crossover(Bit partner);
    void branch(float b_length, float theta, float b_width);
    
        void mutate(float mutationRate);

		DNA dna;
		int numOfGenes, geneSize;
        float fitness;
    
        float branchOffset;
        float startTheta;
        float startLength;
        float minLength;
        float branchReduce;
        float thetaVariance;
        float reduceVariance;
        float startAngle;
        float seed = 0;
        int count = 0;

        int startWidth;
        float erosionFactor;
        int leafSize;
        float leafColorR;
        float leafColorG;
        float leafColorB;
        float leafColorA;
        int leafShape;

//    void print();
};
