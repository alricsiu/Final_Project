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
    pHeap = new Heap();
}

ListHead::ListHead(int fileLength)
{
    pHash = new Hash(Hash::getNextPrime(fileLength*2));
    pTree = new BST();
    pHeap = new Heap();

}

ListHead::~ListHead()
{
    delete pHash;
    delete pTree;
    delete pHeap;
}

Hash* ListHead::getHash()
{
    return pHash;
}

BST* ListHead::getBST()
{
    return pTree;
}

Heap* ListHead::getHeap()
{
    return pHeap;
}

void ListHead::destroyHash()
{
   pHash->destroyHash();
}
void ListHead::destroyBST()
{
    pTree->BST_destroy();
}
void ListHead::destroyHeap()
{
    delete pHeap;
}

