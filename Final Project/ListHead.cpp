//
//  ListHead.cpp
//  Final Project
//
//  Created by Siuperman on 6/18/14.
//  Copyright (c) 2014 Siuperman. All rights reserved.
//
//  Listhead encapsulates all operations of the program, for
//  main to execute. It also serves to protect the data.

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

