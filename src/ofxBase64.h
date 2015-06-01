//
//  ofxBase64.h
//  finalProjectSketch
//
//  Created by William Karges on 5/20/15.
//  Simple Base64 Encoding implementing Poco libraries written by gitHub user jkosoy
//  Modified and code commented by William Karges

#ifndef __finalProjectSketch__ofxBase64__
#define __finalProjectSketch__ofxBase64__

#include <iostream>
#include "ofMain.h"
#include "Poco/MD5Engine.h"
#include "Poco/SHA1Engine.h"
#include "Poco/DigestStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Base64Decoder.h"
#include "Poco/Base64Encoder.h"
#include "Poco/Crypto/Crypto.h"

using Poco::DigestEngine;
using Poco::Base64Encoder;
using Poco::Base64Decoder;
using Poco::DigestOutputStream;
using Poco::StreamCopier;

class ofxBase64 {
public:
    static string base64Encode(string source);
    static string base64Decode(string source);
    
    static string base64Encode(ofBuffer &buffer);
    static ofBuffer base64DecodeToBuffer(string source);
};













#endif /* defined(__finalProjectSketch__ofxBase64__) */
