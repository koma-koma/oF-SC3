//
//  oscSendObject.cpp
//  kinectOscSuperCollider
//
//  Created by Miyashita Keita on 2017/05/24.
//
//

#include "oscSendObject.h"

oscSendObject::oscSendObject(int _obj_num, ofPoint _pos, string _synth_name, int _synth_id) {
  
  obj_num = _obj_num;
  
  pos = _pos;
  speed = ofPoint(ofRandom(-1, 1), ofRandom(-1, 1));
  radius = 15;
  
  max_dist = 0;
  max_dist_obj = 0;
  min_dist = ofGetWidth()*ofGetHeight();
  min_dist_obj = 0;
  
  synth_name = _synth_name;
  synth_id = _synth_id;
  
  freq = 220;
  carPartial = 1;
  modPartial = 1;
  index = 1;
  filter = 1000;
  mul = 0.5;
  pan = 0;
  del = 0.2;
}

void oscSendObject::update() {
  pos += speed;
  if(pos.x > ofGetWidth()-radius || pos.x < radius ) { speed.x *= -1; }
  if(pos.y > ofGetHeight()-radius || pos.y < radius ) { speed.y *= -1; }
  
  calcDist();
  // calculate synth argments
  freq = ofMap(obj_num, 0, otherObjects.size(), 220, 2200);
  modPartial = max_dist;
  carPartial = 1;
  index = ofMap(min_dist, radius, radius*100, 1, 100);
  filter = ofMap(pos.x, 0, ofGetWidth(), 100, 1500);
  mul = float(1.0 / otherObjects.size());
  pan = ofMap(pos.x, 0, ofGetWidth(), -1, 1);
  del = ofMap(max_dist, 0, ofGetWidth(), 0.01, 1);
}

void oscSendObject::draw() {
  ofSetColor(col);
  ofDrawCircle(pos, radius);
  ofDrawBitmapString(ofToString(obj_num), pos.x-5, pos.y-20);
  
  ofDrawBitmapString("max " + ofToString(max_dist_obj), pos.x-5, pos.y+30);
  ofDrawLine(pos, otherObjects[max_dist_obj]->getPos());
  
  ofSetColor(255, 0, 0);
  ofDrawBitmapString("min " + ofToString(min_dist_obj), pos.x-5, pos.y+50);
  ofDrawLine(pos, otherObjects[min_dist_obj]->getPos());
}

void oscSendObject::calcDist() {
  // 距離の最大値最小値計算を検討する必要があります
  // ----常に計算する
  int i = 0;
  if (otherObjects.size() > 1) {
    
    float max = 0;
    float min = ofGetWidth()*ofGetHeight();
    max_dist = max;
    min_dist = min;

    for(int i = 0; i < otherObjects.size(); i++) {
      if (i != obj_num) {
        float dist = ofDist(pos.x, pos.y, otherObjects[i]->getPos().x, otherObjects[i]->getPos().y);
        //ぶつかり判定
        if (dist < radius*2) {
          speed *= -1;
          break;
        }
        if (dist > max_dist) {
          max_dist = dist;
          max_dist_obj = i;
        }
        if (dist < min_dist) {
          min_dist = dist;
          min_dist_obj = i;
        }

      }
    }
  }
}

void oscSendObject::setPos(ofPoint _pos) {
  pos = _pos;
}

void oscSendObject::setSynth(string _synth_name, int _synth_id) {
  synth_name = _synth_name;
}

ofPoint oscSendObject::getPos() {
  return pos;
}

float oscSendObject::getArg(int _arg_num) {
  switch (_arg_num) {
    case 0:
      return freq;
      break;
      
    case 1:
      return carPartial;
      break;
      
    case 2:
      return modPartial;
      break;
      
    case 3:
      return index;
      break;
      
    case 4:
      return filter;
      break;
      
    default:
      break;
  }
}

ofxOscMessage oscSendObject::msgPlaySynth() {
  ofxOscMessage m;
  m.setAddress("/s_new");
  m.addStringArg(synth_name);
  m.addIntArg(synth_id);
  m.addIntArg(0);
  m.addIntArg(1);
  m.addStringArg("freq");
  m.addFloatArg(freq);
  m.addStringArg("carPartial");
  m.addFloatArg(carPartial);
  m.addStringArg("modPartial");
  m.addFloatArg(modPartial);
  m.addStringArg("index");
  m.addFloatArg(index);
  m.addStringArg("filter");
  m.addFloatArg(filter);
  m.addStringArg("mul");
  m.addFloatArg(mul);
  m.addStringArg("pan");
  m.addFloatArg(pan);
  m.addStringArg("del");
  m.addFloatArg(del);
  return m;
}

ofxOscMessage oscSendObject::msgSetArg() {
  ofxOscMessage m;
  m.setAddress("/n_set");
  m.addIntArg(synth_id);
  m.addStringArg("freq");
  m.addFloatArg(freq);
  m.addStringArg("carPartial");
  m.addFloatArg(carPartial);
  m.addStringArg("modPartial");
  m.addFloatArg(modPartial);
  m.addStringArg("index");
  m.addFloatArg(index);
  m.addStringArg("filter");
  m.addFloatArg(filter);
  m.addStringArg("mul");
  m.addFloatArg(mul);
  m.addStringArg("pan");
  m.addFloatArg(pan);
  m.addStringArg("del");
  m.addFloatArg(del);
  return m;
}

ofxOscMessage oscSendObject::msgStopSynth() {
  ofxOscMessage m;
  m.setAddress("/n_set");
  m.addIntArg(synth_id);
  m.addStringArg("gate");
  m.addIntArg(0);
  return m;
}


void oscSendObject::addOtherObjects(vector<oscSendObject *>_others) {
  otherObjects = _others; //othersの受け渡しを検討する必要があります
}
