//
//  ofxEncryption.h
//  finalProjectSketch
//
//  Created by William Karges on 5/20/15.
//  Aes Encryption class written by github user noyanc
//  Modified and commented by William Karges

#ifndef __finalProjectSketch__ofxEncryption__
#define __finalProjectSketch__ofxEncryption__

#include <iostream>
#include "ofxEncryption.h"
#include "ofMain.h"
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

class ofxEncryption {
public:
    ofxEncryption() ;
    ~ofxEncryption() ;
    
    void init(unsigned char *ik, unsigned char *iv) ;
    
    string encrypt(string plainText) ;
    string encrypt(string plainText, string key, string iv) ;
    unsigned char *encrypt(unsigned char* lainText, int length_plainText);
	unsigned char *encrypt(unsigned char* plainText,  int length_plainText, unsigned char* key, unsigned char* iv);
	int encrypt(unsigned char *plainText, int plainTextLength, unsigned char* key, unsigned char* iv, unsigned char* cryptText);
    
    string decrypt(string cryptText) ;
    string decrypt(string cryptText, string key, string iv) ;
    unsigned char *decrypt(unsigned char* cryptText,  int length_cryptText);
	unsigned char *decrypt(unsigned char* cryptText,  int length_plainText, unsigned char* key, unsigned char* iv);
	int decrypt(unsigned char* cryptText, int cryptTextLength, unsigned char* key, unsigned char *iv, unsigned char *plaintext);
    
private:
	unsigned char *k, *v;
	void clean();
	void handleErrors(void);

};



#endif /* defined(__finalProjectSketch__ofxEncryption__) */
