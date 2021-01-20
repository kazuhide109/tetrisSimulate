#pragma once

#include "ofMain.h"

#include "blocks.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
     
     //描画
     ofVec2f fieldSize;
     ofVec2f firstWindowSize;
     ofVec2f blockSize;
     
     //状態制御
     bool isPause;
     bool isDebug;
     
     //ブロックの管理機能をまとめたクラス
     Blocks blocks;
     
     //KeyBoard UI
     ofTrueTypeFont uiFont;
     ofVec2f colrow = {8, 2};
     vector<string> uiStr = {"Q\nRotateL", "W\nRotateR", " ", " ", " ", " ", "UP", " ", "A\nKeep", " ", "SPACE\nPause", "ENTER\nReset", " ", "LEFT", "DOWN", "RIGHT"};
     vector<int> keyStatuses;
     
};
