#pragma once

#include "ofMain.h"
#include "moth.hpp"
#include "target.hpp"
#include "ofxOsc.h"
#include "node.hpp"

#define RECEIVE_PORT 12345
#define SEND_PORT 54321
#define HOST "localhost"
//questions:
/*
 
 Using a list for nodes and doing linkedTo off refrences. Is this intellegent? 
 Would it be better to use map and a primary key? 
 Lists are unordered and thus preclude an elegent way to limit iteration.
 
 
 
 
 */



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
    void rejectAll(float rThresh, float rForce);
    void edgeSplit(float thresh);
    void attractNeighbors(float aThresh, float aForce);
    
//    
//    struct nodePair {
//        
//        Node* a;
//        Node* b;
//        
//    };
//    
//    vector<nodePair> splitQueue;
//    
//    vector<Node> nodeQueue;
    
    struct birth {
        Node child;
        Node* father;
        Node* mother;
    };
    
    int numMoths = 0;
    
    ofImage tex;
    
    ofEasyCam camera;
    ofMesh icosahedron;
    ofLight light;
    
    ofMaterial mothMaterial;
    ofMaterial targetMaterial;
   
    vector<Moth> moths;
    vector<Target> targets;
    list<Node> nodes;
    
    
    ofxOscReceiver receiver;
    float partials[20]; //incoming info about where the targets should end up
    
    bool stop;
    
    //for sending information about moths
    ofxOscSender sender;
    float mothX;
    float mothY;
    float mothZ;
};
