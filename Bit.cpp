#include "Bit.h"
#define GENE_SIZE 1

//-------------------------------------------------------
// accessible variables
Bit::Bit(){

    geneSize = GENE_SIZE;
    fitness = 0;
}

//-------------------------------------------------------
// two functions can have the same name 
// but different inputs and behavior.
// these achieve the same goal
//-------------------------------------------------------

//-------------------------------------------------------
// setup via existing DNA
void Bit::setup(DNA _dna, int _bitNum){
    // use existing DNA for this bit
    bitNum = _bitNum;
    dna = _dna;
    geneSize = dna.geneSize;
    numOfGenes = dna.numOfGenes;
    // specific to this bit 
    calcPhenotype();
}

//-------------------------------------------------------
// setup via creating DNA 
void Bit::setup(int _numOfGenes, int _bitNum){
    // create new DNA for this bit 
    bitNum = _bitNum;
    numOfGenes = _numOfGenes;
    dna.setup(numOfGenes, geneSize);
    // specific to this bit 
    calcPhenotype();
}

//-------------------------------------------------------
// decode the normalized genotype data into 
// phenotype data scaled to different ranges for visuals
void Bit::calcPhenotype(){

    startLength = ofMap(dna.genes[0],0,1, 150, 200);
    startTheta = ofMap(dna.genes[1],0,1, 0, 40);
    startWidth = ofMap(dna.genes[2],0,1, 2, 20);
    minLength = ofMap(dna.genes[3],0,1, 13, 20);
    branchReduce = ofMap(dna.genes[4],0,1, 0.65, 0.7);
    thetaVariance = ofMap(dna.genes[5],0,1, 0, 50);
    reduceVariance = ofMap(dna.genes[6],0,1, 0, 0.1);
    startAngle = ofMap(dna.genes[7],0,1, 0, 30);
    erosionFactor = ofMap(dna.genes[8],0,1, 0.3, 0.5);
    leafSize = ofMap(dna.genes[9],0,1,10,13);
    leafColorA = 150; 
    leafColorB = 75; 

    // ------------------------------------
    seed = ofRandom(1000,65000);

}

//-------------------------------------------------------
void Bit::branch(float b_length, float theta, float b_width, int depthRemaining){
    
    // options: nofill for options inside bitspace, but above target
    if(depthRemaining > 0){
        
        // -------------------------------------
        // current bit
        // -------------------------------------
    
        // current bit's path from 'parent' bit
        ofSetColor(leafColorB,leafColorA);
        ofDrawLine(0,0,0,-b_length);

        // current bit
        if(depthRemaining != 8 - bitNum){
        //if(depthRemaining <= 8 - bitNum){
            ofSetColor(255,75);
        }else{
            ofSetColor(leafColorB,leafColorA);
        }
        ofDrawEllipse(0,-b_length,leafSize-depthRemaining,leafSize);

        bitCount++;

        // -------------------------------------
        // 'child' bit l
        // -------------------------------------
        ofPushMatrix();
        // branch length
        ofTranslate(0,-b_length);
        // branch rotation from parent
        ofRotate(-theta - (ofNoise(ofGetFrameNum()/thetaVariance*0.5, ofGetFrameNum()/b_length)));
        // start child branch from itself
        branch(b_length * (branchReduce + ofRandom(-reduceVariance, reduceVariance)), theta, b_width * erosionFactor, depthRemaining - 1);
        ofPopMatrix();
    
        // -------------------------------------
        // 'child' bit r
        // -------------------------------------
        ofPushMatrix();
        // branch length
        ofTranslate(0,-b_length);
        // branch rotation from parent
        ofRotate(theta + (ofNoise(ofGetFrameNum()/thetaVariance*0.5, ofGetFrameNum()/b_length)));
        //ofRotate(theta + (ofNoise(ofGetFrameNum()/(10*b_length))));
        branch(b_length * (branchReduce + ofRandom(-reduceVariance, reduceVariance)), theta, b_width * erosionFactor, depthRemaining - 1);
        ofPopMatrix();
    }
}

//--------------------------------------------------------
// Draw the bit
void Bit::draw(int x, int y){
    ofSeedRandom(seed);
    ofPushMatrix();
    ofRotate(ofRandom(-startAngle/10, startAngle/10));
    branch(startLength, startTheta,startWidth, 8);
    ofPopMatrix();
}
