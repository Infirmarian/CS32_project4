
#include "provided.h"
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const std::string& s) const;
private:
    unordered_set<char> m_delimiters;
};

TokenizerImpl::TokenizerImpl(string separators){
    for(int i=0; i<separators.length(); i++){
        m_delimiters.insert(separators[i]);
        //add each new delimiter as a char in an unordered (search time of O(1))
    }
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
    string tempWord = "";
    vector<string> tokens;
    for(int i=0; i<s.length(); i++){
        if(m_delimiters.find(s[i]) != m_delimiters.end()){ //the current character was a delimiter
            if(tempWord == "")
                continue;
            tokens.push_back(tempWord);
            tempWord = "";
        }else{
            tempWord = tempWord+s[i];
        }
    }
    if(tempWord != "")
        tokens.push_back(tempWord); //push temp word, (case when s doesn't end in a delimiter)
    return tokens;
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}
