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

//this function might be unnecessary because the rehashing
//is done as a member function.
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
    //Doubles current prime number for rehash
    
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
bool Hash::search(int searchKey){
    for(int i = 0; i < tableSize; i++){
        for(int j = 0; j < bucketSize; j++){
            if(searchKey == hashTable[i].appArray[j]->getUniqueKey()){
                return true;
            }
        }
    }
    return false;
}

int Hash::hasher(int newApp)
{
    return newApp % tableSize;
}

//***************************************************************************
// The insert member function takes in the searchKey/index and the newApp  *
// struct. It then traverses the respective bucket until it finds and empty *
// location. While traversing each time it traverses is counted as a        *
// collision.                                                               *
//***************************************************************************

bool Hash::insert(int searchKey, App * newApp)
{
    int i = 0;
    if(empty) empty = false;
    //While there is a positively defined value for appId
    // continue iterating through the bucket until you find
    // an empty location
    
    // check load factor each time
    // if over 75 then rehash
    entryCount++; // updates
    hashTable[searchKey].count++; //updates bucket count
    while(hashTable[searchKey].appArray[i])
    {
        collisionCount++;
        cout << "Collision Count incremented: " << collisionCount<< endl;
        i++;
    }
    if(i>2){
        hashTable[searchKey].full = true;
        cout<< "Bucket " << searchKey << " is full." << endl;
        return false;
        
    }
    hashTable[searchKey].appArray[i] = newApp;
    return true;
}

//***************************************************************************
// The displayHash function displays all the entries of the hashtable       *
// It will traverse each and display each field and each unique appId       *
//***************************************************************************
void Hash::displayHash()
{
    cout << "Hash Contents:" << endl << "---------------" << endl;
    for(int i = 0; i < tableSize; i++){
        for(int j = 0; j < bucketSize; j++){
            if(hashTable[i].appArray[j]->getUniqueKey()){
                cout << "App Id: " << hashTable[i].appArray[j]->getUniqueKey() << endl;
                cout << "\tName: " << hashTable[i].appArray[j]->getAppName() << endl;
                cout << "\tPublisher: " << hashTable[i].appArray[j]->getAuthor() << endl;
                cout << "\tCategory: " << hashTable[i].appArray[j]->getCategory() << endl;
                cout << "-----------------------" << endl;
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
    cout << "Hash Contents:" << endl << "---------------" << endl;
    for(int i = 0; i < tableSize; i++){
        cout << "Bucket " << i << ": ";
        for(int j = 0; j < bucketSize; j++){
            if(j){cout << "\t\tLocation " << j << ":";}
            else cout << "Location " << j << ":";
            if (hashTable[i].appArray[j]) {
                cout << " App Id: " << hashTable[i].appArray[j]->getUniqueKey() << endl;
                cout << "\t\t\tName: " << hashTable[i].appArray[j]->getAppName() << endl;
                cout << "\t\t\tPublisher: " << hashTable[i].appArray[j]->getAuthor() << endl;
                cout << "\t\t\tCategory: " << hashTable[i].appArray[j]->getCategory();
            }
            cout << "\n-----------------------\n";
            
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
    cout << "----------------" << endl;
    cout << "Collision Frequency: " << collisionCount << endl;
    cout << "Load Factor: " << (double)entryCount/(double)tableSize << endl;
    cout << "Buckets Full: " << fullCount() << endl << endl;
    
}
//***************************************************************************
// fullCount is a function that will traverse the dynamically allocated     *
// hash table and return the count of how many full buckets there are.      *
//***************************************************************************
int Hash::fullCount(){
    int fullCount = 0;
    for(int i = 0; i < tableSize; i++){
        if(hashTable[i].full){
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
void Hash::rehash(){
    // call rehash as member function of original hashtable
    int former_tableSize = tableSize;
    cout << "former tablesize: " << former_tableSize << endl;
    tableSize = getNextPrime(tableSize);
    cout << "New TableSize:" << tableSize; // increase table size
    
    // LEFT OFF: REALIZED THAT I HAVE TO DYNAMICALLY ALLOCATE BUCKETNODE ARRAY
    // MUST THEREFORE CHANGE HOW TRAVERSALS OF IT ARE HANDLED IN INSERT FUNCTION
    // AND MAYBE OTHER MEMBER FUNCTIONS THAT I CANT THINK OF RIGHT NOW.
    
    Hash * reHashTable = new Hash(tableSize);
    // call constructor
    
    for (int i = 0; i < former_tableSize; i++)
        for (int j = 0; j < bucketSize; j++)
            if (hashTable[i].appArray[j])
                reHashTable->insert(hasher(hashTable[i].appArray[j]->getUniqueKey()),
                                    hashTable[i].appArray[j]);
    //does rehashing with tableSize already set to new value.
    
    // iterate through each element of current hashtable
    // run it through the hashtable and take each app
    // run the hasher function on it.
    // insert and transfer all fields
    
    delete hashTable;
    
    hashTable = reHashTable->_getHashTable();
    
    //pass reference back to pointer in main
    //
    
}
//Constructor
Hash::Hash()
{
    hashTable = new bucketNode [tableSize];
    
}

Hash::Hash(int tableSize)
{
    hashTable = new bucketNode[tableSize];
}