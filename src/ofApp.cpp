#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    
    
    sphere.setResolution(5);
    //    light.setSpotlight();
    ofSetSmoothLighting(true);
    light.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    light.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    
    
    
    moths.resize(500);
    targets.resize(10);
    
    for (auto & m : moths){
        //ofVec3f location(ofGetWidth(), ofGetHeight());
        m.setup(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), ofRandom(ofGetHeight()));
    }
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

    
    //    sphere.move(ofVec3f(0,0,-10));
    
    for (auto & m : moths){
        m.applyBehaviors(moths, targets);
        m.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255, 255, 255);
    
    ofEnableDepthTest();
    
    ofEnableLighting();
    camera.begin();
    light.enable();
    
    // draw something
    sphere.drawWireframe();
    //    material.begin();
    //    sphere.draw();
    //    material.end();
    
    for (auto & m : moths){
        m.draw();
    }
    
    for (auto & t : targets){
        t.draw();
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
