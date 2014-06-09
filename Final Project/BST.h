//
//  BST.h
//  TeamProject
//
//  Created by Fangyuan Xing on 5/26/14.
//  Copyright (c) 2014 Emily. All rights reserved.
//

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
    // constructor
    BST();
    
    // destructor
    ~BST();
    
    // for test getting count
    int getCount()
    {
        return count;
    }
    
    // insert node to the tree
    void BST_insert(Data* data);
    
    // add new node to the tree
    void BST_add(Data* data);
    
    // delete a node
    void BST_delete(int target);
    
    // search by a unique key
    bool BST_search(int target);
    
    // list data in key sequence(sorted)
    void BST_list();
    
    // print tree as an indented list
    void BST_print() const;
    
    
private:
    // find out this node is it a left node of its parent
    bool _isLeftChild(BST_Node* target);
    
    // find out the smallest node in right subtree
    BST_Node* _SmallestNodeinRightSubtree(BST_Node* target);
    
    // find out the largest node in left subtree
    BST_Node* _LargestNodeinRightSubtree(BST_Node* target);
    
    // insert
    void _insert(Data* data);
    
    // delete
    void _delete(BST_Node* target);
    
    // search
    BST_Node* _search(int target);
    
    // inorder traversal - stack
    void _InorderTraverse(BST_Node* root) const;
    
    // destroy tree
    void _destroy(BST_Node *root);
    
    // print tree as an indented list
    void _printTree(BST_Node* root, int level) const;
};

#endif /* defined(__TeamProject__BST__) */
