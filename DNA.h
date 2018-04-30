#pragma once
#include "ofMain.h"

class DNA{

	public:
		DNA();
		void setup(int _numOfGenes, int _geneSize);
		void draw();
        DNA crossover(DNA partner);
        void mutate(float mutationRate);

		int numOfGenes;
		int geneSize;
		vector<float> genes;
        float fitness;
        float mutationAmount;
};
