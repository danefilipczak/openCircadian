//
//  node.cpp
//  Circadian
//
//  Created by Dane Filipczak on 7/11/17.
//
//

#include "node.hpp"
#include "ofApp.h"


void Node::addForce(ofVec3f force){
    velocity += force;
}

void Node::applyForce(){
    position += velocity;
    velocity.set(0, 0, 0);
    
}

void Node::breakLink(Node* node){

    
//    
//    linkedTo.erase(remove(linkedTo.begin(), linkedTo.end(), node), linkedTo.end());
    
    int deathIndex;
    
    for(int i = 0; i < linkedTo.size(); i++){
        if(linkedTo[i]==node){
            deathIndex = i;
        }
    }
    linkedTo.erase(linkedTo.begin()+deathIndex);
    
}


Node* Node::getANeighborFartherThan(float thresh){
    
    for(auto & i : linkedTo){
        
        if(position.distance(i->getPosition())>thresh){
            return i;
            break;
        }
        
    }
    
}

vector<Node*> Node::getNeighborsFartherThan(float thresh){
    vector<Node*> tooFar;
    
    for(auto & i : linkedTo){
        
        if(position.distance(i->getPosition())>thresh){
            tooFar.push_back(i);
        }
        
    }
    
    
    return tooFar;
    
}



Node Node::growMidpoint(Node* neighbor){
    
    
    
 
    
    ofVec3f halfway(neighbor->getPosition());
    halfway.interpolate(position, 0.5);
    
    
    Node bud;
    bud.setup(halfway.x, halfway.y, halfway.z);
    
//    neighbor->linkWith(&bud);
//    linkWith(&bud);
    
    
    return bud;

    
    //nodes.push_back(bud);
    
    
    
    
    
}


//var iVec = new THREE.Vector3();
//iVec.copy(this.sphere.position);
//var jVec = new THREE.Vector3();
//jVec.copy(neighbor.sphere.position);
//
//
//
//
//// var jNode = nodes[i].linkedTo[j];
//// var iNode = nodes[i];
//this.breakLink(neighbor);
//neighbor.breakLink(this);
//
//var halfway = iVec.lerp(jVec, 0.5);
//var bud = new Node(halfway);
//
//var overlap = intersect(this.linkedTo, neighbor.linkedTo);
//for(var k = 0;k<overlap.length; k++){
//    bud.makeLink(overlap[k]);
//    overlap[k].makeLink(bud);
//}
//bud.makeLink(neighbor);
//bud.makeLink(this)
//neighbor.makeLink(bud);
//this.makeLink(bud);
//
//nodes.push(bud);

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
