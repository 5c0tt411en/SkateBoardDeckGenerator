#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    output.noFill();
    output.setLineWidth(1);
    ofSetBackgroundColor(255);
    logView = ofPoint(20, ofGetHeight() - 50);
    
    //ofxUI
    gui0 = new ofxUISuperCanvas("deckGenarator");
    gui0->addSpacer();
    gui0->addTextArea("CURVE", "CURVE");
    gui0->addIntSlider("TOP", 0.0, 300.0, &param01);
    gui0->addIntSlider("SIDE", 0.0, 300.0, &param02);
    gui0->addIntSlider("BOTTOM", 0.0, 300.0, &param03);
    gui0->addSpacer();
    gui0->addTextArea("DECK SCALE", "DECK SCALE");
    gui0->addIntSlider("WIDTH", 70.0, 290.0, &param04);
    gui0->addIntSlider("LENGTH", 400.0, 800.0, &param05);
    gui0->addSpacer();
    gui0->addTextArea("ANCHOR POINT", "ANCHOR POINT");
    gui0->addIntSlider("SIDE ANCHOR POINT POSITION", 50, 300.0, &param06);
    gui0->addSpacer();
    gui0->addTextArea("TRACK POSITION", "TRACK POSITION");
    gui0->addIntSlider("DISTANCE FROM TOP EDGE ", 50.0, 120.0, &param07);
    gui0->addIntSlider("DISTANCE FROM BOTTOM EDGE", 50.0, 120.0, &param08);
    gui0->addSpacer();
    gui0->addLabel("A4 PAPER GUIDE");
    gui0->addToggle("A4 PAPER GUIDE", &bA4, 44, 44);
    gui0->addSpacer();
    gui0->addLabel("SAVE");
    gui0->addButton("SAVE", &capture, 44, 44);
    gui0->addSpacer();
    gui0->autoSizeToFitWidgets();
    
    //xmlsettings
    settings.loadFile("settings.xml");
    param01 = settings.getValue("settings:ui1", 0.0);
    param02 = settings.getValue("settings:ui2", 0.0);
    param03 = settings.getValue("settings:ui3", 0.0);
    param04 = settings.getValue("settings:ui4", 0.0);
    param05 = settings.getValue("settings:ui5", 0.0);
    param06 = settings.getValue("settings:ui6", 0.0);
    param07 = settings.getValue("settings:ui7", 0.0);
    param08 = settings.getValue("settings:ui8", 0.0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //TOP JOINT
    point01From = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2 - param05 / 2);
    point01ToN  = ofPoint(ofGetWidth() / 2 - param01, ofGetHeight() / 2 - param05 / 2);
    point01ToP  = ofPoint(ofGetWidth() / 2 + param01, ofGetHeight() / 2 - param05 / 2);
    //RIGHT JOINT
    point02From = ofPoint(ofGetWidth() / 2 + param04 / 2, 125 + param06);
    point02ToN  = ofPoint(ofGetWidth() / 2 + param04 / 2, point02From.y - param02);
    point02ToP  = ofPoint(ofGetWidth() / 2 + param04 / 2, point02From.y + param02);
    //BOTTOM JOINT
    point03From = ofPoint(point01From.x, ofGetHeight() / 2 + param05 / 2);
    point03ToN  = ofPoint(point01From.x + param03, ofGetHeight() / 2 + param05 / 2);
    point03ToP  = ofPoint(point01From.x - param03, ofGetHeight() / 2 + param05 / 2);
    //LEFT JOINT
    point04From = ofPoint(point02From.x - param04, point02From.y);
    point04ToP  = ofPoint(point02From.x - param04, point02ToN.y);
    point04ToN  = ofPoint(point02From.x - param04, point02ToP.y);
    //TRACK POSITION
    track01 = ofPoint(ofGetWidth() / 2, point01From.y + param07);
    track02 = ofPoint(ofGetWidth() / 2, point03From.y - (param08 + screwHeight));
    track01B = ofPoint(ofGetWidth() / 2, point01From.y + param07 + screwHeight);
    track02B = ofPoint(ofGetWidth() / 2, point03From.y - param08);
    
    //A4 paper guide
    for (int i = 2; i < 5; i++) if (param05 > A4Height * (i - 1) && param05 <= A4Height * i) pNum = i;
    
    //logs
    if (logAlpha > 0) logAlpha-=1;
}

