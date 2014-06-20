
//
//  Hash.cpp
//  Hash
//
//  Created by Alexis Candelaria on 6/1/14.
//  Copyright (c) 2014 DreamDrivenApps. All rights reserved.
//

#include "Hash.h"

int Hash::getTableSize()
{
    return tableSize;
}

void Hash::setTableSize(int newTableSize)
{
    tableSize = newTableSize;
}

int Hash::getCollisionCount(){
    return collisionCount;
}

int Hash::getEntryCount()
{
    return entryCount;
}

void Hash::incrementEntryCount()
{
    ++entryCount;
}

int Hash::getNextPrime(int currentprime)
{
    
    // getNextPrime traverses the prime array until the array
    // element is greater than two times the current table size (also a prime)
    
    int dbl_currentprime = currentprime*2;
    int count = 0;
    
    
    while(dbl_currentprime > primes[count] && count < 100){
        count++;
    }
    return primes[count];
}

/*App Hash::getEntry(int searchKey) const{
 int i = searchKey;
 return
 }*/
bool Hash::search(int searchKey, App &foundElem){
    int i = hasher(searchKey);
    if (hashTable[i])
        for(int j = 0; j < bucketSize; j++){
            if (hashTable[i]->appArray[j])
                if(searchKey == hashTable[i]->appArray[j]->getUniqueKey()){
                    foundElem = *hashTable[i]->appArray[j];
                    return true;
                }
        }
    return false;
}

int Hash::hasher(int newApp)
{
    int index = 0;
    int digit1 = newApp / 100000000;
    int digit3 = newApp / 1000000 % 10;
    int digit8 = newApp / 10 % 10;
    int digit9 = newApp % 10;
    index += digit1 * 1000 + digit3 * 100 + digit8 * 10 + digit9;
    index %= tableSize;
    return index;
}

//***************************************************************************
// The insert member function takes in the searchKey/index and the newApp  *
// struct. It then traverses the respective bucket until it finds and empty *
// location. While traversing each time it traverses is counted as a        *
// collision.                                                               *
//***************************************************************************

bool Hash::insert(App * newApp)
{
    int i = 0;
    int searchKey = hasher(newApp->getUniqueKey());
    bool insertSuccess = false;
    if(empty) empty = false;

    if (hashTable[searchKey])
    {
        while (i < 3 && hashTable[searchKey]->appArray[i])
            i++;
        if(i >= 3){
            hashTable[searchKey]->full = true;
//            cout<< "Bucket " << searchKey << " is full." << endl;
            rehash();
        }
        else {
            hashTable[searchKey]->appArray[i] = newApp;
            collisionCount++;
            insertSuccess = true;
            hashTable[searchKey]->count++; //increments number of valid elements per bucket.
        }
    }
    else {
        // First data node inserted for that hashTable index.
        hashTable[searchKey] = new bucketNode;
        hashTable[searchKey]->count = 1;
        for (int j = 0; j < bucketSize; j++)
            hashTable[searchKey]->appArray[j] = nullptr;
        hashTable[searchKey]->appArray[0] = newApp;
        
        insertSuccess = true;
        entryCount++; // updates
    }
    
    // after successful insert, check need for rehash based on load factor
    if (insertSuccess) {
        dataCount++;
        if (getLoadFactor() > 75)
            rehash();
    }
    
    return insertSuccess;
}

//***************************************************************************
// The displayHash function displays all the entries of the hashtable       *
// It will traverse each and display each field and each unique appId       *
//***************************************************************************
void Hash::displayHash()
{
    cout << "Hash Contents:" << endl << "---------------" << endl;
    for(int i = 0; i < tableSize; i++){
        if (hashTable[i]) {
            for(int j = 0; j < bucketSize; j++){
                if (hashTable[i]->appArray[j])
                    if(hashTable[i]->appArray[j]->getUniqueKey()){
                        cout << "App Id: " << hashTable[i]->appArray[j]->getUniqueKey() << endl;
                        cout << "\tName: " << hashTable[i]->appArray[j]->getAppName() << endl;
                        cout << "\tPublisher: " << hashTable[i]->appArray[j]->getAuthor() << endl;
                        cout << "\tCategory: " << hashTable[i]->appArray[j]->getCategory() << endl;
                        cout << "-----------------------" << endl;
                    }
            }
        }
    }
}
//***************************************************************************
// The printHash function displays the entire hash even empty spaces with   *
// specified location.                                                      *
//***************************************************************************
void Hash::printHash()
{
    for(int i = 0; i < tableSize; i++){
        cout << "Bucket " << i << ":"<<endl;
        for(int j = 0; j < bucketSize; j++){
             cout << "\tLocation " << j << ": ";
            if (hashTable[i]) {
                if (hashTable[i]->appArray[j]) {
                    cout << hashTable[i]->appArray[j]->getUniqueKey() << endl;
//                    cout << "\t\t\tName: " << hashTable[i]->appArray[j]->getAppName() << endl;
//                    cout << "\t\t\tPublisher: " << hashTable[i]->appArray[j]->getAuthor() << endl;
//                    cout << "\t\t\tCategory: " << hashTable[i]->appArray[j]->getCategory();
                }
                else{
                    cout<<"Empty"<<endl;
                }

            }
            else
            {
                cout << "Empty" <<endl;
            }
        }
    }
    
}

