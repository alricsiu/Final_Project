//
//  Hash.h
//  Hash
//
//  Created by Alexis Candelaria on 6/1/14.
//  Copyright (c) 2014 DreamDrivenApps. All rights reserved.
//

#ifndef __Hash__Hash__
#define __Hash__Hash__

#include <iostream>
#include <string>
#include "App.h"
using namespace std;

/*struct Data {
    int appId;
    string appName;
    string appPublisher;
    string category;
    
};*/

const int bucketSize = 3;

class Hash{
    struct bucketNode {
        bool full = false;
        int count;
        App * appArray[bucketSize];
    };
private:
    int tableSize;
    bucketNode ** hashTable;
    int collisionCount;
    int entryCount; // keeps track of entry count
    bool empty;
    //random primes. consider including all first 1000 primes.
    int primes [100] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,
        83,89, 97, 101, 103,107,109,113,127,131,137,139,149,151,157,163,199,263, 317,383,443,503,577,641,701,769,839
        ,911,983,1049,1109,1193,1277,1321,1429,1487,1559,1619,1783,1871,1949,2017,2089,2161,
        2267,2339,2393,2579,2713,3541,4111,5051,6011,7159,7919};
    //make array dynamically allocate hashtable pointer dynamically allocate in constructor
    // bucketNode *hashTable = new bucketNode[31];
    bucketNode ** _getHashTable()
    { return hashTable; }
    
public:
    Hash(); // constructor destructor
    Hash(int tableSize); // overloaded constructor
    int getTableSize();//
    void setTableSize(int newTableSize);//
    int getCollisionCount();//
    int getEntryCount();//
    void incrementEntryCount();//
    int getNextPrime(int currentprime);//
    App getEntry(int searchKey) const;//search key index
    bool insert(App * newApp); //inserts newApp into hashTable
    bool remove(int searchKey);
    bool isEmpty();
    bool search(int searchKey);//
    void displayHash();//
    void printHash();//
    void showStats();//
    int fullCount();//
    int hasher(int newApp);//
    bool rehash(Hash *);//
    void printEVERYTHING();
    
    
    
    
    
    
    //~Hash();
    
};

#endif /* defined(__Hash__Hash__) */
//brain storm for hash features/subfunctions
/*
 
 insert
 delete
 find
 hashFunction
 isEmpty
 tableSize
 
 count
 constructor destructor
 
 
 
 
 */
