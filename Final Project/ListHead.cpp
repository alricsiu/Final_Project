//
//  ListHead.cpp
//  Final Project
//
//  Listhead encapsulates all operations of the program, for
//  main to execute. It also serves to protect the data.
//
//  Created by Siuperman on 6/18/14.
//  Copyright (c) 2014 Siuperman. All rights reserved.
//

#include "ListHead.h"
#include "Hash.h"
#include "BST.h"

//////////////////
// Constructor  //
//////////////////
/**
 * The constructor dynamically allocates each primary data
 * structure that will be used to manipulate the data in this
 * program: the Hash Table, Binary Search Tree, and Heap.
 * Without taking the parameters, it constructs the Hash Table
 * with its default parameters.
 */
ListHead::ListHead()
{
    pHash = new Hash();
    pTree = new BST();
    pHeap = new Heap();
}

/////////////////
// Constructor //
/////////////////
/**
 * This constructor dynamically allocates each primary data
 * structure that will be used to manipulate the data in this
 * program: the Hash Table, Binary Search Tree, and Heap.
 * However, it takes a parameter that is used for constructing
 * the Hash Table.
 * @param fileLength The number of data elements in the input file,
 *                   determined by an initial file parse in main.
 */
ListHead::ListHead(int fileLength)
{
    pHash = new Hash(Hash::getNextPrime(fileLength*2));
    pTree = new BST();
    pHeap = new Heap(fileLength*2);

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

