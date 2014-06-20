//
//  Bucket.cpp
//  Lab 5
//
//  Holds the number of apps defined by BUCKET_SIZE in the hash table.
//
//  Created by Siuperman on 6/10/14.
//  Copyright (c) 2014 Siuperman. All rights reserved.
//
#include <iostream>

using namespace std;

#ifndef HW_5_Bucket_h
#define HW_5_Bucket_h
#include "App.h"
#include <vector>

const int BUCKET_SIZE = 3;



class Bucket
{
private:
    App* locations[BUCKET_SIZE];
    int count;
    
public:
    //Constructor
    Bucket();
    // Destructor
    ~Bucket();
    
    int getCount();
    
    // Member functions

    App* searchBucket(int);
    int insert(App*);
    App* remove(int uniqueKey);
    void printBucket();
    void displayBucket();
    
    App* getLocation(int);
    void setBucket(int, App*);
    
    void destroyBucket();
    
    
};


#endif
