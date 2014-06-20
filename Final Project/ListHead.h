//
//  ListHead.h
//  Final Project
//
//  Created by Siuperman on 6/18/14.
//  Copyright (c) 2014 Siuperman. All rights reserved.
//
//  Listhead encapsulates all operations of the program, for
//  main to execute. It also serves to protect the data.

#ifndef __Final_Project__ListHead__
#define __Final_Project__ListHead__

#include <iostream>
#include "App.h"
#include "BST.h"
#include "Hash.h"
#include "Heap.h"

//const int BUCKET_SIZE = 3;

class ListHead
{
private:
    
    int count;
    int arySize;
    int bucketSize = BUCKET_SIZE;
    
    Hash *pHash;
    BST *pTree;
    Heap *pHeap;
    
public:
    //Constructor
    ListHead();
    ListHead(int);

    ~ListHead();
    
    Hash* getHash();
    BST* getBST();
    Heap* getHeap();
    
    void destroyBST();
    void destroyHash();
    void destroyHeap();
    //Member Functions
    
    
};



#endif /* defined(__Final_Project__ListHead__) */
