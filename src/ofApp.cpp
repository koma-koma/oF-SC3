#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0, 0, 0);
  
  oscSender.setup("127.0.0.1", 57110);
  
  synth = "fm1";
  objcount = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
  for(vector <oscSendObject *>::iterator it = objects.begin(); it != objects.end(); ++it){
    (*it)->update();
    ofxOscMessage m = (*it)->msgSetArg();
    oscSender.sendMessage(m);
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  for(vector <oscSendObject *>::iterator it = objects.begin(); it != objects.end(); ++it){
    (*it)->draw();
  }
  ofSetColor(255, 255, 255);
  ofDrawBitmapString("objcount: " + ofToString(objcount), 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
  // add new object
  objects.push_back(new oscSendObject(objcount, ofPoint(x, y), synth, 1000+objcount));
  ofxOscMessage m = objects.back()->msgPlaySynth();
  oscSender.sendMessage(m);
  for(vector <oscSendObject *>::iterator it = objects.begin(); it != objects.end(); ++it){
    (*it)->addOtherObjects(objects); // add last object to other objects
  }
  objcount++;
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

void ofApp::exit() {
  for(vector <oscSendObject *>::iterator it = objects.begin(); it != objects.end(); ++it){
    (*it)->update();
    ofxOscMessage m = (*it)->msgStopSynth();
    oscSender.sendMessage(m);
  }

}
