#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    //ofDisableArbTex();
    ofSetGlobalAmbientColor(ofColor(255));
    nodes.reserve(1000); //a hack
    
    stop = false;
    //OSC boilerplate
    receiver.setup(RECEIVE_PORT);
    sender.setup(HOST, SEND_PORT);
    ofSetFrameRate(60); //this supposedly will keep the OSC from bugging everything. Probably best to just keep the clock lower on SC however
    
    float icoR = 100;
    icosahedron = ofMesh::icosahedron(icoR);
    vector<ofVec3f> verts = icosahedron.getVertices();
    float skew = 5; //for making all the edges not split at once
    for (auto & v : verts){
        Node n;
        n.setup(v.x+ofRandom(skew),
                v.y+ofRandom(skew),
                v.z+ofRandom(skew));
        nodes.push_back(n);
    }
    for (auto & n : nodes){
        for (auto & nn : nodes){
            if(n.getPosition() != nn.getPosition()){
                if(n.getPosition().distance(nn.getPosition())<icoR*1.5){
                    nn.linkWith(&n); //why did this not work when I tried to link it with a full node ob?????
                };
            };
        };
    };
    
    
    //edgeSplit(icoR);
//    for (var i = 0; i < nodes.length; i++) {
//        for (var j = 0; j < nodes.length; j++) {
//            if(i!==j){
//                var iVec = new THREE.Vector3();
//                iVec.copy(nodes[i].sphere.position);
//                var jVec = new THREE.Vector3();
//                jVec.copy(nodes[j].sphere.position);
//                if(jVec.distanceTo(iVec)<geomThresh){
//                    nodes[j].linkedTo.push(nodes[i]);
//                    //nodes[i].linkedTo.push(nodes[j]);
//                }
//            }
//        }
//    }
    
    
    //tex.loadImage("iceland.jpg");
    //tex.allocate(<#const ofTextureData &textureData#>)
    
    mothMaterial.setShininess(120);
    mothMaterial.setSpecularColor(ofColor(0));
    mothMaterial.setDiffuseColor(ofColor(200));
    mothMaterial.setAmbientColor(ofColor(100));
//
    targetMaterial.setShininess(120);
    targetMaterial.setSpecularColor(ofColor(255, 100));
    targetMaterial.setDiffuseColor(ofColor(200, 100));
    targetMaterial.setAmbientColor(ofColor(100));
//    
//    Moth m;
//    m.setup(numMoths, ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), ofRandom(ofGetHeight()));
//    moths.push_back(m);
//    
//    //    light.setSpotlight();
//    
//    
    
    
    //lights
    ofSetSmoothLighting(true);
    light.setPosition(0, 1000, 1000);
    light.setDiffuseColor( ofColor(255) );
    light.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    
    
    
    //moths.resize(500);
    targets.resize(20); //we want exactly ten targets... maybe?
    
    addMoth();
    
//    for (auto & m : moths){
//        //ofVec3f location(ofGetWidth(), ofGetHeight());
//        m.setup(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), ofRandom(ofGetHeight()));
//    }
    float y = 0;
    
    
    //either of the following vector iterating syntaxes work
    //    for (auto & t : targets){
    //
    //        t.setup(ofVec3f(0, -100+(y*50), 0));
    //        y++;
    //
    //    }
    
    ofEnableDepthTest();
    
    for (auto t = targets.begin(); t != targets.end(); t++){
        t->setup(ofVec3f(0, -500+(y*200), 0));
        y++;
    };
    
    
    
    //    material.setDiffuseColor(ofFloatColor(.85, .85, .55));
    //    material.setShininess(0.01);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // OSC STUFF
    while(receiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        if(m.getAddress()=="/noteOn"){
            
            for(int i = 0; i<20; i++){
                partials[i] = m.getArgAsFloat(i);
            };
            
        };
        
    };

    
    //    MOTH STUFF
    if(moths.size()<200){addMoth();};
    for (auto & m : moths){
        m.applyBehaviors(moths, targets);
        m.update();
        
//        ofxOscMessage out;
//        out.setAddress("moth");
//        out.addIntArg(m.getId());
//        
//        out.addFloatArg(m.getPosition().x);
//        out.addFloatArg(m.getPosition().y);
//        out.addFloatArg(m.getPosition().z);
    }
    
    
    // NODE STUFF
    //add forces
    
    
    rejectAll(500, 1); //thresh, then force
    
    //commit forces. with springyness????
    for(auto & n : nodes){
        n.applyForce();
    }
    
    
    if(!stop && nodes.size()<100){
        //consistently breaks on 17. wtf.
        edgeSplit(300);
    }
    
    
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //ofBackground(255, 255, 255);
    ofBackground(100, 100, 100);
    
    ofEnableDepthTest();
    
    ofEnableLighting();
    camera.begin();
    light.enable();
    
    
    // draw something
    //icosahedron.drawWireframe();
    //    material.begin();
    //    sphere.draw();
    //    material.end();
    mothMaterial.begin();
    for (auto & m : moths){
        m.draw();
    }
    mothMaterial.end();
    
    
   
    for (auto & n : nodes){
        n.draw();
    }
    
    
    light.disable();
    //targetMaterial.begin();
    //tex.getTextureReference().bind();
    ofSetColor(255, 255, 50, 100);
    for (auto & t : targets){
        t.draw();
    };
    //tex.getTextureReference().unbind();
    //targetMaterial.end();
   
    
    
    
    
    camera.end();
    
   
    


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    stop = true;
    
    float y = 0;
    for (auto & t : targets){
        
        t.setPosition(ofVec3f(0, -200+(y*40), 0));
        y++;
        
    }
    
    //moths.at(1);

}

