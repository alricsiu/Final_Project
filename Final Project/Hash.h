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
    //random primes.
    int primes [500] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
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
    bool rehash();//
    void printEVERYTHING();//
    bool _delete();//
    
    
private:
    void shift();
    
    
    
    
    
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
