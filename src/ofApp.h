#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxOpenCv.h"
#include "ofxOpenNI.h"

#include "ofxGui.h"

#include "oscSendObject.h"

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
  
  void exit();
  
  ofxOpenNI kinect;
  
  // openCV contourFinder-----------------------
  ofImage kinectImage; // kinectの画像
  ofImage kirinuki; // 深度によって切り抜かれた画像
  ofImage kirinuki_BnW; // 切り抜かれた部分を2値化
  ofxCvColorImage colorImg;
  ofxCvGrayscaleImage grayImage;
  ofxCvGrayscaleImage grayBg;
  ofxCvGrayscaleImage grayDiff;
  ofxCvContourFinder contourFinder;
  
  // gui: openCV
  ofxPanel gui;
  ofxIntSlider groundLevel; // kinectから床面までの距離
  ofxIntSlider threshold;
  ofxFloatSlider minBlobSize; // 物体の最小サイズ
  ofxFloatSlider maxBlobSize; // 物体の最大サイズ
  ofxIntSlider maxNumBlobs;
  ofxToggle findHoles;
  ofxToggle useApproximation;
  ofxFloatSlider fundamentalFreq;
  
  
  ofxOscSender oscSender;
  
  vector <oscSendObject *> objects;
  
  string synth;
  int objcount;
};