//-------------------------------------------------


//helper function

vector<Node*> intersection(vector<Node*> v1, vector<Node*> v2)
{
    
    vector<Node*> v3;
    
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    
    set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));
    
    return v3;
}




void ofApp::edgeSplit(float thresh){
    //for(auto & i : nodes){
    //it's really dumb to loop through a vector using iterators if you're also going to be adding to the vector during the loop... an index-based loop works better.
   
    int oldSize = nodes.size();
    //Node bud;
    for(int i = 0; i<oldSize; i++){
       
        vector<Node*> growth = nodes[i].getNeighborsFartherThan(thresh);
        //Node* close = nodes[i].getANeighborFartherThan(thresh);
        
        if(growth.size()>0){
            
            //cout << growth.size();
            //for(auto & j : growth){
            Node* j = growth[0];
            
                
                //first, make a new node, during which we link it up to its parents
            
            
            
            Node bud = nodes[i].growMidpoint(j);
            nodes.push_back(bud);
            
            //then, push it to its final resting place.
            
            Node* budRef = &nodes.back();
        
            nodes[i].breakLink(j);
            j->breakLink(&nodes[i]);
        
            vector<Node*> overlap = intersection(nodes[i].getLinkedTo(), j->getLinkedTo());
            for(auto & k : overlap){
                budRef->linkWith(k);
                k->linkWith(budRef);
            }

            budRef->linkWith(&nodes[i]);
            budRef->linkWith(j);
            
            
            nodes[i].linkWith(budRef);
            j->linkWith(budRef);
            
            
            
            
                
                
            //}
            
            
            //stop = true;//just for debugging
            break; //stop looking through the nodes
        }
        
        
    }

    
    
}


//function edgeSplit(sThresh){
//    for(var i=0; i<nodes.length;i++){
//        for(var j=0; j<nodes[i].linkedTo.length;j++){
//            if(nodes[i].sphere.position.distanceTo(nodes[i].linkedTo[j].sphere.position)>sThresh){
//                
//                nodes[i].growMidpoint(nodes[i].linkedTo[j]);
//                
//                
//            }
//        }
//    }
//}

//-----------------------------------------------------


void ofApp::rejectAll(float rThresh, float rForce){
    for(auto & i : nodes){
        ofVec3f ip = i.getPosition();
        for(auto & j : nodes){
            ofVec3f jp = j.getPosition();
            if(ip != jp){
                if(ip.distance(jp)<rThresh){
                    ofVec3f force = ip - jp;
                    force.normalize();
                    i.addForce(force *= rForce/nodes.size());
                    j.addForce(-force *= rForce/nodes.size());
                };
            };
        };
    };
};

//function rejectAll(rThresh, rForce){
//    for (var i = 0; i < nodes.length-1; i++) {
//        for (var j = i+1; j < nodes.length; j++) {
//            if(i!==j){
//                var iVec = new THREE.Vector3();
//                iVec.copy(nodes[i].sphere.position);
//                var jVec = new THREE.Vector3();
//                jVec.copy(nodes[j].sphere.position);
//                if(jVec.distanceTo(iVec)<rThresh){
//                    var forceVector = jVec.sub(iVec);
//                    forceVector.normalize();
//                    forceVector.multiplyScalar(rForce/nodes.length);
//                    nodes[i].addForce(forceVector);
//                    nodes[j].addForce(forceVector.multiplyScalar(-1));
//                }
//            }
//        }
//    }
//}


//------------------------------------------------------------

void ofApp::addMoth(){
    float w = ofGetWidth();
    float h = ofGetHeight();

    Moth m;
     m.setup(numMoths, ofRandom(w)-(w/2), ofRandom(w)-(w/2), ofRandom(w)-(w/2));
    moths.push_back(m);
    numMoths++;
    
}




//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
