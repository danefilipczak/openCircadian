//
//  node.hpp
//  Circadian
//
//  Created by Dane Filipczak on 7/11/17.
//
//

#include "ofMain.h"
#ifndef node_hpp
#define node_hpp


//this is how you can pop through vectors

//for (int i = 0; i < particles.size(); i++){
//    particles.at(i)->update();
//    if(particles.at(i)->isDead()){
//        particles.erase(particles.begin() + i);
//    }
//}

class Node {
    
public:
    void setup(float x, float y, float z);
    void draw();
    void age();
    void die();
    
    vector<Node*> getNeighborsFartherThan(float thresh);
    Node* getANeighborFartherThan(float thresh);
    
    void breakLink(Node* node);
    void breakAll();
    void addForce(ofVec3f vec);
    void applyForce();
    void drawPipe(ofVec3f);
    //void growMidpoint(Node neighbor);
    void linkWith(Node* neighbor); 
    Node growMidpoint(Node* neighbor);
    
    
    const ofPoint& getPosition() const {
        return position;
    }
    
    vector<Node*> getLinkedTo() {
        return linkedTo;
    }
    
    
private:
    bool dead = false;
    vector<Node*> linkedTo; //i'm not sure if this is going to work... needs to store a flexibly sized group of things that
    int lifespan;
    int deathClock;
    float r;
    ofMaterial material;
    ofMaterial pipeMaterial;
    
    ofVec3f position;
    ofVec3f velocity;
    
};





#include <stdio.h>

#endif /* node_hpp */
