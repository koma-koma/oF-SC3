/*
 (
 SynthDef(\fm1, { arg bus = 0, gate = 1, freq = 440, detune = 0.01, carPartial = 1, modPartial = 1, index = 1, mul = 0.05, pan = 0;
 
	// index values usually are between 0 and 24
	// carPartial :: modPartial => car/mod ratio
	
	var mod;
	var car;
	var env;
	
	mod = SinOsc.ar(
 [freq * modPartial, freq * (1 + detune) * modPartial],
 0,
 freq * index
);

car = SinOsc.ar(
                (freq * carPartial) + mod,
                0,
                mul
                );

env = EnvGen.ar(Env.adsr(1, 1, 1, 1), gate, doneAction: 2);

car = Pan2.ar(car, pan) * env;
Out.ar(
       [0, 1],
       car
       )
}).store;
)

 */

#pragma once

#include "ofxOsc.h"

class oscSendObject {
public:
  oscSendObject(int obj_num, ofPoint _pos, string _synth_name, int _synth_id);
  
  void update();
  void draw();
  void calcDist();
  
  void setPos(ofPoint _pos);
  void setSynth(string _synth_name, int _synth_id);
  
  ofPoint getPos();
  float getArg(int _arg_name);
  
  ofxOscMessage msgPlaySynth();
  ofxOscMessage msgSetArg();
  ofxOscMessage msgStopSynth();
  
  void addOtherObjects(vector<oscSendObject *>_others);

private:
  int obj_num;
  
  // visual
  ofPoint pos;
  ofPoint speed;
  ofColor col;
  float radius;
  
  float max_dist;
  int max_dist_obj;
  float min_dist;
  int min_dist_obj;
  
  // sound
  string synth_name;
  int synth_id;
  
  // argment of synth
  float freq;
  float carPartial;
  float modPartial;
  float index;
  float filter;
  float mul;
  float pan;
  float del;
  
  vector<oscSendObject*>otherObjects;
  
};
