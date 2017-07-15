//
//  node.cpp
//  Circadian
//
//  Created by Dane Filipczak on 7/11/17.
//
//

#include "node.hpp"


void Node::setup(float x, float y, float z){
    position.set(x, y, z);
    r = 50;
    
    material.setShininess(120);
    material.setSpecularColor(ofColor(0));
    material.setDiffuseColor(ofColor(200));
    material.setAmbientColor(ofColor(0));
}

void Node::draw(){
    ofPushMatrix();
    material.begin();
    
    
    ofSetColor(0, 100);
    ofTranslate(position.x, position.y, position.z);
    //ofRotate(angle);
    //ofDrawCircle(0, 0, 0, r/2);
    ofDrawIcoSphere(0, 0, 0, r/2);
    //ofDraw
    //sphere.drawWireframe();
    material.end();
    ofPopMatrix();

}
