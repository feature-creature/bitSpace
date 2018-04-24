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
void Bit::setup(DNA _dna){
    // use existing DNA for this bit
    dna = _dna;
    geneSize = dna.geneSize;
    numOfGenes = dna.numOfGenes;
    // specific to this bit 
    calcPhenotype();
}

//-------------------------------------------------------
// setup via creating DNA 
void Bit::setup(int _numOfGenes){
    // create new DNA for this bit 
    numOfGenes = _numOfGenes;
    dna.setup(numOfGenes, geneSize);
    // specific to this bit 
    calcPhenotype();
}

//-------------------------------------------------------
// decode the normalized genotype data into 
// phenotype data scaled to different ranges for visuals
void Bit::calcPhenotype(){

        branchOffset = ofMap(dna.genes[0],0,1,0,4);
        startTheta = ofMap(dna.genes[1],0,1, 0, 30);
        startLength = ofMap(dna.genes[2],0,1, 20, 100);
        minLength = ofMap(dna.genes[3],0,1, 3, 10);
        branchReduce = ofMap(dna.genes[4],0,1, 0.45, 0.7);
        thetaVariance = ofMap(dna.genes[5],0,1, 0, 30);
        reduceVariance = ofMap(dna.genes[6],0,1, 0, 0.1);
        startAngle = ofMap(dna.genes[7],0,1, 0, 30);
        startWidth = ofMap(dna.genes[8],0,1, 2, 20);
        erosionFactor = ofMap(dna.genes[9],0,1, 0.3, 0.5);
        leafSize = ofMap(dna.genes[10],0,1,1,6);
        leafColorR = ofMap(dna.genes[11],0,1,0,255);
        leafColorG = ofMap(dna.genes[12],0,1,0,255);
        leafColorB = ofMap(dna.genes[13],0,1,0,255);
        leafColorA = ofMap(dna.genes[14],0,1,25,100);
        leafShape = ofMap(dna.genes[15],0,1,3,5);

        // ?? what is this for
        seed = ofRandom(1000,65000);

}

//-------------------------------------------------------
void Bit::branch(float b_length, float theta, float b_width){
    // limit number of branches
    if(count > 500) cout << "max branches reached" << endl;
    
    // branches
    if(b_length > minLength ){

        ofSetColor(0);
        ofSetLineWidth(b_width);
        ofDrawLine(0,0,0,-b_length);
        
        ofPushMatrix();
        ofTranslate(0,-b_length);
        ofRotate(theta + (ofNoise(ofGetFrameNum()/(10*b_length))));
        branch(b_length * (branchReduce + ofRandom(-reduceVariance, reduceVariance)), theta, b_width * erosionFactor);
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(0,-b_length * 1.5);
        ofRotate(-theta - (ofNoise(ofGetFrameNum()/thetaVariance, ofGetFrameNum()/b_length)));
        branch(b_length * (branchReduce + ofRandom(-reduceVariance, reduceVariance)), theta, b_width * erosionFactor);
        ofPopMatrix();

    // leaves
    }else{

        for(int i = 0; i < 20; i++){

            //ofSetColor(leafColorR,leafColorG,leafColorB,leafColorA);
            ofSetColor(leafColorB,leafColorA);
            ofDrawEllipse(ofRandom(-4,4),ofRandom(-4,4),leafSize,leafSize);
        }
    }
    
}

//--------------------------------------------------------
// Draw the bit
void Bit::draw(int x, int y){
    ofSeedRandom(seed);
    count = 0;
    ofPushMatrix();
    ofRotate(ofRandom(-startAngle, startAngle));
    branch(startLength, startTheta,startWidth);
    ofPopMatrix();
}

////--------------------------------------------------------
//void Bit::print(){
//    cout << branchOffset << endl;
//    cout <<     startTheta << endl;
//    cout <<     startLength << endl;
//        cout << minLength << endl;
//        cout << branchReduce << endl;
//        cout << thetaVariance << endl;
//       cout <<  reduceVariance << endl;
//        cout << startAngle << endl;
//        cout << seed << endl;
//}
