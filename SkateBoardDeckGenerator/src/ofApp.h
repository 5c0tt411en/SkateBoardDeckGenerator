#pragma once

#include "ofMain.h"
#include "ofxVectorGraphics.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"

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
    
    void trackPos(ofPoint &tp);
    void lengthInfo(ofPoint &p1, ofPoint &p2, float d);
    void A4Paper(int n);
    
    
    //UI
    ofxUISuperCanvas *gui0;
    void guiEvent(ofxUIEventArgs &e);
    void exit();
    
    //xmlsettings
    ofxXmlSettings settings;
    
    //Vector graphics
    ofxVectorGraphics output;
    
    bool capture = false;
    
    int   param01, param02, param03, param04, param05, param06, param07, param08,
    logAlpha = 0, pNum;
    ofPoint point01From, point01ToN, point01ToP,
    point02From, point02ToN, point02ToP,
    point03From, point03ToN, point03ToP,
    point04From, point04ToN, point04ToP,
    track01, track02, track01B, track02B,
    logView;
    
    const float circleSize    = 3.0,
    screwWidth    = 41.0,
    screwHeight   = 53.0,
    screwLineSize = 8.0,
    A4Width       = 297.0,
    A4Height      = 210.0;
    string fileName;
    bool bA4;
};
