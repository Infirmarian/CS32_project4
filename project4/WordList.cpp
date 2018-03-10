#include "provided.h"
#include <string>
#include <vector>
#include <functional>
#include <set>
#include "MyHash.h"
#include <fstream>
using namespace std;

class WordListImpl
{
public:
    ~WordListImpl();
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    MyHash<string, int> m_dictionary;
    string lower(const string& s) const;
};

WordListImpl::~WordListImpl(){
    //TODO:??
}

bool WordListImpl::loadWordList(string filename)
{
    ifstream fileStream(filename);
    if(fileStream){
        if(m_dictionary.getNumItems() > 0)
            m_dictionary.reset(); //reset the dictionary to contain nothing
        string line;
        while( getline(fileStream, line)){
            bool add = true;
            for(int i=0; i<line.length(); i++){
                if(isalpha(line[i]) || line[i] == '\'')
                    continue;
                else{
                    add = false;
                    break; // exit the loop
                }
            }
            if(add) //adds the lowercase version of the string to the dictionary
                m_dictionary.associate(lower(line), 1); //TODO: should this associate a value?
            }
    return true;  // finished reading input
    }
    return false; //file was not able to be opened
}

bool WordListImpl::contains(string word) const
{
    return (m_dictionary.find(lower(word)) != nullptr);
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    return vector<string>();  // This compiles, but may not be correct
}
//this function creates a new lower-case string from an input string
string WordListImpl::lower(const string& s) const{
    string ret="";
    for(int i=0; i<s.length(); i++)
        ret  = ret + static_cast<char>(tolower(s[i]));
    return ret;
}


//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}
unsigned int hash(const unsigned int& ui){
    return std::hash<unsigned int>()(ui);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
   return m_impl->findCandidates(cipherWord, currTranslation);
}
