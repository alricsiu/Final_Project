//
//  ListHead.h
//  Final Project
//
//  Created by Siuperman on 6/18/14.
//  Copyright (c) 2014 Siuperman. All rights reserved.
//

#ifndef __Final_Project__ListHead__
#define __Final_Project__ListHead__

#include <iostream>
#include "App.h"
#include "BST.h"
#include "Hash.h"

const int BUCKET_SIZE = 3;

class ListHead
{
private:
    
    int count;
    int arySize;
    int bucketSize = BUCKET_SIZE;
    
    Hash *pHash;
    BST *pTree;
    
public:
    //Constructor
    ListHead();
    ~ListHead();
    
    Hash getHash();
    BST getBST();
    //Member Functions
    
    
};



#endif /* defined(__Final_Project__ListHead__) */
