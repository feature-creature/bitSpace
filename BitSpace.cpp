#include "BitSpace.h"

//-------------------------------------------------------
BitSpace::BitSpace() {
}

//-------------------------------------------------------
void BitSpace::setup(float m, int num)
{
    // initialize global mutation rate 
    mutationRate = m;

    // prepare for current generation by
    // empty/clear the bit vector of any previously stored bit objects
    eightBit.clear();

    // fill the empty bit vector with temporary bit objects
    for (int i=0; i<num; i++){
        // initialize a bit object 
        Bit tempBit;
        // gene (not DNA) version of setup function
        tempBit.setup(10, i);
        // store the new bit in the bit vector
        eightBit.push_back(tempBit);
    }

}

//-------------------------------------------------------
// Generate a mating pool
// designate a sub population of the current population (mating pool)
// for selecting the possible parents for the next generation of eightBit
void BitSpace::select() {
    
    // empty/clear the mating pool vector of any previously stored bit objects
    matingBits.clear(); 

    // clear the previously stored 'total mating quantity' for the entire previous mating pool bit vector 
    // this value is used to determine the individual bit's probability for mating in relation to the whole pool
    float maxFitness=0;

    // sum the total mateability of the current mating pool vector
    for(int i = 0; i < eightBit.size(); i++) maxFitness += eightBit[i].fitness;
    
    // create the mating pool of the current population for generating the next generation
    // first determine % 'mateability' for each current individual in relation to the total current population 
    // then create mating pool by adding each current individual with a non-zero mateability number to the mating pool
    // probabilities are created in the mating pool by adding those non-zero individuals to the pool 
    // multiple times (exactly as many times as their mateability number). 
    // 2 parents will be chosen from this probabilistic mating pool to generate the next generation of eightBit
    // higher percent == higher chance for mating -- only 2 get to mate
    for (int i = 0; i < eightBit.size(); i++) {
        // normalize fitness values on 0-1 scale
        float fitnessNormal = ofMap(eightBit[i].fitness, 0, maxFitness, 0, 1);
        // normalize fitness values on 0-100 scale
        int n = (int) (fitnessNormal * 100);
        // if the individual has a non-zero n value, add individual n times into mating pool
        for (int j = 0; j < n; j++) {
            matingBits.push_back(eightBit[i]);
        }

    }
    // mating pool is now populated for selection
}

//------------------------------------------------------------
// display the current generation of the BitSpace
// draw each bit
void BitSpace::draw(){
    // only draw one of the proper bitspace, not all of them
    //for(int i = eightBit.size(); i >= 0; i--){

        // draw bit labels across window footing
        //ofPushMatrix();
        //ofTranslate((ofGetWidth()/eightBit.size())*i, 0, 0);
        //ofDrawBitmapString(ofToString(pow(2,i)), -10, 20);
        //ofPopMatrix();


        // draw the selected bit configuration
        // set up with color tracking
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2,-50,0);
        eightBit[ofRandom(0,8)].draw(0,0);
        ofSetColor(0);
        ofPopMatrix();
    //}
}

//------------------------------------------------------------
// Create a new generation of eightBit and
// fill the bit vector with them 
void BitSpace::generate() {

    for (int i = 0; i < eightBit.size(); i++) {

        // (at random) choose two bits from the mating pool
        int a = int(ofRandom(matingBits.size()));
        int b = int(ofRandom(matingBits.size()));

        // store the selected bits as two temporary local bit objects
        Bit partnerA = matingBits[a];
        Bit partnerB = matingBits[b];
      
        // create a temporary local DNA object with the temporary local genotype data
        DNA childDNA = partnerA.dna.crossover(partnerB.dna);

        // mutate the child dna for child variability
        childDNA.mutate(mutationRate);

        // create temporary local bit object 
        Bit child;
        //set it up with the temporary local DNA data 
        child.setup(childDNA, i);

        // replace the currently stored bit
        // by storing this local temporary bit in its place
        eightBit[i] = child;
      
        // decodes the newly stored bit's geneotype data into
        // variables for visual phenotype representation
        eightBit[i].calcPhenotype();
    }
}

//------------------------------------------------------------
void BitSpace::flip(int n){
     eightBit[n].fitness++;
}
