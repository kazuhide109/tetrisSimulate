//
//  blocks.cpp
//  tetrisSimulate
//
//  Created by LIFE_MAC_46 on 2021/01/14.
//

#include "blocks.hpp"

void Blocks::setup(){
     timeThred = 1.f;
     settingThred = 1.f;
     reset();
     
};

void Blocks::update(){
     //時間経過
     if(ofGetElapsedTimef() - saveTime > timeThred){
          moveCheck(2);
          saveTime = ofGetElapsedTimef();
     }
     
     if(stackCnt > 1){
          stackCnt = 0;
          saveArea();
          timeThred = settingThred;
          if(s_block.isLoaded())s_block.play();
     }
     
     if(line.size()>0){
          if(s_delete.isLoaded())s_delete.play();
          if(ofGetElapsedTimef() - saveTime > timeThred-0.5f){
               deleteLines(saveField_in);
          }
     }
};

void Blocks::draw(){
     
};

void Blocks::shuffle() {
     vector<int> list;
     int size = 7;
     for(int i = 0; i < size; i++) {
          list.push_back(i);
     }
     for(int i = 0; i < size; i++){
          int j = rand() % size;
          int t = list[i];
          list[i] = list[j];
          list[j] = t;
     }
     for(int i = 0; i < size; i++) {
          nextBlocks.push_back(list[i]);
     }
     
}

void Blocks::saveArea(){
     //ブロックの積み上げか入れ替えかの判断
     if(pKeepBlock == keepBlock){
          for(int i=0; i<4; i++){
               for(int j=0; j<4; j++){
                    if(selectBlock[i][j] == 1)
                         saveField[int(nowPos.x)+i][int(nowPos.y)+j] += selectBlock[i][j]*(nowSelect+1);
               }
          }
          checkTetris(); //テトリス判定
     }
     //keepを1回使っているかの判断
     if(pKeepBlock == keepBlock || pKeepBlock == -1){
          nextBlocks.erase(nextBlocks.begin());
          if(nextBlocks.size()<8) shuffle(); //ブロックの補充
          nowSelect = nextBlocks[0];
          totalBlockNum++;
     }else{
          nowSelect = pKeepBlock;
     }
     
     if(nowSelect>=7) nowSelect=0;
     selectBlock = select(selectBlock,nowSelect);
     nowPos.set(2, 2);
     pKeepBlock = keepBlock;
}

void Blocks::moveCheck(int direction){
     saveTime = ofGetElapsedTimef();
     vector<ofVec4f> in;
     in.resize(4);
     for(int i=0; i<4; i++){
          for(int j=0; j<4; j++){
               in[i][j] = selectBlock[i][j];
          }
     }
     if(direction == 0) nowPos.x--;
     else if(direction == 1) nowPos.x++;
     else if(direction == 2) nowPos.y++;
     
     
     if(check(in, nowPos)){
          if(direction == 0) nowPos.x++;
          else if(direction == 1) nowPos.x--;
          else if(direction == 2){
               nowPos.y--;
               stackCnt++;
          }
     }else{
          stackCnt = 0;
     }
}

void Blocks::rotateCheck(int direction){
     vector<ofVec4f> in;
     in.resize(4);
     vector<ofVec4f> ins;
     ins.resize(4);
     in = selectBlock;
     ins = selectBlock;
     
     for(int i=0; i<4; i++){
          for(int j=0; j<4; j++){
               int p;
               int q;
               p = direction ? j : -j+3;
               q = direction ? -i+3 : i;
               selectBlock[i][j] = in[p][q];
          }
     }
     if(check(selectBlock, nowPos))
          selectBlock = ins;
}

bool Blocks::check(vector<ofVec4f> _in, ofVec2f pos){
     bool reject = false;
          for(int i=0; i<4; i++){
               for(int j=0; j<4; j++){
                    if(_in[i][j] != 0){
                         if(int(pos.x)+i < 0 || int(pos.x)+i >= fieldCol || int(pos.y)+j >= fieldRow){
                              reject = true;
//                              cout << "moveRejectA:" << endl;
                              break;
                         }
                    }
                    int px = int(pos.x) + i;
                    int py = int(pos.y) + j;
                    if(px >= 0 && px < fieldCol && py >= 0 && py < fieldRow){
                         if(saveField[px][py] != 0){
                              if(saveField[int(pos.x)+i][int(pos.y)+j]!=0 && selectBlock[i][j] != 0){
                                   reject = true;
//                                   cout << "moveRejectB" << endl;
                                   break;
                              }
                         }
                    }
               }
          }
     return reject;
}

void Blocks::checkTetris(){
     cout << "checkTetris" << endl;
     line.resize(0);
     for(int j=0; j<fieldRow; j++){
          int count = 0;
          for(int i=0; i<fieldCol; i++){
               saveField_in[i][j] = 0;
               if(saveField[i][j]!=0){
                    count++;
                    if(count == 10){
                         line.push_back(j);
                         cout << "Tetris!" << endl;
                    }
               }
               saveField_in[i][j] = saveField[i][j];
          }
     }
     
}

void Blocks::deleteLines(int _saveField_in[fieldCol][fieldRow]){
     //列消し処理
     if(line.size()>0){
          for(int k=0; k<line.size(); k++){
               for(int i=0; i<fieldCol; i++){
                    saveField[i][line[k]] = 0;
                    for(int j=line[k]; j>=0; j--){
                         if(j==0) saveField[i][j] = 0;
                         else{
                              saveField[i][j] = _saveField_in[i][j-1];
                              _saveField_in[i][j] = saveField[i][j];
                         }
                    }
               }
          }
     }
     line.clear();
}

void Blocks::downShift(){
     while(1){
          moveCheck(2);
          if(stackCnt>1) break;
     }
}

void Blocks::keep(){
     keepBlock = nowSelect;
     saveArea();
}


void Blocks::reset(){
     nowPos.set(2,2);
     nextBlocks.clear();
     for(int k=0; k<2; k++){
          shuffle();
     }
     nowSelect = nextBlocks[0];
     selectBlock = select(selectBlock, nowSelect);
     for(int i=0; i<fieldCol; i++){
          for(int j=0; j<fieldRow; j++){
                    saveField[i][j] = 0;
          }
     }
     saveTime = ofGetElapsedTimef();
     totalBlockNum = 0;
     keepBlock = -1;
     pKeepBlock = -1;
}

void Blocks::setBlockSound(string file){
     s_block.load(file);
     s_block.setVolume(0.75f);
     s_block.setLoop(false);
     s_block.setMultiPlay(true);
}

void Blocks::setDeleteSound(string file){
     s_delete.load(file);
     s_delete.setVolume(0.75f);
     s_delete.setLoop(false);
     s_delete.setMultiPlay(false);
}

vector<ofVec4f> Blocks::select(vector<ofVec4f> in, int num){
     switch (num) {
          case 0:
               in = O;
               break;
          case 1:
               in = I;
               break;
          case 2:
               in = T;
               break;
          case 3:
               in = S;
               break;
          case 4:
               in = Z;
               break;
          case 5:
               in = L;
               break;
          case 6:
               in = J;
               break;
               
          default:
               break;
     }
     return in;
};
