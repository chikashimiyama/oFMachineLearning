#pragma once
#include <GRT.h>
#include "ofMain.h"

#define CLUSTER 5

class ofApp : public ofBaseApp{

    private:
        GRT::MatrixDouble inputMD;
        GRT::GestureRecognitionPipeline pl;
        GRT::KMeans kmeans;
        ofEasyCam cam;
        GRT::Matrix< double > clusters;
        ofSpherePrimitive sp[5];
        ofColor colors[5];
    
        bool centerFlag;
        bool linesFlag;
        bool coloredPointFlag;
    
        int count;
        void reset();
    public:
    ofApp(int row = 1000, int column= 3): inputMD(row, column){};
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
