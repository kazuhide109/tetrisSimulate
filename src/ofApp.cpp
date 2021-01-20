#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
     ofBackground(80);
     ofSetFrameRate(120);
     ofSetVerticalSync(false);
     ofSetWindowTitle("TETRIS");
     
     //初期化
     fieldSize.set(500, 1000);
     blockSize.set(fieldSize.x/fieldCol, fieldSize.y/fieldRow);
     isDebug = true;
     isPause = true;
     
     //ゲーム内容の初期化
     blocks.setup();
     
     //KeyBoard UI
     firstWindowSize.set(ofGetWidth(), ofGetHeight());
     uiFont.load("verdana.ttf", 8);
     keyStatuses.resize(colrow.x*colrow.y);
}

//--------------------------------------------------------------
void ofApp::update(){
     //一時停止時
     if(isPause)
          blocks.saveTime = ofGetElapsedTimef();
     
     //ゲーム進行の更新
     blocks.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
     ofSetColor(255);
     
     //Field
     ofVec2f resFieldSize = {(fieldSize.x/firstWindowSize.x)*ofGetWidth(), (fieldSize.y/firstWindowSize.y)*ofGetHeight()};
     resFieldSize;
     ofPushMatrix();
     ofTranslate(ofGetWidth()/2-resFieldSize.x/2, (ofGetHeight()-resFieldSize.y)/2);
     ofSetColor(10);
     ofDrawRectangle(0, 0, resFieldSize.x, resFieldSize.y);
     
     //NextBlock
     for(int k=0; k<4; k++){
          ofRectangle rectNextBox;
          rectNextBox.set(resFieldSize.x + resFieldSize.x*0.1, k*(resFieldSize.x*0.2 + resFieldSize.x*0.1), resFieldSize.x*0.2, resFieldSize.x*0.2);
          ofSetColor(10);
          ofDrawRectangle(rectNextBox);
          ofSetColor(255);
          for(int i=0; i<4; i++){
               for(int j=0; j<4; j++){
                    vector<ofVec4f> next;
                    next = blocks.select(next, blocks.nextBlocks[1+k]);
                    ofRectangle rect;
                    rect.setSize(rectNextBox.width/4, rectNextBox.height/4);
                    rect.setPosition(rectNextBox.x + i*rect.width, (rectNextBox.y + j*rect.height));
                    next[i][j] ? ofSetColor(blocks.colors[blocks.nextBlocks[1+k]], 255) : ofSetColor(200, 200, 200, 0);
                    ofDrawRectangle(rect);
               }
          }
     }
     
     //KeepBlock
     ofRectangle rectKeepBox;
     rectKeepBox.set(-resFieldSize.x*0.2 - resFieldSize.x*0.1, 0, resFieldSize.x*0.2, resFieldSize.x*0.2);
     ofSetColor(10);
     ofDrawRectangle(rectKeepBox);
     if(blocks.keepBlock != -1){
          for(int i=0; i<4; i++){
               for(int j=0; j<4; j++){
                    vector<ofVec4f> next;
                    next = blocks.select(next, blocks.keepBlock);
                    ofRectangle rect;
                    rect.setSize(rectKeepBox.width/4, rectKeepBox.height/4);
                    rect.setPosition(rectKeepBox.x + i*rect.width, rectKeepBox.y + j*rect.height);
                    next[i][j] ? ofSetColor(blocks.colors[blocks.keepBlock], 255) : ofSetColor(200, 200, 200, 0);
                    ofDrawRectangle(rect);
               }
          }
     }
     
     int col = fieldCol;
     int row = fieldRow -mergeRow;
     ofTranslate(0, -(resFieldSize.y/row)*mergeRow);
     
     //Guide
     vector<ofVec4f> guideIn;
     guideIn = blocks.selectBlock;
     int i=0;
     ofVec2f guidePos;
     guidePos = blocks.nowPos;
     while(i < 25) {
          if(blocks.check(guideIn, guidePos)) break;
          guidePos.y += 1;
     }
     guidePos.y -= 1;
     for(int i=0; i<4; i++){
          for(int j=0; j<4; j++){
               ofRectangle rect;
               rect.setSize(resFieldSize.x/col, resFieldSize.y/row);
               rect.setPosition((i + guidePos.x)*rect.width, (j + guidePos.y)*rect.height);
                    if(blocks.selectBlock[i][j]){
                         if(guidePos.y + j > 4){
                              ofSetColor(255, 120);
                              ofDrawRectangle(rect);
                         }
                    }
          }
     }
     
     //Select Block
     for(int i=0; i<4; i++){
          for(int j=0; j<4; j++){
               ofRectangle rect;
               rect.setSize(resFieldSize.x/col, resFieldSize.y/row);
               rect.setPosition((i + blocks.nowPos.x)*rect.width, (j + blocks.nowPos.y)*rect.height);
               if(isDebug){
                    blocks.selectBlock[i][j] ? ofSetColor(blocks.colors[blocks.nowSelect], 255) : ofSetColor(200, 200, 200, 80);
                     ofDrawRectangle(rect);
               }else{
                    if(blocks.selectBlock[i][j]){
                         if(blocks.nowPos.y + j > 4){
                              ofSetColor(blocks.colors[blocks.nowSelect], 255);
                              ofDrawRectangle(rect);
                         }
                    }
               }
          }
     }
     
     float fixY = resFieldSize.y + (resFieldSize.y/row)*mergeRow;
     //Grid //Static Block
     for(int i=0; i<col; i++){
          for(int j=mergeRow; j<fieldRow; j++){
               ofFill();
               if(blocks.saveField[i][j] != 0){
                    ofSetColor(blocks.colors[blocks.saveField[i][j]-1]);
                    ofDrawRectangle(i*resFieldSize.x/col, j*fixY/fieldRow, resFieldSize.x/col, fixY/fieldRow);
               }
               ofNoFill();
               if(j >= mergeRow){
                    ofSetColor(100);
                    ofDrawRectangle(i*resFieldSize.x/col, j*fixY/fieldRow, resFieldSize.x/col, fixY/fieldRow);
               }
               ofFill();
               for(auto bl : blocks.line){
                    if(bl == j){
                         ofSetColor(180, 255, 255, 255);
                         ofDrawRectangle(i*resFieldSize.x/col, j*fixY/fieldRow, resFieldSize.x/col, fixY/fieldRow);
                    }
               }
          }
     }
     ofFill();
     ofPopMatrix();
     
     //Pause Message
     if(isPause){
          string pauseMes = "Press SPACE KEY to Restart";
          ofDrawBitmapStringHighlight(pauseMes, ofGetWidth()*0.45, ofGetHeight()/2);
     }
     
     //UI Explanattion
     ofPushMatrix();
     ofTranslate(ofGetWidth()*0.72, ofGetHeight()*0.85);
     ofRectangle areaRect;
     float areaSize = ofGetWidth()*0.25;
     areaRect.set(0, 0, (areaSize/firstWindowSize.x)*ofGetWidth(), (areaSize/4/firstWindowSize.y)*ofGetHeight());
     ofSetColor(10, 255);
     ofDrawRectangle(areaRect);
     for(int j=0; j<colrow.y; j++){
          for(int i=0; i<colrow.x; i++){
               ofVec2f xy = {areaRect.width/colrow.x, areaRect.height/colrow.y};
               xy = xy - xy*0.1;
               ofVec2f merge;
               merge.set((areaRect.width - (xy.x*colrow.x))/(colrow.x+1), (areaRect.height - (xy.y*colrow.y))/(colrow.y+1));
               ofRectangle box;
               box.set(i*(xy.x+merge.x)+merge.x, j*(xy.y+merge.y)+merge.y, xy.x, xy.y);
               uiStr[i+(j*colrow.x)] == " " ? ofSetColor(120, 255) : ofSetColor(230, 255);
               ofDrawRectRounded(box, 10);
               ofSetColor(10, 255);
               uiFont.drawString(uiStr[i+(j*colrow.x)], box.x+5, box.y+15);
          }
     }
     ofPopMatrix();
     
     //Debug
     if(isDebug){
          //Debug
          stringstream mes;
          mes << "FPS: " << ofToString(ofGetFrameRate());
          mes << "\n Pos: " << blocks.nowPos;
          mes << "\n GuidePos: " << guidePos;
          mes << "\n MINO_ID: " << blocks.nowSelect;
          mes << "\n Pause: " << isPause;
          mes << "\n TotalBlocks: " << blocks.totalBlockNum;
          for(int k=0; k<blocks.nextBlocks.size(); k++){
               mes << "\n " << k << ": " <<blocks.nextBlocks[k];
          }
          ofDrawBitmapStringHighlight(mes.str(), 10, 20);
     }

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
     switch (key) {
          case ' ':
               isPause = !isPause;
               break;
          case 'd':
               isDebug = !isDebug;
          break;
          case OF_KEY_RETURN:
               blocks.reset();
               isPause = true;
          break;
          case OF_KEY_LEFT:
               blocks.moveCheck(0);
          break;
          case OF_KEY_RIGHT:
               blocks.moveCheck(1);
          break;
          case OF_KEY_DOWN:
               blocks.moveCheck(2);
          break;
          case OF_KEY_UP:
               blocks.downShift();
          break;
          case 'q':
               blocks.rotateCheck(0);
               cout << "rotateR" << endl;
               break;
          case 'w':
               blocks.rotateCheck(1);
               cout << "rotateL" << endl;
          break;
          case 'a':
               blocks.keep();
               cout << "keep" << endl;
          break;
               
          default:
               break;
     }

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
