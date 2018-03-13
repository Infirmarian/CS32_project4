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
using namespace std;
#include "MyHash.h"
#include "provided.h"


void f();
int main(int argc, const char * argv[]) {
    //f();
    
    
    
    string list[] = {
        "havoc",
        "hawthorn",
        "hawthorne",
        "hawthorns",
        "hay",
        "haycock",
        "haycocks",
        "haYdn",
        "hayer",
        "hayers",
        "hayes",
        "HayfieldS",
        "hayfork",
        "hayforks",
        "haying",
        "hayings",
        "hayloft",
        "haylofts",
        "haymaker",
        "haymakers",
        "haymow",
        "haymows",
        "hayrack",
        "hayracks",
        "hayrick",
        "hayricks",
        "HAYRIDE"
    };
    Decrypter d;
    d.load("/Users/geil/Desktop/C++/CS32/project4/project4/wordlist.txt");
    vector<string> words = d.crack("Trcy oyc koon oz rweelycbb vmobcb, wyogrcn oecyb; hjg ozgcy tc moox bo moya wg grc vmobck koon grwg tc ko yog bcc grc oyc trlvr rwb hccy oecyck zon jb. -Rcmcy Xcmmcn");
    for(int i=0;i<words.size(); i++)
        cout<<words[i]<<endl;
    /*
    
  string myList[]= {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    cout << "Hello, World!\n";
    MyHash<int, char> htable(0);
    cout<<htable.getNumItems()<<endl;
    cout<<htable.getLoadFactor()<<endl;
    htable.associate(1, 5);
    htable.associate(1, 33);
    cout<<htable.getNumItems()<<endl;
    cout<<htable.getLoadFactor()<<endl;
    
    if(char* t = htable.find(1))
        cout<<"The value is "<<*t<<endl;
    //htable.associate(1, 77);
    if(char* t = htable.find(1))
        cout<<"The value is "<<*t<<endl;
    cout<<htable.getNumItems()<<endl;
    for(int i=0; i<10000; i++){
       // cout<<htable.getNumItems()<<" items in the table with a load of " <<htable.getLoadFactor()<<endl;
        htable.associate(i, 'a');
    }
     */
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




