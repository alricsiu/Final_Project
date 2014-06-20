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

////////////////
// Destructor //
////////////////
/**
 *  Free's memory for all the data structures.
 */
ListHead::~ListHead()
{
    delete pHash;
    delete pTree;
    delete pHeap;
}

/////////////
// Getters //
/////////////
/**
 * Get the hash.
 * @return The hash.
 */
Hash* ListHead::getHash()
{
    return pHash;
}

/**
 * Get the BST.
 * @return The BST.
 */
BST* ListHead::getBST()
{
    return pTree;
}

/**
 * Get the heap.
 * @return The heap.
 */
Heap* ListHead::getHeap()
{
    return pHeap;
}

/**
 * Destroys the Hash table and all its elements.
 */
void ListHead::destroyHash()
{
   pHash->destroyHash();
}
/**
 * Destroys the BST and all its elements.
 */
void ListHead::destroyBST()
{
    pTree->BST_destroy();
}
/**
 * Destroys the Heap and all its elements.
 */
void ListHead::destroyHeap()
{
    delete pHeap;
}

