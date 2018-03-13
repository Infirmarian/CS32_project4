#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class TranslatorImpl
{
public:
    TranslatorImpl();
    ~TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    struct map{
        //each character maps from plain to encrypted (
                                // cipher->plainText
        string encryptToPlain;  // A->C, B->A represented as CA???...
        string plainToEncrypt;  // A->C, B->A represented as B?A??...
    };
    char translateOneChar(const char& c) const;
    vector<map> m_mappingStack;
};
TranslatorImpl::TranslatorImpl(){
    map m;
    string init;
    for(int i=0; i<26; i++){
        init +='?';
    }
    m.encryptToPlain = init;
    m.plainToEncrypt=init;
    m_mappingStack.push_back(m);
    
}
TranslatorImpl::~TranslatorImpl(){
    m_mappingStack.clear();
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    if(ciphertext.length() != plaintext.length())
        return false; //mappings were a different length
    map m;
    m.plainToEncrypt = m_mappingStack[m_mappingStack.size()-1].plainToEncrypt;
    m.encryptToPlain = m_mappingStack[m_mappingStack.size()-1].encryptToPlain;
    for(int i=0; i<plaintext.length(); i++){
        if(!isalpha(ciphertext[i]) || !isalpha(plaintext[i]))
            return false; //one of the two contained non-numeric characters
       if(m.encryptToPlain[toupper(ciphertext[i]) -'A'] != toupper(plaintext[i]) && m.encryptToPlain[toupper(ciphertext[i]) -'A'] != '?')
           return false;
        if(m.plainToEncrypt[toupper(plaintext[i])-'A'] != toupper(ciphertext[i]) && m.plainToEncrypt[toupper(plaintext[i])-'A'] != '?')
            return false;
        m.encryptToPlain[toupper(ciphertext[i])-'A'] = toupper(plaintext[i]);
        m.plainToEncrypt[toupper(plaintext[i])-'A'] = toupper(ciphertext[i]);
    }
    m_mappingStack.push_back(m);
    return true;  // This compiles, but is totally correct! Heck yeah!
}

bool TranslatorImpl::popMapping()
{
    if(m_mappingStack.size() > 1){ //don't pop the bottom mapping (eg all ?s)
        m_mappingStack.pop_back();
        return true;
    }
    return false;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    string ret ="";
    for(int i=0; i<ciphertext.length(); i++){
        if(!isalpha(ciphertext[i])){
            ret = ret + ciphertext[i];
            continue;
        }
        bool lowercase =islower(ciphertext[i]);
        char toAdd = translateOneChar(ciphertext[i]);
        ret = ret + (lowercase ? static_cast<char>(tolower(toAdd)) : toAdd);
        
    }
    return ret;
}

char TranslatorImpl::translateOneChar(const char& c) const{
    for(int i=0; i<26; i++){
        if((m_mappingStack[m_mappingStack.size()-1]).plainToEncrypt[i] == toupper(c)){
            return 'A' + i;
        }
    }
    return '?';
}


//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
