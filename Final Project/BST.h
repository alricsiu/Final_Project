
//  Created by Fangyuan Xing on 5/26/14.
//  Copyright (c) 2014 Emily. All rights reserved.
//  BST.h

#ifndef __TeamProject__BST__
#define __TeamProject__BST__

#include <iostream>
#include <string>
using namespace std;

struct Data
{
    int ID;
    string name;
    string author;
    string category;
};

class BST
{
    struct BST_Node
    {
        Data* data;
        BST_Node* left;
        BST_Node* right;
        BST_Node* parent;
        BST_Node() : data(new Data), left(NULL), right(NULL), parent(NULL) {}
        ~BST_Node() {delete data;}
    };
    
    BST_Node* root;
    int count;
    
public:
    //***************************************************************************
    //   constructor
    //
    //***************************************************************************
    BST();
    
    //***************************************************************************
    //  destructor calls private funtion _destory to delete the whole tree
    //
    //***************************************************************************
    ~BST();
    
    //***************************************************************************
    //  This funtion gets the count
    //  returns count
    //***************************************************************************
    int getCount()
    {
        return count;
    }
    
    //***************************************************************************
    //  This function calls the private function _insert to insert data
    //
    //***************************************************************************
    void BST_insert(Data* data);
    
    //***************************************************************************
    //  This function calls the private function _insert to add data
    //
    //***************************************************************************
    void BST_add(Data* data);
    
    //***************************************************************************
    //  This function deletes a node by calling the private function _search to
    //  search target first, and if found, calls private function _delete, print
    //  error message if not found and return
    //***************************************************************************
    void BST_delete(int target);
    
    //***************************************************************************
    //  This function searches by a unique key
    //  It calls the private function _search to check target, returns true if
    //  found, returns false if not
    //***************************************************************************
    bool BST_search(int target);
    
    //***************************************************************************
    //  This funtion prints data in key sequence by calling private funtion
    //  __InorderTraverse
    //***************************************************************************
    void BST_list();
    
    //***************************************************************************
    //  This funtion prints indented tree by calling private funtion _printTree
    //
    //***************************************************************************
    void BST_print() const;
    
    
private:
    //***************************************************************************
    //   This funtion checks if the node is a left node of its parent
    //   The parameter is BST_Node* target
    //   returns true if it is
    //***************************************************************************
    bool _isLeftChild(BST_Node* target);
    
    //***************************************************************************
    //  This funtion finds out the samllest node in right subtree
    //  The parameter is BST_Node* target
    //  returns the pointer of BST_Node*
    //***************************************************************************
    BST_Node* _SmallestNodeinRightSubtree(BST_Node* target);
    
    //***************************************************************************
    //  This funtion finds out the largest node in left subtree
    //  The parameter is BST_Node* target
    //  returns the pointer of BST_Node*
    //***************************************************************************
    BST_Node* _LargestNodeinRightSubtree(BST_Node* target);
    
    //***************************************************************************
    //  This funtion inserts a node to the tree
    //  The parameter is Data* data
    //***************************************************************************
    void _insert(Data* data);
    
    //***************************************************************************
    //  This funtion deletes a node from the tree
    //  The parameter is BST_Node* target
    //***************************************************************************
    void _delete(BST_Node* target);
    
    //***************************************************************************
    //  This funtion searches a node by an unique key
    //  The parameter is int target
    //  returns the pointer if found, returns NULL if not
    //***************************************************************************
    BST_Node* _search(int target);
    
    //***************************************************************************
    //  This funtion is inorder traverasl
    //  The parameter is BST_Node* root
    //***************************************************************************
    void _InorderTraverse(BST_Node* root) const;
    
    //***************************************************************************
    //  This funtion deletes all the nodes in the tree
    //  The parameter is BST_Node* root
    //***************************************************************************
    void _destroy(BST_Node *root);
    
    //***************************************************************************
    //  This funtion prints tree as an indented list
    //  The parameters are BST_Node* root and int level
    //***************************************************************************
    void _printTree(BST_Node* root, int level) const;
};

#endif /* defined(__TeamProject__BST__) */