//***************************************************************************
// ShowStats function shows the useful hashTable statistics such as         *
// collision frequency, load factor, and number of buckets full.             *
//***************************************************************************
void Hash::showStats()
{
    cout << "Hash Statistics:" <<endl;
    cout << "\tCollision Frequency: " << collisionCount << " of " << dataCount << " elements.\n";
    cout << "\tLoad Factor: " << getLoadFactor() << endl;
    cout << "\tBuckets Full: " << fullCount() << endl;
    cout << "\tTotal Entries: " << entryCount<<endl;
    cout << "\tTotal Buckets: " << tableSize<<endl;
    
}
//***************************************************************************
// fullCount is a function that will traverse the dynamically allocated     *
// hash table and return the count of how many full buckets there are.      *
//***************************************************************************
int Hash::fullCount(){
    int fullCount = 0;
    for(int i = 0; i < tableSize; i++){
        if(hashTable[i]){
            if (hashTable[i]->full)
                fullCount++;
        }
        
    }
    return fullCount;
}
//***************************************************************************
// Rehash is a function that will double the table size of the hash and     *
// increase the bucket array size by one. Table size will be double and then*
// incremented to the next prime number for most effective hashing using    *
// modulus operations. Next all of the bucketsize full boolean values will  *
// be reset to false. Then the App structure will be replicated (array of  *
// buckets) and each value from the original App structure will be rehash  *
// using the hasher function and being relocated to its respective place    *
// in the newly rehashed hashtable.                                         *
//***************************************************************************
bool Hash::rehash(){
    // call rehash as member function of original hashtable
    int former_tableSize = tableSize;
//    cout << "former tablesize: " << former_tableSize << endl;
    tableSize = getNextPrime(tableSize);
//    cout << "New TableSize: " << tableSize << endl; // increase table size
    
    Hash * reHashTable = new Hash(tableSize);
    // call constructor
    
    for (int i = 0; i < former_tableSize; i++)
        if (hashTable[i])
            for (int j = 0; j < bucketSize; j++)
                if (hashTable[i]->appArray[j])
                    if (!reHashTable->insert(hashTable[i]->appArray[j]))
                        return false; ///asdfasdfasdfasdfasd
    
    delete hashTable;
    hashTable = reHashTable->hashTable;
    
    
    return true;
}

//********************************************************************
// The deleteElem function tries to find the element with a specified*
// app ID in the hashTable by first hashing the ID to determine the *
// element in the hash table (if it exists). It returns true if the *
// app was found and successfully deleted, and false otherwise.     *
//********************************************************************
bool Hash::deleteElem(int appID)
{
    int key = hasher(appID);
    int i, j;
    if (!hashTable[key])
        return false;
    for (i = 0; i < bucketSize; i++) {
        if (hashTable[key]->appArray[i]->getUniqueKey() == appID) {
            delete hashTable[key]->appArray[i];
            if (i < bucketSize) {// index of 2 is end of array, so this tests whether current i has another element after it
                // shifting
                for (j = i + 1; j < bucketSize && hashTable[key]->appArray[j]; j++, i++) {
                    hashTable[key]->appArray[i] = hashTable[key]->appArray[j];
                    hashTable[key]->appArray[j] = nullptr;
                }
            }
            return true;
        }
    }
    return false;
}

//******************************************************************
// The shift function is designed to shift all entries in a bucket *
// after an element is deleted from the hashtable. It essentially  *
// fills the gaps and shifts everything.                           *
//******************************************************************
//void Hash::shift()
//{
//
//}


//Constructor
Hash::Hash()
{
    tableSize = 31;
    hashTable = new bucketNode * [tableSize];
    for (int i = 0; i < tableSize; i++)
        hashTable[i] = nullptr; // safety
    dataCount = 0;
}

Hash::Hash(int lineCount)
{
    hashTable = new bucketNode * [lineCount];
    this->tableSize = lineCount;
    for (int i = 0; i < tableSize; i++)
        this->hashTable[i] = nullptr; // safety
    dataCount = 0;
}