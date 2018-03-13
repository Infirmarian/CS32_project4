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
        string plainText;
        string encText;
    };
    char translateOneChar(const char& c) const;
    vector<map> m_mappingStack;
    string emptyString = "??????????????????????????"; //sloppy
};
TranslatorImpl::TranslatorImpl(){
    map m;
    m.encText = emptyString;
    m.plainText = emptyString;
    m_mappingStack.push_back(m);
    
}
TranslatorImpl::~TranslatorImpl(){
    m_mappingStack.clear();
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    if(ciphertext.length() != plaintext.length())
        return false; //mappings were a different length
    map m = m_mappingStack[m_mappingStack.size()-1]; //map equals current most recent translation
    
    for(int i=0; i<plaintext.length(); i++){
        if(m.plainText[toupper(plaintext[i]) - 'A'] != '?' && m.plainText[toupper(plaintext[i])-'A'] != toupper(ciphertext[i])) //if current cipher contradicts a letter, the pushed mapping is rejected
            return false;
        if(!isalpha(ciphertext[i]) || !isalpha(plaintext[i]))
            return false; //one of the two contained non-numeric characters
        
        
        m.plainText[toupper(plaintext[i]) -'A'] = toupper(ciphertext[i]);
        m.encText[toupper(ciphertext[i]) -'A'] = toupper(plaintext[i]);
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
    int l =m_mappingStack[m_mappingStack.size()-1].plainText.length();
    for(int i=0; i<l; i++){
        if((m_mappingStack[m_mappingStack.size()-1]).plainText[i] == toupper(c)){
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
