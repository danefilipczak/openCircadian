//
//  target.cpp
//  Circadian
//
//  Created by Dane Filipczak on 7/11/17.
//
//

#include "target.hpp"


void Target::setup(ofVec3f pos){
    position = pos;
};


void Target::setPosition(ofVec3f pos){
    position = pos;
};

void Target::draw(){
    ofPushMatrix();
    
    ofSetColor(255, 255, 0, 100);
    ofTranslate(position.x, position.y, position.z);
    //ofRotate(angle);
    ofDrawCircle(0, 0, 0, 3);
    //ofDrawIcoSphere(0, 0, 0, r/2);
    //ofDraw
    //sphere.drawWireframe();
    ofPopMatrix();
}
