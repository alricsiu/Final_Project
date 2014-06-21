//  Hash.h
//  Lab 5
//
//  This class is a Hash Table. Allows user to search the hash, 
//  get hash statistics, get print the detailed 
//  hash table, and print all items in the hash.
//
//  Created by Siuperman on 6/10/14.
//  Copyright (c) 2014 Siuperman. All rights reserved.
//

#include <iostream>

using namespace std;

#ifndef HW_4_BSTree_h
#define HW_4_BSTree_h
#include "App.h"
#include <vector>
#include "Bucket.h"

const int HASH_SIZE = 31;

class Hash
{
private:
    
    Bucket *hashList;
    
    int count; // total number of data points in hash.
    int count_occupiedBuckets;
   int tableSize;
   int collisions;
 
public:
    
   //Constructor
    Hash();
    Hash(int tableSize);
   // Destructor
   ~Hash();
    
   // Member functions

    void insert(App*);
    App* remove(int uniqueKey);
    void printHash();
    App* search(int uniqueKey);
    void displayHash();
    void showStats();
    int getCollisions();
    double getLoadFactor();
    int  getCount();
    int  getLongestBucketLength();
    int  getNumFullBuckets();
    int  hasher(int);
    
    int getTableSize();
    Bucket* getHashList();
    
    void reHash();
    void destroyHash();

    static int getNextPrime(int currentNumber);
    
};



#endif
