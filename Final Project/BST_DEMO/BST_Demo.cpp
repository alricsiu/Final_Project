/**
 Project: BUILD A BINARY SEARCH TREE

 The main goal of this example is build a binary search tree that could be used to
 test the traversal functions and other binary search tree functions

 NAME:
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include "BST.h"

using namespace std;

void build_BST( BST &tree, int n );

int main( void )
{
   BST tree;
   int n = 10; // number of nodes
   int searchCount = n;
   int r;
   Data data;

   srand(time(NULL));
   build_BST(tree, n );
   // Test BST Traversals
   tree.BST_InorderTraverse();
   cout << endl << endl;

   // Test BST Search
   while (searchCount--)
   {
       if (tree.Search(r = rand() % 100, data))
       {
           cout << r << " FOUND! Data contains: "
                << data.num << endl;
       }
       else
           cout << r << " NOT FOUND!\n";
   }

   return 0;
}

/**~*~*
   Builds a random Binary Search Tree of integer numbers within the range
   [0, 99]
*/
void build_BST( BST &tree, int n )
{
    Data data;

    while(n--)
    {
        data.num = rand( ) % 100;
        tree.BST_insert(data);
   }
}
