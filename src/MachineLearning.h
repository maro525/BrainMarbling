//
// Created by Hidemaro Fujinami on 2017/08/30.
//

#pragma once

class MachineLearning {

public:
    
    void setup() {
        
        udp_rec.Create();
        udp_rec.Connect("127.0.0.1", 2222);
        udp_rec.SetNonBlocking(true);
    }
    
    void ml_receive () {
        
        char udpMessage[100000];
        udp_rec.Receive(udpMessage ,100000);
        string message = udpMessage;
        vector<string> strPnt = ofSplitString(message, "|");
        
        float answer;
        
        for(int i = 0; i < strPnt.size(); i++){
            vector<string> point = ofSplitString(strPnt[i], "|");
            answer = atof(point[0].c_str());
        }
//    std::cout << "message = " << answer << endl;
        
        if(answer == 1) focus = true;
        else focus = false;
    }
    
    bool getFocusBool() { return focus; }

private:
    
    ofxUDPManager udp_rec;
    
    bool focus;
};
