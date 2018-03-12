#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class TranslatorImpl
{
public:
    TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    char translateOneChar(const char& c) const;
    vector<string> m_mappingStack;
    string m_emptyMap = "??????????????????????????"; //sloppy
};
TranslatorImpl::TranslatorImpl(){
    m_mappingStack.push_back(m_emptyMap);
    
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    string map = m_mappingStack[m_mappingStack.size()-1]; //map equals current most recent translation
    for(int i=0; i<plaintext.length(); i++){
        if(map[toupper(plaintext[i]) - 'A'] != '?' && map[toupper(plaintext[i])] != toupper(ciphertext[i])) //if current cipher contradicts a letter, the pushed mapping is rejected
            return false;
        map[toupper(plaintext[i]) -'A'] = toupper(ciphertext[i]);
    }
    m_mappingStack.push_back(map);
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
    return ret;//m_mappingStack[m_mappingStack.size()-1];
}

char TranslatorImpl::translateOneChar(const char& c) const{
    int l =m_mappingStack[m_mappingStack.size()-1].length();
    for(int i=0; i<l; i++){
        if((m_mappingStack[m_mappingStack.size()-1])[i] == toupper(c)){
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
