//
//  node.cpp
//  Circadian
//
//  Created by Dane Filipczak on 7/11/17.
//
//

#include "node.hpp"


void Node::addForce(ofVec3f force){
    velocity += force;
}

void Node::applyForce(){
    position += velocity;
    velocity.set(0, 0, 0);
    
}

void Node::setup(float x, float y, float z){
    position.set(x, y, z);
    r = 50;
    
    material.setShininess(120);
    material.setSpecularColor(ofColor(0));
    material.setDiffuseColor(ofColor(200));
    material.setAmbientColor(ofColor(0));
}

void Node::linkWith(Node* node){
    linkedTo.push_back(node);
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
    
    ofSetLineWidth(10);
    ofSetColor(255, 255, 70, 100);
    for(auto & n : linkedTo){
        //ofVec3f l = n->getPosition();
        //cout << l;
        //ofDrawLine(position.x, position.y, position.z, l.x, l.y, l.z);
        ofDrawLine(position, n->getPosition());
        //cout << n->getPosition();
        
    };
    

}
