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
    //Doubles current prime number for rehash
    int nextprime = currentprime*2;
    int count = 0;
    //increments doubled prime by one until it matches an included prime number
    while(nextprime != primes[count]){
        nextprime++;
    }
    return nextprime;
}

/*Data Hash::getEntry(int searchKey) const{
    int i = searchKey;
    return
}*/
bool Hash::search(int searchKey){
    for(int i = 0; i < tableSize; i++){
        for(int j = 0; j < bucketSize; j++){
            if(searchKey == hashTable[i].appArray[j].appId){
                return true;
            }
        }
    }
    return false;
}

int Hash::hasher(int newData)
{
    return newData % tableSize;
}

//***************************************************************************
// The insert member function takes in the searchKey/index and the newData  *
// struct. It then traverses the respective bucket until it finds and empty *
// location. While traversing each time it traverses is counted as a        *
// collision.                                                               *
//***************************************************************************

bool Hash::insert(int searchKey, Data newData)
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
    while(hashTable[searchKey].appArray[i].appId!=0)
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
    hashTable[searchKey].appArray[i].appId = newData.appId;
    hashTable[searchKey].appArray[i].appName = newData.appName;
    hashTable[searchKey].appArray[i].appPublisher = newData.appPublisher;
    hashTable[searchKey].appArray[i].category = newData.category;
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
            if(hashTable[i].appArray[j].appId){
            cout << "App Id: " << hashTable[i].appArray[j].appId << endl;
            cout << "\tName: " << hashTable[i].appArray[j].appName << endl;
            cout << "\tPublisher: " << hashTable[i].appArray[j].appPublisher << endl;
            cout << "\tCategory: " << hashTable[i].appArray[j].category << endl;
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
                cout << " App Id: " << hashTable[i].appArray[j].appId << endl;
                cout << "\t\t\tName: " << hashTable[i].appArray[j].appName << endl;
                cout << "\t\t\tPublisher: " << hashTable[i].appArray[j].appPublisher << endl;
                cout << "\t\t\tCategory: " << hashTable[i].appArray[j].category << endl;
                cout << "-----------------------" << endl;
            
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
// be reset to false. Then the data structure will be replicated (array of  *
// buckets) and each value from the original data structure will be rehash  *
// using the hasher function and being relocated to its respective place    *
// in the newly rehashed hashtable.                                         *
//***************************************************************************
void Hash::rehash(){
    // call rehash as member function of original hashtable
    tableSize = getNextPrime(tableSize*2);
    cout << "New TableSize:" << tableSize;
    bucketSize+=1;
    Hash *reHashTable = new Hash(tableSize);
    
    
    // LEFT OFF: REALIZED THAT I HAVE TO DYNAMICALLY ALLOCATE BUCKETNODE ARRAY
    // MUST THEREFORE CHANGE HOW TRAVERSALS OF IT ARE HANDLED IN INSERT FUNCTION
    // AND MAYBE OTHER MEMBER FUNCTIONS THAT I CANT THINK OF RIGHT NOW. 
    
    
    // increase table size and bucket size
    // call constructor
    // iterate through each element of current hashtable
    // run it through the hashtable and take each app
    // run the hasher function on it.
    // insert and transfer all fields
    
    
    
    //pass reference back to pointer in main
    //
    
}
//Constructor
Hash::Hash()
{
    hashTable = new bucketNode[tableSize];
    
}

Hash::Hash(int tableSize)
{
    hashTable = new bucketNode[tableSize];
}