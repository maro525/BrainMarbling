#pragma once

#include "ofMain.h"
#include "robot.h"
#include "DataController.h"
#include "MachineLearning.h"

class ofApp : public ofBaseApp{

public:
    
    void setup() {
        
        ofSetFrameRate(30);
    
        data_controller.setup();
        ml.setup();
    };
    
    void update(){
        
        data_controller.getData();
        data_controller.shapeData();
    
        r.update();
    
        if(bool_ml) {
        
            ml.ml_receive();
            focus = ml.getFocusBool();
        }else {
            float beta = data_controller.getBeta();
            if(beta > 60) focus = true;
            else focus = false;
        }
    };
    
    void draw(){
        ofBackground(255);
    
        data_controller.drawData();
    
        if(focus) r.setFocusWaiting();
    
        r.send();
    
        ////////////////////
        // 情報表示/////////
        ////////////////////
        int textX = 10;
        int textY = 20;
        string text = "";
        ofSetColor(0,0,0);
    
        text = "-------FOCUS STATUS--------";
        ofDrawBitmapString(text, textX, textY);
    
        if(bool_ml) ofSetColor(0, 255, 0);
        else ofSetColor(0, 0, 0);
        text = bool_ml ? "USING MACHINE LEARNING" : "NOT USING MACHINE LEARNING";
        textY += 15;
        ofDrawBitmapString(text, textX, textY);
    
        if(focus) ofSetColor(0, 255, 0);
        else ofSetColor(0, 0, 0);
        text = focus ? "FOCUS" : "NOT FOCUS";
        textY += 15;
        ofDrawBitmapString(text, textX, textY);
    
        ofSetColor(0, 0, 0);
        text = "-------ROBOT STATUS--------";
        textY += 30;
        ofDrawBitmapString(text, textX, textY);
    
        text = r.getStatus();
        textY += 15;
        ofDrawBitmapString(text, textX,textY);
    
        if(r.getTime() != 0 ) ofSetColor(255, 0, 0);
        else ofSetColor(0, 0, 0);
        text = ofToString(r.getTime());
        textY += 15;
        ofDrawBitmapString(text, textX, textY);
    
        ofSetColor(0, 0, 0);
        text = "key p : serial setup";
        textY += 30;
        ofDrawBitmapString(text, textX, textY);
    
        text = "key b : robot setup";
        textY += 15;
        ofDrawBitmapString(text, textX, textY);
    
        text = "key m : robot move";
        textY += 15;
        ofDrawBitmapString(text, textX, textY);
    
        text = "key s : robot supply";
        textY += 15;
        ofDrawBitmapString(text, textX, textY);
    
        text = "key q : bands power export to csv file";
        textY += 15;
        ofDrawBitmapString(text, textX, textY);
    
        text = "key 0 : Machine Learning Switch";
        textY += 15;
        ofDrawBitmapString(text, textX, textY);
    };
    
    void keyPressed(int key){
    
        if(key == 'b'){
        
            r.begin();
        
        } else if(key == 'm') {
        
            r.move();
        
        } else if(key == 's') {
        
            r.setFocusWaiting();
            r.supply();
        
        } else if(key == 'p') {
        
            r.setup();
        
        } else if(key == 'f'){
        
            r.setFinishWaiting();
            r.end();
        
        } else if(key == 'q') {
        
            data_controller.saveToCsv();
        
        } else if(key == '0') {
        
            bool_ml = !bool_ml;
        }
    };

    
    
private:
    
    DataController data_controller;
    robot r;
    MachineLearning ml;
    
    bool bool_ml = false;
    bool focus;
};
