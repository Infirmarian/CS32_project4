//
//  main.cpp
//  project4
//
//  Created by Robert Geil on 3/7/18.
//  Copyright © 2018 Robert Geil. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
#include "MyHash 2.h"

int main(int argc, const char * argv[]) {
    // insert code here...
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
    return 0;
}
