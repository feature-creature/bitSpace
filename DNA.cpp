#include "DNA.h"

//-------------------------------------------------------
// accessible variables
DNA::DNA(){
    mutationAmount = 1;
}

//-------------------------------------------------------
void DNA::setup(int _numOfGenes, int _geneSize)
{
    numOfGenes = _numOfGenes;
    geneSize = _geneSize;

    for (int i = 0; i < numOfGenes; i++) {
        for (int j = 0; j < geneSize; j++) {
           genes.push_back(ofRandom(1));
        }
    }
}

//------------------------------------------------------------------
// Crossover
DNA DNA::crossover(DNA partner) {
    
    // initialize and setup a local temporary DNA object
    DNA child;
    child.setup(numOfGenes, geneSize);

    // pick a random midpoint in the gene space
    // to determine which genes to take from either of the two parent's DNA 
    // (NO RESPECT FOR GENE INTEGRITY)
    int midpoint = int(ofRandom(genes.size())); 

    // populate the local temporary DNA object with genes from 2 parents. 
    // take a portion of genes from parent one,
    // take the remainder of genes from parent two
    for (int i = 0; i < genes.size(); i++) {
        if (i > midpoint) child.genes[i] = genes[i];
        else              child.genes[i] = partner.genes[i];
    }
    
    // return the local temporary DNA object
    return child;

}

//------------------------------------------------------------------
void DNA::mutate(float mutationRate) {
    // if a random number is within the mutation rate
    // give the current gene a new value
    // within the assigned mutation amount
    for (int i = 0; i < genes.size(); i++) {
      if (ofRandom(1) < mutationRate) {
        genes[i] = ofRandom(mutationAmount);
      }
   }
}
