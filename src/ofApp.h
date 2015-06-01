#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxGui.h"
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "ofxEncryption.h"
#include "ofTrueTypeFontExt.h"
#include "ofxBase64.h"
#include "Poco/Crypto/Cipher.h"
#include "ofxWalkingFirstPersonCamera.h"
#include "MathUtils.h"


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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void setNormals(ofMesh &mesh);
    
    void mainGUI() ;
    void passGUI() ;
    void webInfoGUI() ;
    void colorGUI() ;
    
    void NSAInfoGUI() ;
    void Info1() ;
    void Info2() ;
    void Info3() ;
    
    ofxUISuperCanvas *gui1 ;
    ofxUISuperCanvas *gui2 ;
    ofxUISuperCanvas *gui3 ;
    ofxUISuperCanvas *gui4 ;
    ofxUISuperCanvas *gui4a ;
    ofxUISuperCanvas *gui4b ;
    
    ofxUISuperCanvas *guic ;
    
    void exit();
    void guiEvent(ofxUIEventArgs &e);
    
    ofxPanel GUI;
    ofxLabel dim ;
    
    void setKey(string myKey) ;
    string _key, _iv ;
    
    ofxEncryption aes ;
    string pText ;
    string encryptedText ;
    string encodedText ;
    string deCrypt ;
    string deCrypted ;
    ofTrueTypeFontExt fontSmall ;
    ofxBase64 b64 ;
    
    
    float red, green, blue, redf, greenf, bluef, rot, tran ;
    vector<string> dItems ;
    vector<string> d2Items ;
    ofBuffer nsa1, nsa2, nsa3, nsa4, nsa5, nsa6, xKey ;
    ofBuffer anon, pMan ;
    ofImage *tor, *https, *prism, *xkey, *lPass, *kPass, *dLane ;
    bool bDrawVisuals, bDrawGrid, rain, white, cust, en, de ;
    
    ofxFirstPersonCamera	camera;
    ofMesh textMesh;
    ofLight light;
    vector<string> wordList ;
    vector<ofVec3f> wordVerts ;
    ofVec3f position ;

};
















