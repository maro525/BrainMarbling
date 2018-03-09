//
// Created by Hidemaro Fujinami on 2017/08/29.
//

#pragma once

#include "ofMain.h"

class Ink {

public:
    Ink() {
        radius = 0;
    };
    
    ~Ink();
    
    void draw() {
    
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
        ofSetColor(0);
//        ofSetLineWidth(2);
//        ofNoFill();
        
        ofDrawCircle(0, 0, radius);
    
        ofPopMatrix();
    }
    
    void addRadius() {
        radius += speed;
    }
    
    float getRadius() {
        return radius;
    }

private:
    float radius;
    float speed = 0.05;
};
