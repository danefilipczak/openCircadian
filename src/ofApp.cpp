#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    //ofDisableArbTex();
    ofSetGlobalAmbientColor(ofColor(255));
    //nodes.reserve(1000); //a hack
    
    stop = false;
    //OSC boilerplate
    receiver.setup(RECEIVE_PORT);
    sender.setup(HOST, SEND_PORT);
    ofSetFrameRate(60); //this supposedly will keep the OSC from bugging everything. Probably best to just keep the clock lower on SC however
    
    float icoR = 100;
    icosahedron = ofMesh::icosahedron(icoR);
    vector<ofVec3f> verts = icosahedron.getVertices();
    float skew = 5; //for making all the edges not split at once
    for (auto & v : verts){
        Node n;
        n.setup(v.x+ofRandom(skew),
                v.y+ofRandom(skew),
                v.z+ofRandom(skew));
        nodes.push_back(n);
    }
    for (auto & n : nodes){
        for (auto & nn : nodes){
            if(n.getPosition() != nn.getPosition()){
                if(n.getPosition().distance(nn.getPosition())<icoR*1.5){
                    nn.linkWith(&n); //why did this not work when I tried to link it with a full node ob?????
                };
            };
        };
    };
    

    
    
    //tex.loadImage("iceland.jpg");
    //tex.allocate(<#const ofTextureData &textureData#>)
    
    mothMaterial.setShininess(120);
    mothMaterial.setSpecularColor(ofColor(0));
    mothMaterial.setDiffuseColor(ofColor(200));
    mothMaterial.setAmbientColor(ofColor(100));
//
    targetMaterial.setShininess(120);
    targetMaterial.setSpecularColor(ofColor(255, 100));
    targetMaterial.setDiffuseColor(ofColor(200, 100));
    targetMaterial.setAmbientColor(ofColor(100));
//    
//    Moth m;
//    m.setup(numMoths, ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), ofRandom(ofGetHeight()));
//    moths.push_back(m);
//    
//    //    light.setSpotlight();
//    
//    
    
    
    //lights
    ofSetSmoothLighting(true);
    light.setPosition(0, 1000, 1000);
    light.setDiffuseColor( ofColor(255) );
    light.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    camera.setFarClip(100000000);
    
    
    
    //moths.resize(500);
    targets.resize(20); //we want exactly ten targets... maybe?
    
    addMoth();
    
//    for (auto & m : moths){
//        //ofVec3f location(ofGetWidth(), ofGetHeight());
//        m.setup(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), ofRandom(ofGetHeight()));
//    }
    float y = 0;
    
    
    //either of the following vector iterating syntaxes work
    //    for (auto & t : targets){
    //
    //        t.setup(ofVec3f(0, -100+(y*50), 0));
    //        y++;
    //
    //    }
    
    ofEnableDepthTest();
    
    for (auto t = targets.begin(); t != targets.end(); t++){
        t->setup(ofVec3f(0, -500+(y*200), 0));
        y++;
    };
    
    
    
    //    material.setDiffuseColor(ofFloatColor(.85, .85, .55));
    //    material.setShininess(0.01);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // OSC STUFF
    while(receiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        if(m.getAddress()=="/noteOn"){
            
            for(int i = 0; i<20; i++){
                partials[i] = m.getArgAsFloat(i);
            };
            
        };
        
    };

    
    //    MOTH STUFF
    if(moths.size()<200){addMoth();};
    for (auto & m : moths){
        m.applyBehaviors(moths, targets);
        m.update();
        
//        ofxOscMessage out;
//        out.setAddress("moth");
//        out.addIntArg(m.getId());
//        
//        out.addFloatArg(m.getPosition().x);
//        out.addFloatArg(m.getPosition().y);
//        out.addFloatArg(m.getPosition().z);
    }
    
    
    // NODE STUFF
    //add forces
    
    float r = ofNoise(ofGetElapsedTimef())*0.1;
    float a = ofNoise(ofGetElapsedTimef()+1000)*0.3;
    
    
    rejectAll(300, r); //thresh, then force
    //attractNeighbors(100, -a);
    
    //commit forces. with springyness????
    for(auto & n : nodes){
        n.applyForce();
    }
    
    
    if(!stop && nodes.size()<200){
        //consistently breaks on 17. wtf.
        edgeSplit(170);
    }
    
    
    
    //ofSaveScreen(ofToString(ofGetFrameNum())+".png");
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //ofBackground(255, 255, 255);
    ofBackground(10);
    
    ofEnableDepthTest();
    
    ofEnableLighting();
    camera.begin();
    light.enable();
    
    mothMaterial.begin();
    for (auto & m : moths){
        m.draw();
    }
    mothMaterial.end();
    
    for (auto & n : nodes){
        n.draw();
    }
    
    
    light.disable();
    
    ofSetColor(255, 255, 50, 100);
    for (auto & t : targets){
        t.draw();
    };
    
    camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    stop = true;
    
    float y = 0;
    for (auto & t : targets){
        
        t.setPosition(ofVec3f(0, -200+(y*40), 0));
        y++;
        
    }
    
    //moths.at(1);

}

