//
//
//William Karges
//Advanced Coding Final Project Spring 2015
//
//
//

#include "ofApp.h"



void ofApp::setup(){
    
    //Set Cameras---------------------------------------
    camera.setNearClip(0.01f);
	camera.setPosition( 0, 20, 150 );
    camera.lookAt( ofVec3f( 0, 0, 0 ));
	camera.setMovementMaxSpeed( 1 );
    
    //Set Colors/Texts/Images---------------------------
    red = 233;
    blue = 240;
    green = 52;
    redf = 0.0 ;
    greenf = 0.0 ;
    bluef = 0.0 ;
    rot = 0.0 ;
    tran = 0.0 ;
    fontSmall.loadFont("Fonts/Lucida Sans Unicode.ttf", 8 );
    anon = ofBufferFromFile("Files/textDoc1.txt") ;
    nsa1 = ofBufferFromFile("NSA/NSA1.txt") ;
    nsa3 = ofBufferFromFile("NSA/NSA3.txt") ;
    xKey = ofBufferFromFile("NSA/xkey.txt") ;
    pMan = ofBufferFromFile("Files/passMan.txt") ;
    wordList.push_back("startingText") ;
    
    tor = new ofImage("Images/tor.png") ;
    https = new ofImage("Images/https.png") ;
    prism = new ofImage("Images/PRISM.png") ;
    xkey = new ofImage("Images/xkey.png") ;
    lPass = new ofImage("Images/LastPassLogo.png") ;
    kPass = new ofImage("Images/Keepass.png") ;
    dLane = new ofImage("Images/dashlane.png");
 
    //GUI functions-------------------------------------
    mainGUI() ;
    passGUI() ;
    webInfoGUI() ;
    NSAInfoGUI() ;
    colorGUI() ;
    Info1() ;
    Info2() ;
    
    
    gui1->loadSettings("settings1.xml") ;
    gui2->loadSettings("settings2.xml") ;
    gui3->loadSettings("settings3.xml") ;
    gui4->loadSettings("settings4.xml") ;
    gui4a->loadSettings("settings4a.xml") ;
    gui4b->loadSettings("settings4a.xml") ;
    
    guic->loadSettings("colorSettings.xml") ;
    
    
    //Encryption-----------------------------------------
    _iv = "KAkeepiitlFo1Mifiml3esOfevenGl08" ;
    unsigned char *key = (unsigned char*)_key.c_str() ;
    unsigned char *iv = (unsigned char*)_iv.c_str();
    aes.init(key, iv);
    
    
    light.enable();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    float time = ofGetElapsedTimef();
    ofBackground(red, green, blue) ; //Background Settings
    ofDrawBitmapString(encodedText, 50, ofGetHeight()-40) ; //Encoded Text Reference
    
    //Draw Grid
    ofEnableDepthTest();
    camera.begin() ;
    if(bDrawGrid == true) {
        ofPushMatrix() ;
        ofRotate(90, 0, 0, -1);
        ofDrawGridPlane( 50, 10, false);
        ofPopMatrix() ;
    }
    
    for(int i = 0; i < wordList.size(); i++) {
        ofMesh tMesh ;
        if(wordList[i] == "") {
            wordList[i] = "blank" ;
        }
        //Convert textInput to mesh and add it to tMesh
        tMesh = fontSmall.getStringMesh(wordList[i], ofRandom(-125, 75),ofRandom(-150, 150)) ;
        
        vector<ofVec3f> wVerts ;
        wVerts = tMesh.getVertices() ; //Get verticies of tMesh
        float move = time * -20 ;
        if(time > 30) {
            ofResetElapsedTimeCounter() ;
            cout << "reset" << endl ;
        }
        for(int j = 0; j < wVerts.size(); j++) {
//          tMesh.setVertex(j, wVerts[j].rotate(90, wVerts[j].x, wVerts[j].z)) ;
            wVerts[j].z = move ; //Move Z verticies for each textMesh
            //Change color of Verticies
            if(rain == true) {
                tMesh.addColor(ofFloatColor(ofRandom(0.0,1.0),ofRandom(0.0,1.0),ofRandom(0.0,1.0))) ;
            }
            else if(white == true) {
                tMesh.addColor(ofFloatColor(1.0,1.0,1.0)) ;
            }
            else if(cust == true) {
                tMesh.addColor(ofFloatColor(redf, greenf, bluef)) ;
            }
            else {
                tMesh.addColor(ofFloatColor(1.0,1.0,1.0)) ;
            }
            tMesh.setVertex(j, wVerts[j]) ; //Set verticies of tMesh at specified location

        }
        
        textMesh.append(tMesh) ;//add values of temporaryMesh to textMesh
        
        wordList.clear() ;//clear list of words
    }
    if(bDrawVisuals == true) {
        fontSmall.bind() ;
        ofPushMatrix() ;
        float move = time * 5 ;
        ofRotate(rot, 0.0, 1.0, 0.0) ; //rotate textMesh with GUI slider
        ofTranslate(0, 0, move) ; //Move the z coordinates of textMesh overTime
        ofTranslate(0,0, tran) ; //Translate textMesh z coordinates with GUI slider
        //    ofScale(1.0, -1.0, 1.0);
        textMesh.draw() ; //draw textMesh
        ofPopMatrix() ;
        fontSmall.unbind() ;
    }
    
    
    camera.end() ;
    ofDisableDepthTest() ;
    
}

