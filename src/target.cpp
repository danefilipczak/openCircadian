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
    
    
    ofTranslate(position.x, position.y, position.z);
    //ofRotateX(90);
    //ofRotate(angle);
    //ofDrawCircle(0, 0, 0, 3);
    //ofDrawPlane(100, 100);
    ofDrawBox(100, 20, 100);
    //ofDrawIcoSphere(0, 0, 0, r/2);
    //ofDraw
    //sphere.drawWireframe();
    ofPopMatrix();
}
