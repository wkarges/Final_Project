//
//  ofxEncryption.cpp
//  finalProjectSketch
//
//  Created by William Karges on 5/20/15.
//  Aes Encryption class written by github user noyanc
//  Modified and commented by William Karges

#include "ofxEncryption.h"

ofxEncryption::ofxEncryption() {
    unsigned char empty[] = {0} ;
    k = empty ;
    v = empty ;
}
ofxEncryption::~ofxEncryption() {
    
}


void ofxEncryption::init(unsigned char *ik, unsigned char *iv) {
    ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	OPENSSL_config(NULL);
	k = ik;
	v = iv;
}

void ofxEncryption::clean() {
    EVP_cleanup();
	CRYPTO_cleanup_all_ex_data();
	ERR_free_strings();
}

string ofxEncryption::encrypt(string plainText) {
    unsigned char empty[] = {0} ;
    unsigned char* cryptText = empty ;
    int length_cryptText = encrypt((unsigned char*)plainText.c_str(), (int)plainText.length(), k, v, cryptText);
	string str(reinterpret_cast<char*>(cryptText));
	clean();
	ofLogVerbose("ofxEncryption.cpp") << "encrypted";
	return str.substr(0, length_cryptText);
}

string ofxEncryption::encrypt(string plainText, string key, string iv) {
    unsigned char empty[] = {0} ;
    unsigned char* cryptText = empty ;
    int length_cryptText = encrypt((unsigned char*)plainText.c_str(), (int)plainText.length(), (unsigned char*)key.c_str(), (unsigned char*)iv.c_str(), cryptText);
	std::string str(reinterpret_cast<char*>(cryptText));
    clean() ;
    ofLogVerbose("ofxEncryption.cpp") << "encrypted";
	return str.substr(0, length_cryptText);
}

unsigned char* ofxEncryption::encrypt(unsigned char* plainText, int length_plainText) {
	unsigned char empty[] = { 0 };
	unsigned char* cryptText = empty;
	int lenciphertext = encrypt(plainText, length_plainText, k, v, cryptText);
	clean();
	ofLogVerbose("ofxEncryption.cpp") << "encrypted";
	return cryptText;
}

unsigned char* ofxEncryption::encrypt(unsigned char* plainText, int length_plainText, unsigned char* key, unsigned char* iv) {
	unsigned char empty[] = { 0 };
	unsigned char* cryptText = empty;
	int length_cipherText = encrypt(plainText, length_plainText, key, iv, cryptText);
	clean();
	ofLogVerbose("ofxEncryption.cpp") << "encrypted";
	return cryptText;
}


string ofxEncryption::decrypt(string cryptText) {
    unsigned char empty[] = { 0 };
	unsigned char* plainText = empty;
    int length_plainText = decrypt((unsigned char*)cryptText.c_str(), (int)cryptText.length(), k, v, plainText);
	std::string str(reinterpret_cast<char*>(plainText));
	clean();
    ofLogVerbose("ofxEncryption.cpp") << "decrypted";
	return str.substr(0, length_plainText);
}

string ofxEncryption::decrypt(string cryptText, string key, string iv) {
    unsigned char empty[] = { 0 };
	unsigned char* plainText = empty;
    int length_plainText = decrypt((unsigned char*)cryptText.c_str(), (int)cryptText.length(), (unsigned char*)key.c_str(), (unsigned char*)iv.c_str(), plainText);
	std::string str(reinterpret_cast<char*>(plainText));
	clean();
	ofLogVerbose("ofxEncryption.cpp") << "decrypted";
	return str.substr(0, length_plainText);
}

unsigned char* ofxEncryption::decrypt(unsigned char* cryptText, int length_cryptText) {
    unsigned char empty[] = { 0 };
	unsigned char* plainText = empty;
	int length_plainText = decrypt(cryptText, length_cryptText, k, v, plainText);
	clean();
	ofLogVerbose("ofxEncryption.cpp") << "decrypted";
	return plainText;
}

unsigned char* ofxEncryption::decrypt(unsigned char* cryptText, int length_cryptText, unsigned char* key, unsigned char* iv) {
    unsigned char empty[] = { 0 };
	unsigned char* plainText = empty;
    int length_plainText = decrypt(cryptText, length_cryptText, key, iv, plainText);
    clean() ;
    ofLogVerbose("ofxEncryption.cpp") << "decrypted" ;
}

int ofxEncryption::encrypt(unsigned char *plainText, int plainTextLength, unsigned char *key, unsigned char *iv, unsigned char *cryptText) {
    EVP_CIPHER_CTX *ctx;
    int length ;
    int cryptTextLength ;
    
    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
    
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) handleErrors();
    
    if(1 != EVP_EncryptUpdate(ctx, cryptText, &length, plainText, plainTextLength)) handleErrors();
    cryptTextLength = length;
    
    if(1 != EVP_EncryptFinal_ex(ctx, cryptText + length, &length)) handleErrors();
    cryptTextLength = length;
    
    EVP_CIPHER_CTX_free(ctx);
    
    return cryptTextLength;
}

int ofxEncryption::decrypt(unsigned char *cryptText, int cryptTextLength, unsigned char *key, unsigned char *iv, unsigned char *plainText) {
    EVP_CIPHER_CTX *ctx;
    int length ;
    int plainTextLength ;
    
    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
    
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_ofb(), NULL, key, iv)) handleErrors();
    
    if(1 != EVP_DecryptUpdate(ctx, plainText, &length, cryptText, cryptTextLength)) handleErrors();
    plainTextLength = length ;
    
    if(1 != EVP_DecryptFinal_ex(ctx, plainText + length, &length)) handleErrors();
    plainTextLength += length ;
    
    EVP_CIPHER_CTX_free(ctx);
    return plainTextLength;
    
}

void ofxEncryption::handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}













