//
//  node.hpp
//  Circadian
//
//  Created by Dane Filipczak on 7/11/17.
//
//


#ifndef node_hpp
#define node_hpp
#include "ofMain.h"

//this is how you can pop through vectors

//for (int i = 0; i < particles.size(); i++){
//    particles.at(i)->update();
//    if(particles.at(i)->isDead()){
//        particles.erase(particles.begin() + i);
//    }
//}

class Node {
    
public:
    void age();
    void die();
    void makeLink(Node node);
    void breakLink(Node node);
    void breakAll();
    void addForce(ofVec3f vec);
    void applyForce();
    void growMidpoint(Node neighbor);
    
    
private:
    bool dead = false;
    vector<Node> linkedTo; //i'm not sure if this is going to work... needs to store a flexibly sized group of things that
    int lifespan;
    int deathClock;
    
};





#include <stdio.h>

#endif /* node_hpp */