//--------------------------------------------------------------
void ofApp::exit() {
    //save current settings of each gui upon exit
    gui1->saveSettings("settings1.xml");
    gui2->saveSettings("settings2.xml");
    gui3->saveSettings("settings3.xml");
    gui4->saveSettings("settings4.xml");
    gui4a->saveSettings("settings4a.xml");
    guic->saveSettings("colorSettings.xml") ;
    
    //delete each gui upon exit
    delete gui1;
    delete gui2;
    delete gui3;
    delete gui4;
    delete gui4a ;
    delete gui4b ;
    
    delete guic;
    
}

//unused function
void ofApp::setKey(string myKey) {
    _key =  myKey ;
    cout << "keylen: " << myKey.length() << endl ;
    _key = b64.base64Encode(_key) ;
    //    char *mykey = (char*)_key.data();
    //    _key = _key.copy(mykey, 16) ;
    cout << "keylen2: " << _key.length() << endl ;
    
}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e) {
    if(e.getName() == "Message") { //GUI for message text input
        ofxUITextInput *text1 = (ofxUITextInput *) e.widget ;
        pText = text1->getTextString() ;
        if(en == true) { //if encode toggle true, b64 encode text input
            encodedText = b64.base64Encode(pText) ;
            encryptedText = encryptedText + b64.base64Encode(pText) ;
            wordList.push_back(encodedText) ;
            cout << "text1: " << pText << " encoded: " << encodedText << endl ;
        }
        if(de == true) { //if decode toggle true, b64 decode text input
            deCrypt = b64.base64Decode(pText) ;
            deCrypted = deCrypt + " " + b64.base64Decode(deCrypted) ;
            if(deCrypt == "") {
                deCrypt = b64.base64Encode("blank") ;
            }
            wordList.push_back(deCrypt) ;
        }
        else { //if no cryption toggle true, add plain text to wordList
            wordList.push_back(pText) ;
        }
    }
    else if(e.getName() == "Encrypt") { //Encrypt Toggle
        ofxUIToggle *eToggle = (ofxUIToggle *) e.getToggle() ;
        en = eToggle->getValue() ;
    }
    else if(e.getName() == "Decrypt") { //Decrypt Toggle
        ofxUIToggle *dToggle = (ofxUIToggle *) e.getToggle() ;
        de = dToggle->getValue() ;
    }
    else if(e.getName() == "Visual Toggle") { //Text visuals toggle
        ofxUIToggle *vToggle = (ofxUIToggle *) e.getToggle() ;
        bDrawVisuals = vToggle->getValue() ;
    }
    else if(e.getName() == "Grid Toggle") { //draw grid toggle
        ofxUIToggle *gToggle = (ofxUIToggle *) e.getToggle() ;
        bDrawGrid = gToggle->getValue() ;
    }
    else if(e.getName() == "Rainbow") { //rainbow text toggle
        ofxUIToggle *rToggle = (ofxUIToggle *) e.getToggle() ;
        rain = rToggle->getValue() ;
    }
    else if(e.getName() == "White") { //white text toggle
        ofxUIToggle *wToggle = (ofxUIToggle *) e.getToggle() ;
        white = wToggle->getValue() ;
    }
    else if(e.getName() == "Custom") { //custom text color toggle
        ofxUIToggle *cToggle = (ofxUIToggle *) e.getToggle() ;
        cust = cToggle->getValue() ;
        if(cust == true) {
            guic->setVisible(true) ;
        }
        else if(cust == false) {
            guic->setVisible(false) ;
        }
    }
    else if(e.getName() == "DDL") { //Useful Information drop down list
        ofxUIDropDownList *ddList = (ofxUIDropDownList *) e.widget ;
        vector<ofxUIWidget *> &selected = ddList->getSelected();
        for(int i = 0; i < selected.size(); i++) {
            cout << "SELECTED: " << selected[i]->getName() << endl;
            if(selected[i]->getName() == "Password Protection") {
                gui2->setVisible(true) ;
                gui3->setVisible(false) ;
                gui4->setVisible(false) ;
                gui4a->setVisible(false) ;
                gui4b->setVisible(false) ;
            }
            else if(selected[i]->getName() == "Anonymous Browsing") {
                gui2->setVisible(false) ;
                gui3->setVisible(true) ;
                gui4->setVisible(false) ;
                gui4a->setVisible(false) ;
                gui4b->setVisible(false) ;
            }
            else if(selected[i]->getName() == "NSA Spying") {
                gui2->setVisible(false) ;
                gui3->setVisible(false) ;
                gui4->setVisible(true) ;
            }
            else if(selected[i]->getName() == "None") {
                gui2->setVisible(false) ;
                gui3->setVisible(false) ;
                gui4->setVisible(false) ;
                gui4a->setVisible(false) ;
                gui4b->setVisible(false) ;
            }
            else {
                gui2->setVisible(false) ;
                gui3->setVisible(false) ;
                gui4->setVisible(false) ;
            }
        }
    }
    else if(e.getName() == "spyList") { //NSA Spy Programs drop down list
        ofxUIDropDownList *ddList2 = (ofxUIDropDownList *) e.widget ;
        vector<ofxUIWidget *> &selected2 = ddList2->getSelected();
        for(int i = 0; i < selected2.size(); i++) {
            if(selected2[i]->getName() == "PRISM") {
                gui4a->setVisible(true) ;
                gui4b->setVisible(false) ;
            }
            if(selected2[i]->getName() == "X_Keyscore") {
                gui4a->setVisible(false) ;
                gui4b->setVisible(true) ;
            }
            else if(selected2[i]->getName() == "None") {
                gui4a->setVisible(false) ;
                gui4b->setVisible(false) ;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::mainGUI() { //Main GUI controls
    gui1 = new ofxUISuperCanvas("Online Safety");
    gui1->setTheme(OFX_UI_THEME_MACOSX) ;
    gui1->setDrawBack(true) ;
    gui1->addTextInput("Message", "Your Message", OFX_UI_FONT_SMALL) ; //Text Input GUI
    gui1->addToggle("Encrypt", true) ; //Encrypt Toggle
    gui1->addToggle("Decrypt", false) ; //Decrypt Toggle
    gui1->addSpacer() ;
    
    gui1->addLabel("Color Toggle") ; //Text color Toggles
    gui1->addToggle("Rainbow", true) ;
    gui1->addToggle("White", false) ;
    gui1->addToggle("Custom", false) ;
    gui1->addSpacer() ;
    
    gui1->addLabel("Visuals Toggle") ; //3D visuals Toggle
    gui1->setGlobalButtonDimension(64) ;
    gui1->addMultiImageToggle("Visual Toggle", "GUI/toggle.png", false) ;
    gui1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui1->addMultiImageToggle("Grid Toggle", "GUI/toggle.png", false) ;
    gui1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    gui1->addSpacer() ;
    
    gui1->addLabel("Text Rotation") ; //Mesh Rotation slider
    gui1->addRotarySlider("rotSlide", -100, 100, &rot);
    gui1->addSpacer() ;
    
    gui1->addLabel("Text Translation") ; //Mesh Translation slider
    gui1->addSlider("zSlide", -150, 100, &tran) ;
    gui1->addSpacer() ;
    
    gui1->addLabel("Useful Information"); //Useful Information Drop Down List
    dItems.push_back("Password Protection") ;
    dItems.push_back("Anonymous Browsing") ;
    dItems.push_back("NSA Spying") ;
    dItems.push_back("None") ;
    gui1->addDropDownList("DDL", dItems);
    
//    gui1->addTextArea("EncodedText", "encoded: " + encodedText) ;
    gui1->autoSizeToFitWidgets();
    
    ofAddListener(gui1->newGUIEvent, this, &ofApp::guiEvent);

    
}
//--------------------------------------------------------------
void ofApp::passGUI() {
    gui2 = new ofxUISuperCanvas("Password Managers", OFX_UI_FONT_LARGE) ; //Pasword Managers information GUI
    gui2->setTheme(OFX_UI_THEME_MACOSX) ;
    gui2->setDrawBack(true) ;
    gui2->addLabel("Wiki Description:", OFX_UI_FONT_MEDIUM) ;
    gui2->addTextArea("Password Info", pMan.getText(), OFX_UI_FONT_SMALL) ;
    gui2->addImage("lastPass", lPass) ;
    gui2->addImage("keePass", kPass) ;
    gui2->addImage("dashlane", dLane) ;
    gui2->autoSizeToFitWidgets();
    ofAddListener(gui2->newGUIEvent, this, &ofApp::guiEvent) ;
    gui2->setVisible(false) ;
}
//--------------------------------------------------------------
void ofApp::webInfoGUI() {
    gui3 = new ofxUISuperCanvas("Safe Web Browsing") ; //Anonymous web browsing Information GUI
    gui3->setTheme(OFX_UI_THEME_MACOSX) ;
    gui3->setDrawBack(true) ;
    gui3->addTextArea("WEBINFO1", anon.getText(), OFX_UI_FONT_SMALL) ;
    gui3->addImage("TorImage", tor) ;
    gui3->addImage("httpsImage", https) ;
    gui3->autoSizeToFitWidgets() ;
    ofAddListener(gui3->newGUIEvent, this, &ofApp::guiEvent) ;
    gui3->setVisible(false) ;
    
}
//--------------------------------------------------------------
void ofApp::NSAInfoGUI() {
    gui4 = new ofxUISuperCanvas("NSA Spying Program") ; //NSA Overview GUI
    gui4->setTheme(OFX_UI_THEME_MACOSX) ;
    gui4->setDrawBack(true) ;
    gui4->addTextArea("NSA Overview", nsa1.getText(), OFX_UI_FONT_SMALL) ;
    gui4->addSpacer() ;
    
    gui4->addLabel("Spying Programs") ;
    d2Items.push_back("PRISM") ;
    d2Items.push_back("X_Keyscore") ;
    d2Items.push_back("None") ;
    gui4->addDropDownList("spyList", d2Items) ;
    
    gui4->autoSizeToFitWidgets() ;
    ofAddListener(gui4->newGUIEvent, this, &ofApp::guiEvent) ;
    gui4->setVisible(false) ;
    
}
void ofApp::Info1() { //Prism information GUI
    gui4a = new ofxUISuperCanvas("PRISM Program") ;
    gui4a->setTheme(OFX_UI_THEME_MACOSX) ;
    gui4a->setDrawBack(true) ;
    gui4a->addTextArea("Prism", nsa3.getText(), OFX_UI_FONT_SMALL) ;
    gui4a->addImage("PrismImage", prism) ;
    gui4a->autoSizeToFitWidgets() ;
    ofAddListener(gui4a->newGUIEvent, this, &ofApp::guiEvent) ;
    gui4a->setVisible(false) ;
}
void ofApp::Info2() { //X_KeyScore information GUI
    gui4b = new ofxUISuperCanvas("X_KeyScore Program") ;
    gui4b->setTheme(OFX_UI_THEME_MACOSX) ;
    gui4b->setDrawBack(true) ;
    gui4b->addTextArea("xKeyscore", xKey.getText(),OFX_UI_FONT_SMALL) ;
    gui4b->addImage("xkeyImage", xkey) ;
    gui4b->autoSizeToFitWidgets() ;
    ofAddListener(gui4b->newGUIEvent, this, &ofApp::guiEvent) ;
    gui4b->setVisible(false) ;
}
//--------------------------------------------------------------
void ofApp::colorGUI() { //Custom Colors GUI
    guic = new ofxUISuperCanvas("Colors") ;
    guic->setTheme(OFX_UI_THEME_MACOSX) ;
    guic->setDrawBack(true) ;
    guic->addLabel("Background") ;
    guic->addSlider("RED", 0, 255, &red) ;
    guic->addSlider("GREEN", 0, 255, &green) ;
    guic->addSlider("BLUE", 0, 255, &blue) ;
    guic->addLabel("Text") ;
    guic->addSlider("R", 0.0, 1.0, &redf) ;
    guic->addSlider("G", 0.0, 1.0, &greenf) ;
    guic->addSlider("B", 0.0, 1.0, &bluef) ;
    guic->autoSizeToFitWidgets() ;
    ofAddListener(guic->newGUIEvent, this, &ofApp::guiEvent) ;
    guic->setVisible(false) ;

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '~':
            guic->toggleVisible();
            break;
        case OF_KEY_TAB:
            gui1->toggleVisible() ;
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
void ofApp::windowResized(int w, int h){
//    dim = ofToString(w) + "x" + ofToString(h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
////Universal function which sets normals for the triangle mesh
//void ofApp::setNormals( ofMesh &mesh ){
//    
//    //The number of the vertices
//    int nV = mesh.getNumVertices();
//    
//    //The number of the triangles
//    int nT = mesh.getNumIndices() / 3;
//    
//    vector<ofPoint> norm( nV ); //Array for the normals
//    
//    //Scan all the triangles. For each triangle add its
//    //normal to norm's vectors of triangle's vertices
//    for (int t=0; t<nT; t++) {
//        
//        //Get indices of the triangle t
//        int i1 = mesh.getIndex( 3 * t );
//        int i2 = mesh.getIndex( 3 * t + 1 );
//        int i3 = mesh.getIndex( 3 * t + 2 );
//        
//        //Get vertices of the triangle
//        const ofPoint &v1 = mesh.getVertex( i1 );
//        const ofPoint &v2 = mesh.getVertex( i2 );
//        const ofPoint &v3 = mesh.getVertex( i3 );
//        
//        //Compute the triangle's normal
//        ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
//        
//        //Accumulate it to norm array for i1, i2, i3
//        norm[ i1 ] += dir;
//        norm[ i2 ] += dir;
//        norm[ i3 ] += dir;
//    }
//    
//    //Normalize the normal's length
//    for (int i=0; i<nV; i++) {
//        norm[i].normalize();
//    }
//    
//    //Set the normals to mesh
//    mesh.clearNormals();
//    mesh.addNormals( norm );
//}
