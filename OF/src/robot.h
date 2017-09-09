//
// Created by Hidemaro Fujinami on 2017/08/30.
//

#pragma once
#include "ofMain.h"

class robot {

public:
    
    void setup() {
        
        if(!bSerial) {
            serial.setup("/dev/cu.usbmodem1421", 9600);
            std::cout << "p pressed" << endl;
            
            startTime = ofGetElapsedTimeMillis();
            endTime = 1000;
            
            waiting = true;
            bSerial = true;
            
            status = "CONNECTED";
        }
    }
    
    void begin(){
    
        if(bSerial && !waiting) {
            
            serial.writeByte('b');
            std::cout << "b pressed" << endl;
            
            startTime = ofGetElapsedTimeMillis();
            endTime = 5000;
            
            waiting = true;
            bBegin = true;
            
            status = "ROBOT SETUP";
        }
    }
    
    void end(){
        
        if(bSerial && !waiting) {
            
            serial.writeByte('f');
            std::cout << "f pressed" << endl;
            
            bBegin = false;
            bSerial = false;
            
            status = "ROBOT END";
        }
    }
    
    void move(){
        
        if(bSerial && bBegin && !waiting) {
            
            serial.writeByte('m');
            std::cout << "m pressed" << endl;
            
            startTime = ofGetElapsedTimeMillis();
            endTime = 10000;
            
            waiting = true;
            
            status = "ROBOT MOVE";
        }
    }
    
    void supply() {
        
        if(bSerial && bBegin && !waiting && !supplyWaiting) {
            
            serial.writeByte('s');
            std::cout << "s pressed" << endl;
            
            startTime = ofGetElapsedTimeMillis();
            supplyStartTime = ofGetElapsedTimeMillis();
            
            endTime = 20000;
            supplyEndTime = 30000;
            
            waiting = true;
            supplyWaiting = true;
            
            status = "ROBOT SUPPLYING";
        }
    }
    
    void update() {
    
        if(supplyWaiting) {
            supplyTime = ofGetElapsedTimeMillis() - supplyStartTime;
            if (supplyTime >= supplyEndTime) supplyWaiting = false;
        } else {
            supplyEndTime = 0;
            supplyTime = 0;
        }
        
        if(waiting) {
            
            time = ofGetElapsedTimeMillis() - startTime;
            if(time >= endTime) waiting = false;
            
        } else {
            
            endTime = 0;
            
            time = 0;
            if(bSerial) status = "FREE";
            
        }
    }
    
    void send() {
        
        if(!waiting) {
            
            if(focusWaiting) {
                supply();
                focusWaiting = false;
            } else {
                move();
            }
        }
    }
    
    bool getBegin() { return bBegin; }
    bool getBSerial() { return bSerial; }
    bool getWaiting() { return waiting; }
    float getTime() { return (endTime - time)/1000; }
    string getStatus() { return status; }
    
    void setFocusWaiting() {
        if(!focusWaiting) focusWaiting  = true;
    }
    
    void setFinishWaiting() {
        if(!finishWaiting) finishWaiting = true;
    }
    
private:
    
    ofSerial serial;
    
    bool bBegin = false;
    bool bSerial = false;
    bool waiting = false;
    bool focusWaiting = false;
    bool supplyWaiting = false;
    bool finishWaiting = false;
    
    float startTime;
    float endTime;
    float time;
    
    float supplyStartTime;
    float supplyEndTime;
    float supplyTime;
    
    string status = "NOT CONNECTED";
};
