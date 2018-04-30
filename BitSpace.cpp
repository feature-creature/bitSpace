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
    // clearing the byte vector of any previously stored byte objects
    eightBytes.clear();

    // fill the empty byte vector with byte objects
    for (int i=0; i<num; i++){
        // initialize local, temporary a byte object 
        Byte tempByte;
        // use gene (not DNA) version of setup function, since parent DNA does not exist
        tempByte.setup(10, i);
        // store the new byte in the byte vector
        eightBytes.push_back(tempByte);
        
        // for each byte fill bitState vector
        // !! clean this up
        bitStates.push_back(false);
    }

}

//-------------------------------------------------------
// designate a sub population (mating pool) of the current population 
// for eventual selection of parents for the next generation of eightBytes
void BitSpace::select() {
    
    // clear the mating pool vector of any previously stored byte objects
    matingBytes.clear(); 

    // clear the 'total mating quantity'
    // stored for the previous mating pool
    // this value is used to determine each individual byte's
    // probability for mating in relation to the whole pool
    float maxFitness=0;

    // calculate and set the 'total mating quantity' for the current mating pool
    for(int i = 0; i < eightBytes.size(); i++) maxFitness += eightBytes[i].fitness;
    
    // create the mating pool from the current population: 
    // first determine % 'mateability' for each current individual byte 
    // then populate the mating pool by adding each byte
    // 'their mateability' number of times to the mating pool  
    for (int i = 0; i < eightBytes.size(); i++) {
        // normalize fitness values on 0-1 scale
        float fitnessNormal = ofMap(eightBytes[i].fitness, 0, maxFitness, 0, 1);
        // normalize fitness values on 0-100 scale
        int n = (int) (fitnessNormal * 100);
        // if the individual has a non-zero n value, add individual n times into mating pool
        for (int j = 0; j < n; j++) {
            matingBytes.push_back(eightBytes[i]);
        }
    }
}

//------------------------------------------------------------
// display the current generation of the BitSpace
// draw each bit
void BitSpace::draw(){

    // only draw the byte whose index
    // equals the index of the most recently flipped bitstate
    // not the entire byte general population
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,-75,0);
    // !! link up with flipping
    eightBytes[3].draw(0,0, bitStates);
    ofSetColor(0);
    ofPopMatrix();
    
    for(int i = eightBytes.size(); i >= 0; i--){
        // draw bit labels across window footing
        ofPushMatrix();
        ofTranslate((ofGetWidth()/eightBytes.size())*i, 0, 0);
        ofDrawBitmapString(ofToString(pow(2,i)), -10, 20);
        ofPopMatrix();
    }
}

//------------------------------------------------------------
// Create a new generation of eightBytes
void BitSpace::generate() {

    // for the entire general population in the bitspace
    for (int i = 0; i < eightBytes.size(); i++) {

        // (at random) choose two parent bytes from the mating pool
        // for generating the next generation
        int a = int(ofRandom(matingBytes.size()));
        int b = int(ofRandom(matingBytes.size()));

        // store the selected bytes as two temporary local byte objects
        Byte partnerA = matingBytes[a];
        Byte partnerB = matingBytes[b];
      
        // create a temporary local dna object for the eventual child byte
        // using the parent's temporary local genotype data
        DNA childDNA = partnerA.dna.crossover(partnerB.dna);

        // mutate the local, temporary child dna for child variability
        childDNA.mutate(mutationRate);

        // create temporary local byte object 
        Byte child;
        //set up with the temporary local child DNA
        child.setup(childDNA, i);

        // replace the current generation's stored byte
        // with a byte for the new generation
        eightBytes[i] = child;
      
        // decode the newly stored byte's geneotype data 
        // for shaping visual phenotype representation
        eightBytes[i].calcPhenotype();
    }
}

//------------------------------------------------------------
void BitSpace::flip(int n){
     eightBytes[n].fitness++;
}