//-------------------------------------------------


//helper function

vector<Node*> intersection(vector<Node*> v1, vector<Node*> v2)
{
    /*
     return the intersection of two vectors
     */
    
    vector<Node*> v3;
    
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    
    set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));
    
    return v3;
}




void ofApp::edgeSplit(float thresh){
    
    /*
     
     loop through all the nodes and see if any neighbors are over the split threshold
     if they are, first break up the parents and then add their info to a staging vector. 
     then, loop through the staging vector and insert new nodes between all the parents.
     */
    
    vector <birth> stage;
    stage.clear();
    for(auto & i : nodes){
       
        //this function returns 'this' if no offending neighbor is found
        Node* close = i.getANeighborFartherThan(thresh);
        if(close != &i){ //if a neighbor over the threshold has been found
            
            vector<Node*> growth = i.getNeighborsFartherThan(thresh);
            
            for(auto & g : growth){
                i.breakLink(g);
                g->breakLink(&i);
                birth babe;
                babe.mother = &i;
                babe.father = g;
                stage.push_back(babe);
            }
        }
        
    };
    
    
    for(auto & b : stage){
        
        //initialize a new Node halfway between the parents.
        Node babe = b.mother->growMidpoint(b.father);
        //add it to the list and grab a pointer to it
        nodes.push_back(babe);
        Node* budPtr= &nodes.back();
        
        //get the intersection of its parents' neighbors
        vector<Node*> overlap = intersection(b.mother->getLinkedTo(), b.father->getLinkedTo());
        
        //link the babe up to the intersection
        for(auto & k : overlap){
            budPtr->linkWith(k);
            k->linkWith(budPtr);
        }
        
        //establish familial bonds
        budPtr->linkWith(b.mother);
        budPtr->linkWith(b.father);
        b.mother->linkWith(budPtr);
        b.father->linkWith(budPtr);
    }
}


//-----------------------------------------------------


void ofApp::rejectAll(float rThresh, float rForce){
    for(auto & i : nodes){
        ofVec3f ip = i.getPosition();
        for(auto & j : nodes){
            ofVec3f jp = j.getPosition();
            if(ip != jp){
                if(ip.distance(jp)<rThresh){
                    ofVec3f force = ip - jp;
                    force.normalize();
                    i.addForce(force *= rForce);
                    j.addForce(-force *= rForce);
                };
            };
        };
    };
};


void ofApp::attractNeighbors(float aThresh, float aForce){
    for(auto & i : nodes){
        ofVec3f ip = i.getPosition();
        vector<Node*> neighbors = i.getLinkedTo();
        for(auto & j : neighbors){
            ofVec3f jp = j->getPosition();
            if(ip != jp){
                if(ip.distance(jp)>aThresh){
                    ofVec3f force = ip - jp;
                    force.normalize();
                    i.addForce(force *= aForce);
                    j->addForce(-force *= aForce);
                };
            };
        };
    };
};




//------------------------------------------------------------

void ofApp::addMoth(){
    float w = ofGetWidth();
    float h = ofGetHeight();

    Moth m;
     m.setup(numMoths, ofRandom(w)-(w/2), ofRandom(w)-(w/2), ofRandom(w)-(w/2));
    moths.push_back(m);
    numMoths++;
    
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
