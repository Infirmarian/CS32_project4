#include "provided.h"
#include <string>
#include <vector>
#include <algorithm>
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
            if(isalpha(ciphertext[k]) || ciphertext[k] == '\''){
                s = s+decryptedWords[i][dec];
                dec++;
            }
            else
                s = s+ciphertext[k]; //only prints out non-letter, non-apostrophe characters from the cipher
        }
        sentences.push_back(s);
    }
    sort(sentences.begin(), sentences.end());
    return sentences;
}
vector<string> DecrypterImpl::recDecrypt(vector<string> currTranslation, vector<string> cipher){
    //check if all the words in currTranslation are complete (no question marks)
    bool doneTranslating = true;
    for(int i=0; i<currTranslation.size(); i++)
        if(countQuestions(currTranslation[i]) != 0){
            doneTranslating = false;
            break;
        }
    if(doneTranslating){ //no question marks in the text, indicating that a complete translation was done
        //check if all words are in the dictionary
        bool allWords = true;
        for(int i=0; i<currTranslation.size(); i++)
            if(!m_wordList.contains(currTranslation[i])){
                allWords = false;
                break;
            }
        if(allWords){
            string s="";
            for(vector<string>::iterator i=currTranslation.begin(); i!=currTranslation.end(); i++)
                s+= *i;
            currTranslation.clear();
            currTranslation.push_back(s);
            return currTranslation;
        }
        else
            return vector<string>(); //all words were translated, but there was non-english words in there
    }
    //get translation based on current cipher and translation
    Translator t;
    string enc;
    string ptext;
    for(int i=0; i<currTranslation.size(); i++){
        for(int k=0; k<currTranslation[i].length(); k++){
            if(currTranslation[i][k] != '?' && currTranslation[i][k] != '\''){
                ptext = ptext + currTranslation[i][k];
                enc = enc + cipher[i][k];
            }
            
        }
    }
    if(!t.pushMapping(enc, ptext)) //update the current mapping with the translation between currTranslation and cipher
        return vector<string>();
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
   // vector<string> toReturn;
    vector<string> temp;
    //return an empty vector if there are no candidates
    for(int i=0; i<candidates.size(); i++){
        if(!t.pushMapping(cipher[longestPos], candidates[i]))
            continue; //translation contradicted a previous translation
        //update all objects in cipher with the most recent translation
        for(int i=0; i<currTranslation.size(); i++){
            currTranslation[i] = t.getTranslation(cipher[i]);
        }
        vector<string> tmp =recDecrypt(currTranslation, cipher);
        
        if(!tmp.empty())
            temp.insert(temp.end(), tmp.begin(), tmp.end());
        t.popMapping();
    }
    candidates.clear();
    
    return temp;
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
