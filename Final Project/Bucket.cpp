//
//  Bucket.cpp
//  Final Project
//
//  Holds the number of apps defined by BUCKET_SIZE in the hash table.
//
//  Created by Alric Siu on 6/10/14.
//  Copyright (c) 2014 Alric Siu. All rights reserved.
//

#include "Bucket.h"

//////////////////
// Constructor  //
//////////////////
/**
 * Initializes count to zero, also assigns NULL to each location. 
 */
Bucket::Bucket()
{
    count = 0;
    for(int i = 0; i<BUCKET_SIZE;i++)
    {
        locations[i] = NULL;
    }
}

////////////////
// Destructor //
////////////////
/**
 *  Frees memory of all the Apps in all buckets
 */
Bucket::~Bucket()
{
    destroyBucket();
}

///////////////////
// Search Bucket //
///////////////////
/**
 * Search the Bucket
 * @param  uniqueKey the unique key of an App
 * @return           the pointer to the app if found, else will be null
 */
App* Bucket::searchBucket(int uniqueKey)
{
 
        App *result = NULL;
        
        for(int i = 0; i<count; i++)
        {
                if(locations[i]->getUniqueKey() == uniqueKey)
                {
                    result = locations[i];
                    break;
                }
        }
        
        return result;
    
}
///////////////////
// Remove Item //
///////////////////
/**
 * Remove App item from the Bucket
 * @param  uniqueKey the unique key of an App to be removed
 * @return           the pointer to the app if removed, else will be null
 */
App* Bucket::remove(int uniqueKey)
{
    
    App *result = NULL;
    
    for(int i = 0; i<count; i++)
    {
        if(locations[i]->getUniqueKey() == uniqueKey)
        {
            result = locations[i];
            locations[i] = NULL;
            count--;

            if(i<count)
            {
                locations[i] = locations[count];
                locations[count] = NULL;
            }
            
            break;
        }
    }
    
    return result;
    
}

////////////
// Insert //
////////////
/**
 * Attempt to insert into the bucket.
 * @param  app The app to insert into the bucket.
 * @return     The status of insertion. If the bucket is full, return -1
 *                 if the bucket had a collision but insertion was successful
 *                 returns 1, if the bucket was empty (ie no collision ) 
 *                 returns 0.
 */
int Bucket::insert(App* app)
{

    // 1 = collision, 0 = no collision, -1 = failed to insert into bucket (bucket full)
    int status = -1;
    
    
    if(count<BUCKET_SIZE)
    {
        if(count==0)
            status = 0;
        else
            status = 1;
        locations[count] = app;
        count+=1;
    }
    
    return status;
}

////////////////////
// Display Bucket //
////////////////////
/*
 *  Helper to display the bucket. Lists the app unique key in order of location.
 */
void Bucket::displayBucket()
{
    for(int i = 0; i<BUCKET_SIZE;i++)
    {
        App* buffer = locations[i];
        if(buffer)
            cout<<"\t"<<buffer->getUniqueKey()<<endl;
    }
    
}

//////////////////
// Print Bucket //
//////////////////
/**
 *   A more detailed print of the locations in the bucket
 *  Will print each location and the unique key it contains.
 *   Will print empty if the location is empty
 **/
void Bucket::printBucket()
{
    for(int i = 0; i<BUCKET_SIZE;i++)
    {
        App* buffer = locations[i];
        if(buffer)
        {
            cout<<"\tLocation "<<i<<": "<<buffer->getUniqueKey()<<endl;
        }
        else
        {
            cout<<"\tLocation "<<i<<": Empty"<<endl;
        }
    }
    
}

/////////////
// Getters //
/////////////

/**
 * Gets the count of locations full in the bucket
 * @return The count of locations full.
 */
int Bucket::getCount()
{
    return count;
}

/**
 * Gets the location at a specific index.
 * @param  index The index of the bucket
 * @return        the App at the location as a pointer.
 */
App* Bucket::getLocation(int index)
{
    if(index>=0 && index<=BUCKET_SIZE-1)
    {
        return locations[index];
    }
    
    return NULL;
}



////////////////////
// Destroy Bucket //
////////////////////
/**
 * Destroys the bucket, removes all app and frees their memory.
 */
void Bucket::destroyBucket()
{
    for(int i = 0; i<BUCKET_SIZE;i++)
    {
        if(locations[i])
        {
            locations[i] = NULL;
//            delete locations[i];
//            App* temp = locations[i]; //clean up pointer
//            temp = NULL;
        }
    }
}
