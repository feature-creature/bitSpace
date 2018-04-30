#include "DNA.h"

//-------------------------------------------------------
DNA::DNA(){
    mutationAmount = 1;
}

//-------------------------------------------------------
void DNA::setup(int _numOfGenes, int _geneSize)
{
    numOfGenes = _numOfGenes;
    geneSize = _geneSize;

    // initialize genes
    for (int i = 0; i < numOfGenes; i++) {
        for (int j = 0; j < geneSize; j++) {
           genes.push_back(ofRandom(1));
        }
    }
}

//------------------------------------------------------------------
// Crossover
DNA DNA::crossover(DNA partner) {
    
    // initialize and setup a local, temporary DNA object
    DNA child;
    child.setup(numOfGenes, geneSize);

    // pick a random number within the genesize 
    int midpoint = int(ofRandom(genes.size())); 

    // create genes
    for (int i = 0; i < genes.size(); i++) {
        // all the genes indexed above the midpoint are taken from parent one 
        // all genes indexed below or equal to the midpoint are taken from two parent
        if (i > midpoint){
            child.genes[i] = genes[i];
        }else{
            child.genes[i] = partner.genes[i];
        }
    }

    // return the local temporary DNA object
    return child;

}

//------------------------------------------------------------------
void DNA::mutate(float mutationRate) {
    // for each gene
    // test if a random number falls below the mutation rate
    // if below, give the current gene a new random value
    // within the mutation amount
    for (int i = 0; i < genes.size(); i++) {
      if (ofRandom(1) < mutationRate) {
        genes[i] = ofRandom(mutationAmount);
      }
   }
}
