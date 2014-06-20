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

#include "Hash.h"
#include <sstream>
#include <iostream>
#include <fstream>


/////////////////////////
// Default Constructor //
/////////////////////////

/**
 * The constructor initializes the count of the tree to zero.
 */
Hash::Hash()
{
    tableSize = HASH_SIZE;
    
    hashList = new Bucket[tableSize];

    overflow = new vector<App*>;
    count = 0;
    collisions = 0;
}

/////////////////
// Constructor //
/////////////////
/**
 *  Constructor that takes table size as a parameter.
 */
Hash::Hash(int tableSize)
{
    this->tableSize = tableSize;
    
    hashList = new Bucket[tableSize];
    
    overflow = new vector<App*>;
    count = 0;
}

////////////
// Insert //
////////////
/**
 * Insert App into the Hash
 * @param app The app to insert into the hash
 */
void Hash::insert(App* app)
{
    
    int hashedKey = app->getUniqueKey()%(tableSize-1);
    
    int status = hashList[hashedKey].insert(app);
    
    switch (status)
    {
        case -1:
            reHash();
            insert(app);
            break;
        case 0:
            count++;
            break;
        case 1:
            collisions++;
            count++;
            break;
        default:
           overflow->push_back(app);
            break;
    }
    
    if(getLoadFactor()>.75)
    {
        reHash();
    }
}

/////////////
// Delete  //
/////////////
/**
 * Searches the hash for the app with a specific unique key.
 * @param  uniqueKey The app unique key
 * @return           The pointer to the App if found, will return null
 *                       if app is not found.
 */
App* Hash::remove(int uniqueKey)
{
    App *result = NULL;
    int hashedKey = uniqueKey % (tableSize-1);
    result = hashList[hashedKey].remove(uniqueKey);
    if(result)
        count--;
    return result;
}



////////////////
// Print Hash //
////////////////
/**
 *     Detailed view of the hash. Shows the all buckets and the apps
 *     inside each bucket.
 */

void Hash::printHash()
{
    for(int i = 0; i<tableSize;i++)
    {
        cout<<"Bucket "<<i<<":"<<endl;
        hashList[i].printBucket();
    }
    
    cout<<"Overflow : [ ";
    if(overflow->size()>0)
    {
        for(int i = 0; i<overflow->size();i++)
        {
            cout<<overflow->at(i)->getUniqueKey();
            if(i!=overflow->size()-1)
                cout<<", ";
            else
                cout<<" ]";

        }
    }
    else
        cout<<"Empty";
    
    cout<<endl;
}

//////////////////
// Display Hash //
//////////////////
/**
 *     Displays all items in the hash. 
 */
void Hash::displayHash()
{
    cout<<"Hash Items "<<":"<<endl;

    for(int i = 0; i<tableSize;i++)
    {
        hashList[i].displayBucket();
    }
    
    if(overflow->size()>0)
    {
        for(int i = 0; i<overflow->size();i++)
        {
            cout<<"\t"<<overflow->at(i)->getUniqueKey()<<endl;
            
        }
    }
    
}


/////////////
// Search  //
/////////////
/**
 * Searches the hash for the app with a specific unique key.
 * @param  uniqueKey The app unique key
 * @return           The pointer to the App if found, will return null
 *                       if app is not found.
 */
App* Hash::search(int uniqueKey)
{
    App *result = NULL;
    int hashedKey = uniqueKey % (tableSize-1);
    result = hashList[hashedKey].searchBucket(uniqueKey);
    return result;
}


///////////
// Stats //
///////////
/**
 * Shows the Hash statistics, Load factor, collisions, count, tablesize
 */
void Hash::showStats()
{
    
    cout <<"\tLoad Factor: " << getLoadFactor() <<endl;
    int bucketsFull=0;
    for(int i = 0; i<tableSize;i++)
    {
        if(hashList[i].getCount() >= 3)
        {
            bucketsFull++;
        }
    }
    cout << "\tCollisions: "<< collisions<<endl;
    cout << "\tCount: "<< count<<endl;
    cout << "\tTableSize: "<< tableSize<<endl;

    // for Debugging to verify if the hash count is updated properly.
    /*
    int countreal = 0;
    for(int i = 0;i<tableSize;i++)
    {
        for(int j = 0; j<BUCKET_SIZE;j++)
        {
            App *currentApp = hashList[i].getLocation(j);
            if(currentApp)
                countreal++;
        }
    }  

    cout << "\tReal Count (Should match count): "<< count<<endl;
    */
   

}

/////////////
// Getters //
/////////////
/**
 * Gets the number of collisions that occured
 * @return the number of collisions.
 */
int Hash::getCollisions()
{
    return collisions;
}
/**
 * Calculates load factor, which is total elements / table size.
 * @return The load factor
 */
double Hash::getLoadFactor()
{
    return (double)count/tableSize;
}

////////////
// Rehash //
////////////
/**
 * Not required for HW 5. Rehashes the table.
 */
void Hash::reHash()
{
    
    Hash *rehashbuffer = new Hash(getNextPrime(tableSize*2)); //getnextprime
    
    for(int i = 0;i<tableSize;i++)
    {
        for(int j = 0; j<BUCKET_SIZE;j++)
        {
            App *currentApp = hashList[i].getLocation(j);
            if(currentApp)
                rehashbuffer->insert(currentApp);
            else
                break;
        }
    }
    
    this->tableSize = rehashbuffer->tableSize;
    this->hashList = rehashbuffer->hashList;
    this->count = rehashbuffer->count;
    this->collisions = rehashbuffer ->collisions;
    
}

//////////////////
// Destroy Hash //
//////////////////
/**
 *     Displays all items in the hash.
 */
void Hash::destroyHash()
{
    for(int i = 0; i<tableSize;i++)
    {
        hashList[i].destroyBucket();
    }
}


////////////////
// Destructor //
////////////////
/**
*
 */
Hash::~Hash()
{
    destroyHash();
    delete [] hashList;
}

////////////////////
// Get Next Prime //
////////////////////
/**
 * Helper method for Rehash. Gets the next prime number
 * @param  currentNumber The current number
 * @return               The next prime number.
 */
 int Hash::getNextPrime(int currentNumber)
{
    int primes [500] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
    
    //Doubles current prime number for rehash
    int nextPrime = currentNumber;
    int count = 0;
    //increments doubled prime by one until it matches an included prime number
    // Note original array of primes included could be remade to include first 1000 primes instead of just randomly selected ones
    while(primes[count] < nextPrime){
        count++;
    }
    nextPrime = primes[count];
    return nextPrime;
}
