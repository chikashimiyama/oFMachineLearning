#include "ofApp.h"
#include <cassert>
//--------------------------------------------------------------
void ofApp::setup(){
    int numEntries = inputMD.getNumCols() * inputMD.getNumRows();
    
    for(int i = 0; i< inputMD.getNumRows();i++){
        for(int j = 0; j< inputMD.getNumCols();j++){
            inputMD[i][j] = ofRandom(-500, 500);
        }
    }
    
    kmeans.setComputeTheta(true);
    kmeans.setNumClusters(CLUSTER);
    kmeans.setMinChange( 1.0e-10 );
    kmeans.setMinNumEpochs( 1 );
	kmeans.setMaxNumEpochs( 100 );
    
    colors[0] = ofColor::red;
    colors[1] = ofColor::green;
    colors[2] = ofColor::blue;
    colors[3] = ofColor::violet;
    colors[4] = ofColor::brown;
    count = 0;
    
    for(int i = 0; i < CLUSTER;i++){
        sp[i].setScale(0.5);
    }
    centerFlag = false;
    linesFlag = false;
    coloredPointFlag = false;

    glLineWidth(0.1);
    reset();
}

void ofApp::reset(){

    

 
    for(int i = 0; i< inputMD.getNumRows();i++){
        for(int j = 0; j< inputMD.getNumCols();j++){
            inputMD[i][j] = ofRandom(-500, 500);
        }
    }
    
    bool result = kmeans.train(inputMD);
    assert(result);
    
    clusters = kmeans.getClusters();
    //    for(unsigned int i=0; i<clusters.getNumRows(); i++){
    //		for(unsigned int j=0; j<clusters.getNumCols(); j++){
    //			cout << clusters[i][j] << "\t";
    //		}
    //	}
    

    
    for (int i = 0; i < CLUSTER; i++) {
        GRT::VectorDouble vd = clusters.getRowVector(i);
        sp[i].setGlobalPosition(vd[0], vd[1], vd[2]);
    }
}


//--------------------------------------------------------------
void ofApp::update(){

    
    count++;
    if(count > 60){
        centerFlag = true;
    }
    if(count > 120){
        linesFlag = true;
        coloredPointFlag = false;

    }
    if(count > 180){
        linesFlag = false;
        coloredPointFlag = true;
    }
    
    if(count > 240){
        centerFlag = false;
        linesFlag = false;
        coloredPointFlag = false;
        
        count = 0;
        reset();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0, 0, 0);
    //legacy openGL
    ofSetColor(255,255,255);
    glPointSize(5);
    
    cam.begin();
    int numPoints = inputMD.getNumRows();
    std::vector<GRT::UINT> clv = kmeans.getClassLabelsVector();

    if(centerFlag){
        for (int i = 0; i < CLUSTER; i++) {
            ofSetColor(colors[i]);
            sp[i].draw();
        }
    }
    
    ofSetColor(255, 255, 255);

    for(int i = 0; i< numPoints; i++){
        GRT::VectorDouble vd = inputMD.getRowVector(i);
        GRT::UINT cl = clv[i];
        if(coloredPointFlag){
            ofSetColor(colors[cl]);
        }
        glBegin(GL_POINTS);
        glVertex3f(vd[0], vd[1], vd[2]);
        glEnd();

        if(linesFlag){
            ofSetColor(colors[cl]);
            ofVec3f pos = sp[cl].getPosition();
            glBegin(GL_LINES);
            glVertex3f(vd[0], vd[1], vd[2]);
            glVertex3f(pos.x, pos.y, pos.z);
            glEnd();
        }
    }
 
    ofDrawAxis(10);
    
    cam.end();
    ofSetColor(255,0,0);
    int x = 0;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch(key){
        
    };
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
