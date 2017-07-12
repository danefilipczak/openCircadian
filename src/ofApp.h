#pragma once

#include "ofMain.h"
#include "moth.hpp"
#include "target.hpp"
#include "ofxOsc.h"

#define RECEIVE_PORT 12345
#define SEND_PORT 54321
#define HOST "localhost"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    void addMoth();
    int numMoths = 0;
    
    
    ofEasyCam camera;
    ofSpherePrimitive sphere;
    ofLight light;
   
    vector<Moth> moths;
    vector<Target> targets;
    
    ofxOscReceiver receiver;
    float partials[20]; //incoming info about where the targets should end up
    
    
    //for sending information about moths
    ofxOscSender sender;
    float mothX;
    float mothY;
    float mothZ;
};
