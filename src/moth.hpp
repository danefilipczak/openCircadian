//
//  moth.hpp
//  Circadian
//
//  Created by Dane Filipczak on 7/11/17.
//
//
#include "ofMain.h"
#include "target.hpp"

class Moth{
public:
    void setFavoriteNumber(int);
    void setup(float, float, float);
    void applyForce(const ofVec3f & force);
    void applyBehaviors(vector<Moth> moths, vector<Target> targets);
    void update();
    void draw();
    ofVec3f getClosestTarget(vector<Target> targets);
    
    
    
    
    ofVec3f separate(vector<Moth> moths);
    ofVec3f seek(const ofVec3f & target);
    
    
    const ofPoint& getPosition() const {
        return position;
    }
    
private:
    int favoriteNumber;
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f acceleration;
    float r;
    float maxforce;    // Maximum steering force
    float maxspeed;    // Maximum speed
    bool active;
    float separateY = 10;
    float seekY = 0.8;
    
    //ofSpherePrimitive sphere;
};

#ifndef moth_hpp
#define moth_hpp

#include <stdio.h>

#endif /* moth_hpp */
