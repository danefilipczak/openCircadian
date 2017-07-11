//
//  moth.cpp
//  Circadian
//
//  Created by Dane Filipczak on 7/11/17.
//
//

#include "moth.hpp"
#include "target.hpp"



void Moth::setup(float x, float y, float z){
    
    position.set(x, y, z);
    r = 12;
    maxspeed = 20;
    maxforce = 0.1;
    acceleration.set(0, 0, 0);
    velocity.set(0, 0, 0);
    active = false;
    //sphere.setResolution(2);
    
}




void Moth::applyForce(const ofVec3f & force) {
    // We could add mass here if we want A = F / M
    ofVec3f f(force);
    acceleration += force;
}


void Moth::applyBehaviors(vector<Moth> moths, vector<Target> targets) {
    ofVec3f separateForce = separate(moths);
    
    separateForce*=1;
    separateForce.y*=separateY;
    applyForce(separateForce);
    
    ofVec3f seekForce = seek(getClosestTarget(targets));
    //ofVec3f seekForce = seek(ofVec3f(0, 0, 0));
    seekForce*=3;
    seekForce.y*=seekY;
    applyForce(seekForce);
    
}


ofVec3f Moth::seek(const ofVec3f & target){
    ofVec3f desired;
    desired = target - position;
    
    desired.normalize();
    desired*=maxspeed;
    
    ofVec3f steer;
    //STEERING IS EQUAL TO DESIRED MINUS VELOCITY
    steer = desired - velocity;
    steer.limit(maxforce);
    
    return steer;
}

ofVec3f Moth::separate(vector<Moth> moths){
    float desiredseparation = r*2;
    ofVec3f sum;
    int count = 0;
    
    vector<Moth>::iterator other;
    for (other = moths.begin(); other < moths.end(); other++){
        float d = (position - other->getPosition()).length();
        if((d>0) && (d < desiredseparation)){
            
            ofPoint diff = position - other->getPosition();
            diff.normalize();
            diff /= d;
            sum+= diff;
            count ++;
        }
    }
    if(count > 0){
        sum /= count;
        sum.normalize();
        sum*=maxspeed;
        
        sum -= velocity;
        sum.limit(maxforce);
    }
    return sum;
}


ofVec3f Moth::getClosestTarget(vector<Target> targets){
    Target closest = targets.at(0);
    float shortestD = 10000;
    for (Target t : targets){
        float dist = t.getPosition().distance(position);
        if(dist<shortestD){
            
            closest = t;
            shortestD = dist;
            
        }
    }
    
    return closest.getPosition();
}


void Moth::draw(){
    //float angle = ofRadToDeg(atan2(velocity.y,velocity.x)) + 90;
    
    ofPushMatrix();
    
    ofSetColor(0, 100);
    ofTranslate(position.x, position.y, position.z);
    //ofRotate(angle);
    //ofDrawCircle(0, 0, 0, r/2);
    ofDrawIcoSphere(0, 0, 0, r/2);
    //ofDraw
    //sphere.drawWireframe();
    ofPopMatrix();
}


void Moth::update(){
    velocity += acceleration;
    position += velocity;
    velocity.limit(maxspeed);
    acceleration *= 0;
}