//--------------------------------------------------------------
void ofApp::draw(){
    //length info
    lengthInfo(point01From, point03From, ofGetWidth() / 2 + 250);
    lengthInfo(point02From, point04From, 50);
    lengthInfo(point01From, track01, ofGetWidth() / 2 - 250);
    lengthInfo(track01B, track02, ofGetWidth() / 2 - 250);
    lengthInfo(track02B, point03From, ofGetWidth() / 2 - 250);
    
    // besier arm
    ofNoFill();
    ofSetColor(100);
    ofDrawLine(point01From, point01ToP);
    ofDrawLine(point02From, point02ToN);
    ofDrawLine(point02From, point02ToP);
    ofDrawLine(point03From, point03ToN);
    ofDrawLine(point03From, point03ToP);
    ofDrawLine(point04From, point04ToN);
    ofDrawLine(point04From, point04ToP);
    ofDrawLine(point01From, point01ToN);
    ofDrawCircle(point01ToP, circleSize);
    ofDrawCircle(point02ToN, circleSize);
    ofDrawCircle(point02ToP, circleSize);
    ofDrawCircle(point03ToN, circleSize);
    ofDrawCircle(point03ToP, circleSize);
    ofDrawCircle(point04ToN, circleSize);
    ofDrawCircle(point04ToP, circleSize);
    ofDrawCircle(point01ToN, circleSize);
    
    // capture output data
    if (capture) {
        fileName = ofToString(ofGetYear()) + "_" + ofToString(ofGetMonth()) + "_" + ofToString(ofGetDay()) + "_" + ofToString(ofGetHours()) + "_" + ofToString(ofGetMinutes()) + "_" + ofToString(ofGetSeconds()) + ".ai";
        output.beginEPS(fileName);
    }
    //bezier
    output.setColor(255, 0, 0);
    output.bezier(point01From.x, point01From.y, point01ToP.x, point01ToP.y,
                  point02ToN.x, point02ToN.y, point02From.x, point02From.y);
    output.bezier(point02From.x, point02From.y, point02ToP.x, point02ToP.y,
                  point03ToN.x, point03ToN.y, point03From.x, point03From.y);
    output.bezier(point03From.x, point03From.y, point03ToP.x, point03ToP.y,
                  point04ToN.x, point04ToN.y, point04From.x, point04From.y);
    output.bezier(point04From.x, point04From.y, point04ToP.x, point04ToP.y,
                  point01ToN.x, point01ToN.y, point01From.x, point01From.y);
    //track postion
    trackPos(track01);
    trackPos(track02);
    //A4 paper guide
    if (bA4) A4Paper(pNum);
    if (capture){
        capture = false;
        output.endEPS();
        logAlpha = 255;
    }
    
    //graphic event when saved
    ofFill();
    ofSetColor(255, 255, 0, logAlpha / 1.5);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    //logs
    ofSetColor(0, 122, 0, logAlpha);
    ofDrawBitmapString("Data has been saved as " + fileName, logView.x, logView.y);
}

void ofApp::exit()
{
    //xmlsettings
    settings.setValue("settings:ui1", param01);
    settings.setValue("settings:ui2", param02);
    settings.setValue("settings:ui3", param03);
    settings.setValue("settings:ui4", param04);
    settings.setValue("settings:ui5", param05);
    settings.setValue("settings:ui6", param06);
    settings.setValue("settings:ui7", param07);
    settings.setValue("settings:ui8", param08);
    settings.saveFile("settings.xml");
    
    //UI
    delete gui0;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

void ofApp::trackPos(ofPoint & tp){
    //TOP LEFT
    output.line(tp.x - screwWidth / 2 - screwLineSize / 2, tp.y,
                tp.x - screwWidth / 2 + screwLineSize / 2, tp.y);
    output.line(tp.x - screwWidth / 2, tp.y - screwLineSize / 2,
                tp.x - screwWidth / 2, tp.y + screwLineSize / 2);
    //TOP RIGHT
    output.line(tp.x + screwWidth / 2 - screwLineSize / 2, tp.y,
                tp.x + screwWidth / 2 + screwLineSize / 2, tp.y);
    output.line(tp.x + screwWidth / 2, tp.y - screwLineSize / 2,
                tp.x + screwWidth / 2, tp.y + screwLineSize / 2);
    //BOTTOM LEFT
    output.line(tp.x - screwWidth / 2 - screwLineSize / 2, tp.y + screwHeight,
                tp.x - screwWidth / 2 + screwLineSize / 2, tp.y + screwHeight);
    output.line(tp.x - screwWidth / 2, tp.y - screwLineSize / 2 + screwHeight,
                tp.x - screwWidth / 2, tp.y + screwLineSize / 2 + screwHeight);
    //BOTTOM RIGHT
    output.line(tp.x + screwWidth / 2 - screwLineSize / 2, tp.y + screwHeight,
                tp.x + screwWidth / 2 + screwLineSize / 2, tp.y + screwHeight);
    output.line(tp.x + screwWidth / 2, tp.y - screwLineSize / 2 + screwHeight,
                tp.x + screwWidth / 2, tp.y + screwLineSize / 2 + screwHeight);
}

void ofApp::lengthInfo(ofPoint &p1, ofPoint &p2, float d){
    ofSetColor(255, 0, 255, 122);
    ofPoint dPos1 = p1;
    ofPoint dPos2 = p2;
    p1.x == p2.x ? dPos1.x = d : dPos1.y = d;
    p1.x == p2.x ? dPos2.x = d : dPos2.y = d;
    ofDrawLine(dPos1.x, dPos1.y, dPos2.x, dPos2.y);
    ofDrawLine(p1.x, p1.y, dPos1.x, dPos1.y);
    ofDrawLine(p2.x, p2.y, dPos2.x, dPos2.y);
    ofDrawBitmapString(ofToString(ofDist(p1.x, p1.y, p2.x, p2.y)) + "mm", (dPos1.x + dPos2.x) / 2, (dPos1.y + dPos2.y) / 2);
}

void ofApp::A4Paper(int n){
    output.setColor(0, 0, 200);
    for (int p = 0; p < n; p++) output.rect(ofGetWidth() / 2 - A4Width / 2, ofGetHeight() / 2 - A4Height * (float(n) / 2 - p),A4Width, A4Height);
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
