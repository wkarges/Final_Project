/*
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

//
//  ofxBase64.cpp
//  finalProjectSketch
//
//  Created by William Karges on 5/20/15.
//  Simple Base64 Encoding implementing Poco libraries written by gitHub user jkosoy
//  Modified and code commented by William Karges

#include "ofxBase64.h"


string ofxBase64::base64Encode(string source) {
    ostringstream ostr;
    Base64Encoder encoder(ostr);
    encoder << source;
    encoder.close();
    return ostr.str();
}

string ofxBase64::base64Decode(string source) {
    ostringstream ostr;
    istringstream istr(source);
    Base64Decoder decoder(istr);
    StreamCopier::copyStream(decoder, ostr);
    return ostr.str();
}

string ofxBase64::base64Encode(ofBuffer &buffer) {
    long max = buffer.size() ;
    char *buf = buffer.getBinaryBuffer() ;
    string str = string(buf,max);
    return base64Encode(str);
}

ofBuffer ofxBase64::base64DecodeToBuffer(string source) {
    stringstream strs;
    strs << source ;
    Poco::Base64Decoder decoder(strs);
    ofBuffer buffer;
	decoder >> buffer;
    return buffer ;
}

