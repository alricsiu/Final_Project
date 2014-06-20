//
//  ListHead.cpp
//  Final Project
//
//  Created by Siuperman on 6/18/14.
//  Copyright (c) 2014 Siuperman. All rights reserved.
//

#include "ListHead.h"
#include "Hash.h"
#include "BST.h"

ListHead::ListHead()
{
    pHash = new Hash();
    pTree = new BST();
}

ListHead::ListHead(int fileLength)
{
    pHash = new Hash(Hash::getNextPrime(fileLength*2));
    pTree = new BST();
}

Hash* ListHead::getHash()
{
    return pHash;
}

BST* ListHead::getBST()
{
    return pTree;
}