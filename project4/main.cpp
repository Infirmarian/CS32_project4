//
//  main.cpp
//  project4
//
//  Created by Robert Geil on 3/7/18.
//  Copyright © 2018 Robert Geil. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;
#include "MyHash.h"
#include "provided.h"


void f();
int main(int argc, const char * argv[]) {
    f();

    Decrypter d;
    Translator t;
    cout<<t.pushMapping("xydv", "abcd");
    cout<<t.pushMapping("xy", "ab");
    cout<<t.pushMapping("xy", "bd");
    cout<<t.pushMapping("bq", "ab");
    cout<<t.getTranslation("xydv")<<endl;
    d.load("/Users/geil/Desktop/C++/CS32/project4/project4/wordlist.txt");
    vector<string> words = d.crack("Axevfvu lvnelvp bxqp mvpprjv rgl bvoop Grnxvgkvuj dqupb jvbp buvrbvl be lqggvu");
    for(int i=0;i<words.size(); i++)
        cout<<words[i]<<endl;
    cout<<"Hello world!"<<endl;
    return 0;
}


void f()
{
    WordList wl;
    if ( ! wl.loadWordList("/Users/geil/Desktop/C++/CS32/project4/project4/wordlist.txt"))
    {
        cout << "Unable to load word list" << endl;
        return;
    }
    if (wl.contains("onomatopoeia"))
        cout << "I found onomatopoeia!" << endl;
    else
        cout << "Onomatopoeia is not in the word list!" << endl;
    string cipher = "xyqbbq";
    string decodedSoFar = "?R????";
    vector<string> v = wl.findCandidates(cipher, decodedSoFar);
    if (v.empty())
        cout << "No matches found" << endl;
    else
    {
        cout << "Found these matches:" << endl;
        for (size_t k = 0; k < v.size(); k++)
            cout << v[k] << endl; // writes grotto and troppo
    }
}




