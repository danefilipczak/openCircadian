//
//  target.hpp
//  Circadian
//
//  Created by Dane Filipczak on 7/11/17.
//
//


#ifndef target_hpp
#define target_hpp
#include "ofMain.h"

class Target{
    
public:
    
    
    void setup(ofVec3f pos);
    
    void setPosition(ofVec3f pos);
    
    void draw();
    
    
    const ofPoint& getPosition() const {
        return position;
    };
    
    
private:
    ofVec3f position;
    //ofPlanePrimitive plane;
};


#include <stdio.h>

#endif /* target_hpp */
