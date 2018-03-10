//
//  MyHash.h
//  project4
//
//  Created by Robert Geil on 3/7/18.
//  Copyright © 2018 Robert Geil. All rights reserved.
//

#ifndef MyHash_h
#define MyHash_h
#include <string>
template <class KeyType, class ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor =0.5){
        m_maxLoad = maxLoadFactor <= 0 ? 0.5 : maxLoadFactor < 2 ? maxLoadFactor : 2.0;
        m_size = 100; //default size of 100 buckets
        m_nItems = 0; //the hash table is constructed empty
        m_table = new Node* [m_size];
        for(int i =0; i<m_size; i++){
            m_table[i] = nullptr; //reset all values of the hash table to nullptr
        }
    }
    ~MyHash(){
        deleteTable();
    }
    void reset(){
        deleteTable();
        m_size = 100;
        m_nItems = 0;
        m_table = new Node* [100]; //create new table of 100 elements
        for(int i=0; i<m_size; i++)
            m_table[i] = nullptr;
    }
    void associate(const KeyType& key, const ValueType& value){
        if(find(key)){
            //simply updating a key, not actually inserting a new value
            *find(key) = value;
            return;
        }
        m_nItems ++; // not just updating key, but adding a new item
        if(static_cast<double>(m_nItems)/m_size > m_maxLoad){
            Node** tempTable = new Node* [m_size * 2]; //new table
            for(int i=0; i<m_size*2; i++)
                tempTable[i] = nullptr; //set each item in new table to nullptr
            
            for(int i=0; i<m_size; i++){
                if(m_table[i] != nullptr){
                    Node* ptr = m_table[i];
                    while(ptr != nullptr){
                        Node* tempPtr = ptr->next;
                        int b = getBucket(key, m_size*2);
                        ptr->next = nullptr; //delete old link between the lists when moving a node over
                        insertToTable(b, ptr, tempTable); //insert into the new table
                        ptr = tempPtr;
                    }
                }
            }
            
            m_size *=2;
            delete [] m_table;
            m_table = tempTable;
        }
        unsigned int bucketToInsert = getBucket(key, m_size);
        Node* temp = new Node;
        temp->key = key;
        temp->val = value;
        temp->next = nullptr;
        //insert new value into calculated bucket
        insertNodeIntoBucket(bucketToInsert, temp);
    }
    ValueType* find(const KeyType& key) const{
        unsigned int bucketToSearch = getBucket(key, m_size);
        Node* ptr = m_table[bucketToSearch];
        while(ptr != nullptr){
            if(ptr->key == key){
                return &(ptr->val);
            }
            ptr = ptr->next;
        }
        return nullptr;
    }
    int getNumItems() const{
        return m_nItems;
    }
    double getLoadFactor() const{
        return (static_cast<double>(m_nItems)/m_size);
    }
private:
    struct Node{
        KeyType key;
        ValueType val;
        Node* next;
    };
    //given a table size and a key, the key is hashed
    unsigned int getBucket(const KeyType& key, int tableSize) const{
        unsigned int hash(const KeyType& k);  //prototype
        return hash(key)%tableSize;
        
    }
    //helper function to delete all items in a linked list
    //beginning at head
    void freeList(Node* head){
        if(head == nullptr)
            return;
        freeList(head->next);
        delete head;
    }
    //frees all allocated memory in a given table. This is called by the destructor
    void deleteTable(){
        //delete the list attached to each bucket
        for(int i=0; i<m_size; i++){
            freeList(m_table[i]);
        }
        //deletes the table
        delete [] m_table;
    }
    //insert node into given table
    void insertToTable(unsigned int b, Node* n, Node** table){
        if(table[b] == nullptr){
            table[b] = n;
        }else{
            Node* temp = table[b];
            while(temp->next != nullptr)
                temp = temp->next;
            temp->next = n;
        }
    }
    //given a bucket and a new node, this function inserts that node into the
    //respective bucket at the end of the linked list
    void insertNodeIntoBucket(unsigned int b, Node* n){
        insertToTable(b, n, m_table);
    }
    int m_nItems;
    int m_size;
    double m_maxLoad;
    Node** m_table; //pointer to the beginning of the table
};


#endif /* MyHash_h */
