//
//  blocks.hpp
//  tetrisSimulate
//
//  Created by LIFE_MAC_46 on 2021/01/14.
//
#include "ofMain.h"

#define fieldCol 10
#define fieldRow 25
#define mergeRow 5

class Blocks : public ofBaseApp {
     
public:
     
     void setup();
     void update();
     void draw();
     void moveCheck(int direction);
     void rotateCheck(int direction);
     void saveArea();
     bool check(vector<ofVec4f> in);
     void checkTetris();
     void downShift();
     void keep();
     void reset();
     void shuffle();
     vector<ofVec4f> select(vector<ofVec4f> in, int num);
     
     float saveTime;
     float timeThred;
     float settingThred;
     
     vector<ofVec4f> selectBlock;
     vector<int> nextBlocks;
     int totalBlockNum;
     int nowSelect;
     int saveField[fieldCol][fieldRow];
     int stackCnt;
     int keepBlock;
     int pKeepBlock;
     ofVec2f nowPos;
     
     //各ブロックの格納行列
     vector<ofColor> colors = {
          {200, 200, 100},
          {100, 190, 210},
          {210, 100, 180},
          {220, 100, 100},
          {100, 220, 100},
          {230, 160, 80},
          {100, 100, 220}
     };
     
     vector<ofVec4f> O= {
          {0, 0, 0, 0},
          {0, 1, 1, 0},
          {0, 1, 1, 0},
          {0, 0, 0, 0}
     };
     
     vector<ofVec4f> I = {
          {0, 0, 1, 0},
          {0, 0, 1, 0},
          {0, 0, 1, 0},
          {0, 0, 1, 0}
     };
     
     vector<ofVec4f> T = {
          {0, 0, 0, 0},
          {0, 0, 1, 0},
          {0, 1, 1, 0},
          {0, 0, 1, 0}
     };
     
     vector<ofVec4f> S = {
          {0, 0, 0, 0},
          {0, 1, 0, 0},
          {0, 1, 1, 0},
          {0, 0, 1, 0}
     };
     
     vector<ofVec4f> Z = {
          {0, 0, 0, 0},
          {0, 0, 1, 0},
          {0, 1, 1, 0},
          {0, 1, 0, 0}
     };
     
     vector<ofVec4f> L = {
          {0, 0, 0, 0},
          {0, 0, 1, 0},
          {0, 0, 1, 0},
          {0, 1, 1, 0}
     };
     
     vector<ofVec4f> J = {
          {0, 0, 0, 0},
          {0, 1, 0, 0},
          {0, 1, 0, 0},
          {0, 1, 1, 0}
     };
     
     
};
