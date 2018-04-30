#include "Byte.h"
#define GENE_SIZE 1

//-------------------------------------------------------
// constructor - initializea byte object
Byte::Byte(){
    geneSize = GENE_SIZE;
    fitness = 0;
}

//-------------------------------------------------------
// two functions can have the same name 
// but different inputs and behavior.
// these achieve the same goal
// setup Byte with existing DNA or with genes to create new DNA
//-------------------------------------------------------

void Byte::setup(DNA _dna, int _bitNum){
    bitNum = _bitNum;
    dna = _dna;
    geneSize = dna.geneSize;
    numOfGenes = dna.numOfGenes;
    calcPhenotype();
}

void Byte::setup(int _numOfGenes, int _bitNum){
    bitNum = _bitNum;
    numOfGenes = _numOfGenes;
    dna.setup(numOfGenes, geneSize);
    calcPhenotype();
}


//-------------------------------------------------------
// decode the normalized genotype data into scaled phenotype data
void Byte::calcPhenotype(){

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
    seed = ofRandom(1000,65000);

}

//-------------------------------------------------------
void Byte::branch(float b_length, float theta, float b_width, int depthRemaining, vector<bool> _bitStates){
    
    // limit to 8 levels deep (1 byte == 8 bits)
    if(depthRemaining > 0){

        ofSetColor(leafColorB,leafColorA);

        // !! this is where to aesthetic
        // current bit's path from previous bit
        ofDrawLine(0,0,0,-b_length);

        // if bitstate is off - color white, otherwise color gray
        if(_bitStates[8-depthRemaining] == false) ofSetColor(255,75);

        // !! this is where to aesthetic
        // current bit's path from previous bit
        //ofDrawLine(0,0,0,-b_length);

        // bit
        ofDrawEllipse(0,-b_length,leafSize-depthRemaining,leafSize);


        // 'child' bit 0
        ofPushMatrix();
        ofTranslate(0,-b_length);
        ofRotate(-theta - (ofNoise(ofGetFrameNum()/thetaVariance*0.5, ofGetFrameNum()/b_length)));
        branch(b_length * (branchReduce + ofRandom(-reduceVariance, reduceVariance)), theta, b_width * erosionFactor, depthRemaining - 1, _bitStates);
        ofPopMatrix();
    
        // 'child' bit 1
        ofPushMatrix();
        ofTranslate(0,-b_length);
        ofRotate(theta + (ofNoise(ofGetFrameNum()/thetaVariance*0.5, ofGetFrameNum()/b_length)));
        //ofRotate(theta + (ofNoise(ofGetFrameNum()/(10*b_length))));
        branch(b_length * (branchReduce + ofRandom(-reduceVariance, reduceVariance)), theta, b_width * erosionFactor, depthRemaining - 1, _bitStates);
        ofPopMatrix();
    }
}

//--------------------------------------------------------
// Draw the bit
void Byte::draw(int x, int y, vector<bool> _bitStates){
    ofSeedRandom(seed);
    ofPushMatrix();
    ofRotate(ofRandom(-startAngle/10, startAngle/10));
    // !! pass popmax
    branch(startLength, startTheta,startWidth, 8, _bitStates);
    ofPopMatrix();
}
