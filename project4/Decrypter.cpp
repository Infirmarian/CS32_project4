#include "provided.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class DecrypterImpl
{
public:
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
    WordList m_wordList;
    int countQuestions(const string& s) const;
    vector<string> recDecrypt(vector<string> currTranslation, vector<string> sentance);
    bool getTranslation(string& cipherText, string& sentance);
    string deTokenize(string& withTokens, string& withOutTokens);
};

bool DecrypterImpl::load(string filename)
{
    return m_wordList.loadWordList(filename);
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    //update translation
    Translator t;
    Tokenizer token(".,;!(){}-\"$%^&?0123456789 ");
    vector<string> words = token.tokenize(ciphertext);
    vector<string> translation;
    string toProcess ="";
    for(vector<string>::iterator i =words.begin(); i!= words.end(); i++){
        translation.push_back(t.getTranslation(*i));
    }
    vector<string> decryptedWords = recDecrypt(translation, words);
    vector<string> sentences;
    for(int i=0; i<decryptedWords.size(); i++){
        string s="";
        int dec = 0;
        for(int k=0; k<ciphertext.length(); k++){
            if(isalpha(ciphertext[k])){
                s = s+decryptedWords[i][dec];
                dec++;
            }
            else
                s = s+ciphertext[k];
        }
        sentences.push_back(s);
    }
    
    return sentences;
    
    
    string leastTranslated;
    int leastTCount=0;
    for(vector<string>::iterator i=words.begin(); i!= words.end(); i++){
        if(leastTCount < countQuestions(*i)){
            leastTCount = countQuestions(*i);
            leastTranslated = *i;
        }
    }
    if(leastTCount == 0) //no untranslated words in the sentance
        return words;
    
    vector<string> possibleTranslations = m_wordList.findCandidates(leastTranslated, t.getTranslation(leastTranslated));
    
    return words;  // This compiles, but may not be correct
}
vector<string> DecrypterImpl::recDecrypt(vector<string> currTranslation, vector<string> cipher){

    //check if all the words in currTranslation are complete (no question marks)
    bool doneTranslating = true;
    for(int i=0; i<currTranslation.size(); i++)
        if(countQuestions(currTranslation[i]) != 0)
            doneTranslating = false;
    
    if(doneTranslating){ //no question marks in the text, indicating that a complete translation was done
        //check if all words are in the dictionary
        bool allWords = true;
        for(int i=0; i<currTranslation.size(); i++)
            if(!m_wordList.contains(currTranslation[i])){
                allWords = false;
                break;
            }
        if(allWords)
        return currTranslation;
    }
    
    Translator t;
    string enc;
    string ptext;
    for(int i=0; i<currTranslation.size(); i++){
        for(int k=0; k<currTranslation[i].length(); k++){
            if(currTranslation[i][k] != '?'){
                ptext = ptext + currTranslation[i][k];
                enc = enc + cipher[i][k];
            }
            
        }
    }
    t.pushMapping(enc, ptext); //update the current mapping with the translation between currTranslation and cipher
   
    //find longest unknown word
    int longestPos=-1;
    int longestUnknownValue = -1;
    for(int i=0; i<currTranslation.size(); i++){
        if(longestUnknownValue < countQuestions(currTranslation[i])){
            longestUnknownValue = countQuestions(currTranslation[i]);
            longestPos = i;
        }
    }
    if(longestPos==-1)
        return vector<string>(); //error
    
    //list of all possible translations of longest possible word
    vector<string> candidates = m_wordList.findCandidates(cipher[longestPos], currTranslation[longestPos]);
    //vector to return. Contains "sentences"
    vector<string> toReturn;

    for(int i=0; i<candidates.size(); i++){
        if(!t.pushMapping(cipher[longestPos], candidates[i]))
            continue; //translation contradicted a previous translation
        //update all objects in cipher with the most recent translation
        for(int i=0; i<currTranslation.size(); i++){
            currTranslation[i] = t.getTranslation(cipher[i]);
        }
        vector<string> temp = recDecrypt(currTranslation, cipher);
        string r = "";
        for(int i=0; i<temp.size(); i++)
            r+=temp[i];
        r+="\n";
        if(!temp.empty())
        toReturn.push_back(r);
        
        t.popMapping();
    }
    
    return toReturn;
}

int DecrypterImpl::countQuestions(const string &s) const{
    int val=0;
    for(int i=0; i<s.length(); i++){
        if(s[i] == '?')
            val++;
    }
    return val;
}



//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
