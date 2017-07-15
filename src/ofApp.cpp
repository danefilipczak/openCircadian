#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    //OSC boilerplate
    receiver.setup(RECEIVE_PORT);
    sender.setup(HOST, SEND_PORT);
    ofSetFrameRate(60); //this supposedly will keep the OSC from bugging everything. Probably best to just keep the clock lower on SC however
    
    
    //give yourself an icosahedron
    icosahedron = ofMesh::icosahedron(100);
    
    vector<ofVec3f> verts = icosahedron.getVertices();
    
    for (auto & v : verts){
        Node n;
        n.setup(v.x, v.y, v.z);
        nodes.push_back(n);
    }
    
    
    mothMaterial.setShininess(120);
    mothMaterial.setSpecularColor(ofColor(0));
    mothMaterial.setDiffuseColor(ofColor(200));
    mothMaterial.setAmbientColor(ofColor(100));
//    
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
    
    
    
    for (auto t = targets.begin(); t != targets.end(); t++){
        t->setup(ofVec3f(0, -100+(y*50), 0));
        y++;
    };
    
    
    //    material.setDiffuseColor(ofFloatColor(.85, .85, .55));
    //    material.setShininess(0.01);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    while(receiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        if(m.getAddress()=="/noteOn"){
            
            for(int i = 0; i<20; i++){
                partials[i] = m.getArgAsFloat(i);
            };
            
        };
        
    };

    
    //    sphere.move(ofVec3f(0,0,-10));
    if(moths.size()<700){addMoth();};
    
    
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
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //ofBackground(255, 255, 255);
    ofBackground(10);
    
    ofEnableDepthTest();
    
    ofEnableLighting();
    camera.begin();
    light.enable();
    
    // draw something
    //icosahedron.drawWireframe();
    //    material.begin();
    //    sphere.draw();
    //    material.end();
    mothMaterial.begin();
    for (auto & m : moths){
        m.draw();
    }
    mothMaterial.end();
    for (auto & t : targets){
        t.draw();
    }
    for (auto & n : nodes){
        n.draw();
    }
    
    
    
    light.disable();
    camera.end();
    


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    float y = 0;
    for (auto & t : targets){
        
        t.setPosition(ofVec3f(0, -200+(y*40), 0));
        y++;
        
    }

}


//------------------------------------------------------------

void ofApp::addMoth(){
    

    Moth m;
     m.setup(numMoths, ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), ofRandom(ofGetHeight()));
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
