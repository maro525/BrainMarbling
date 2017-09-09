//
// Created by Hidemaro Fujinami on 2017/08/30.
//

#pragma once
#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxCsv.h"
#include "ofxOsc.h"

#define PORT 12345
#define BANDS 5
#define CHANNEL 16

class DataController {

public:
    void setup() {
        
        receiver.setup(PORT);
        
        udp.Create();
        udp.Connect("127.0.0.1", 1111);
        udp.SetNonBlocking(true);
    
        ofSetCircleResolution(100);
    }
    
    // bandsパワーが16チャンネル送られてくるのを受け取る関数
    void getData() {
        
        int index = 0;
        while(receiver.hasWaitingMessages()) {
            index++;
            
            ofxOscMessage *m = new ofxOscMessage;
            receiver.getNextMessage(m);
            
            if (m->getAddress() == address) {
                
                if (m->getNumArgs() == 1) raw_data_list.clear();
                
                vector<float> data;
                
                for (int i = 0; i < m->getNumArgs(); i++) {
                    
                    if (m->getArgType(i) == OFXOSC_TYPE_FLOAT) {
                        
                        data.push_back(m->getArgAsFloat(i));
//                    std::cout << "m->getArgAsFloat(" << i << ")" << m->getArgAsFloat(i) << endl;
                    }
                }
                
                raw_data_list.push_back(data);
            }
            
            delete m;

//        std::cout << "index:" << index << endl;
        }

//    std::cout << "raw_data_list.size() = " <<  raw_data_list.size() << endl;
    }
    

    
    // 整形されたデータを作成する関数
    void shapeData() {
        
        if(raw_data_list.size() != 0) {
            float band_power[BANDS] = {0, 0, 0, 0, 0};
    
            int index = raw_data_list.size() / CHANNEL - 1;
            //    std::cout << "index = " << index << endl;
    
            for (int i = 0; i < CHANNEL; i++) {
        
                //        std::cout << "raw_data_list.at(index * CHANNEL + i).size = " << raw_data_list.at(index * CHANNEL + i).size() << endl;
        
                band_power[0] += raw_data_list.at(index * CHANNEL + i).at(0);
                band_power[1] += raw_data_list.at(index * CHANNEL + i).at(1);
                band_power[2] += raw_data_list.at(index * CHANNEL + i).at(2);
                band_power[3] += raw_data_list.at(index * CHANNEL + i).at(3);
                band_power[4] += raw_data_list.at(index * CHANNEL + i).at(4);
        
            }
    
            //    std::cout << "band_power = " << band_power << endl;
    
            vector<float> tmp;
            ofxCsvRow row;
            string send_str = "";
            for (int i = 0; i < BANDS; i++) {
                tmp.push_back(band_power[i]);
        
                row.setFloat(i, band_power[i]);
        
                send_str += ofToString(band_power[i]) + "|";
            }
    
            csv.addRow(row);
    
            shaped_data_list.push_back(tmp);
    
            udp.Send(send_str.c_str(), send_str.length());
        }
    }
    
    void saveToCsv() {
        csv.save("shaped_data.csv");
    }
    
    void drawData() {
        
        if(shaped_data_list.size() != 0) {
            int size = shaped_data_list.size();
            
            for(int i = 0; i < BANDS; i++) {
                
                float band = shaped_data_list.at(size-1).at(i);
                
                if(band > 100) ofSetColor(255, 0, 0);
                else ofSetColor(0, 0, 255);
                
                float centY = ofGetHeight() / 2;
                float centX = ofGetWidth() * (i+1) /6;
                
                ofDrawCircle(centX, centY, band);
            }
        }
    }

    
    bool getFocusBool() {return focus;}
    
    float getBeta() {
        
        float beta = 0;
        
        if(shaped_data_list.size() != 0) {
            
            int size = shaped_data_list.size();
            
            beta = shaped_data_list.at(size-1).at(4);
        }
        
        return beta;
    }

private:
    
    ofxOscReceiver receiver;
    string address = "/openbci";
    ofxOscReceiver focus_receiver;
    string focus_address = "/focus";
    
    vector<vector<float>> raw_data_list;
    vector<vector<float>> shaped_data_list;
    
    ofxCsv csv;
    
    bool focus;
    
    ofxUDPManager udp;
};
