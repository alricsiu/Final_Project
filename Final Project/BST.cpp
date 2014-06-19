
//  Created by Fangyuan Xing on 5/26/14.
//  Copyright (c) 2014 Emily. All rights reserved.
//***************************************************************************
//  BST.cpp
//  The role of the BST in the application is to print indented tree, insert
//  items and delete items
//***************************************************************************

#include "BST.h"
#include "Stack.h"
using namespace std;

//***************************************************************************
//   constructor
//
//***************************************************************************
BST::BST()
{
    root = NULL;
    count = 0;
}

//***************************************************************************
//  destructor calls private funtion _destory to delete the whole tree
//
//***************************************************************************
BST::~BST()
{
    if(root)
        _destroy(root);
}

//***************************************************************************
//  This function calls the private function _insert to insert data
//
//***************************************************************************
void BST::BST_insert(Data* data)
{
    _insert(data);
}

//***************************************************************************
//  This function calls the private function _insert to add data
//
//***************************************************************************
void BST::BST_add(Data* data)
{
    _insert(data);
}

//***************************************************************************
//  This function deletes a node by calling the private function _search to
//  search target first, and if found, calls private function _delete, print
//  error message if not found and return
//***************************************************************************
void BST::BST_delete(int target)
{
    BST_Node* found = _search(target);
    
    if(!found)
    {
        cout << "Cannot find in the tree! " << endl;
        return;
    }
    _delete(found);
}

//***************************************************************************
//  This function searches by a unique key
//  It calls the private function _search to check target, returns true if
//  found, returns false if not
//***************************************************************************
bool BST::BST_search(int target)
{
    BST_Node *found = _search(target);
    if (found)
    {
        cout << "found in the tree! " << endl;
        cout << found -> data -> ID << " "
             << found -> data -> name << " "
             << found -> data -> author << " "
        << found -> data -> category << endl;
        return true;
    }
    cout << "cannot find in the tree!" << endl;
    return false;
}

//***************************************************************************
//  This funtion prints data in key sequence by calling private funtion
//  __InorderTraverse
//***************************************************************************
void BST::BST_list()
{
    _InorderTraverse(root);
}

//***************************************************************************
//  This funtion prints indented tree by calling private funtion _printTree
//
//***************************************************************************
void BST::BST_print() const
{
    _printTree(root, 1);
}



//***************************    PRIVATE    ************************************//



//***************************************************************************
//  This funtion inserts a node to the tree
//  The parameter is Data* data
//***************************************************************************
void BST::_insert(Data* data)
{
    BST_Node* newNode = new BST_Node;
    BST_Node* pWalk;
    
    // allocate the new node
    newNode->data = data;
    newNode->left  = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    
    if (!root) // tree is empty
    {
        root = newNode;
        newNode -> parent = NULL;
    }
    
    else
    {
        pWalk = root;
        
        while( pWalk )
        {
            newNode -> parent = pWalk;
            
            if( newNode -> data ->ID < pWalk->data->ID )
                pWalk = pWalk->left;
            else
                pWalk = pWalk->right;
        }
        
        // insert the new node
        if( newNode -> data ->ID < newNode -> parent -> data->ID ) // no left child
            newNode -> parent -> left  = newNode;
        else
           newNode -> parent -> right = newNode;
    }
    count++;
}


//***************************************************************************
//   This funtion checks if the node is a left node of its parent
//   The parameter is BST_Node* target
//   returns true if it is
//***************************************************************************
bool BST::_isLeftChild(BST_Node* target)
{
    return target -> data -> ID < target -> parent -> data -> ID;
}

//***************************************************************************
//  This funtion finds out the samllest node in right subtree
//  The parameter is BST_Node* target
//  returns the pointer of BST_Node*
//***************************************************************************
BST::BST_Node* BST::_SmallestNodeinRightSubtree(BST_Node* target)
{
    while(target -> left)
    {
        target = target -> left;
    }
    return target;
}

//***************************************************************************
//  This funtion finds out the largest node in left subtree
//  The parameter is BST_Node* target
//  returns the pointer of BST_Node*
//***************************************************************************
BST::BST_Node* BST::_LargestNodeinRightSubtree(BST_Node* target)
{
    while(target -> right)
    {
        target = target -> right;
    }
    return target;
}


//***************************************************************************
//  This funtion deletes a node from the tree
//  The parameter is BST_Node* target
//***************************************************************************
void BST::_delete(BST_Node* target)
{
    // target has both left and right children
    if(target -> left && target -> right)
    {
        BST_Node* smallestNode = _SmallestNodeinRightSubtree(target -> right);
        
        target -> data -> ID = smallestNode -> data -> ID;
        target -> data -> name = smallestNode -> data -> name;
        target -> data -> author = smallestNode -> data -> author;
        target -> data -> category = smallestNode -> data -> category;
        
        // smallest -> parent == target
        if(smallestNode -> parent == target)
        {
            // smallest has a child (must be right)
            if(smallestNode -> right)
            {
                smallestNode -> parent -> right = smallestNode -> right;
                smallestNode -> right -> parent = smallestNode -> parent;
                smallestNode -> right = NULL;
                smallestNode -> parent = NULL;
            }
            // smallest has no children
            else
            {
                smallestNode -> parent -> right = NULL;
                smallestNode -> parent = NULL;
            }
        }
        else
        {
            // smallest has a child (must be right)
            if(smallestNode -> right)
            {
                smallestNode -> parent -> left = smallestNode -> right;
                smallestNode -> right -> parent = smallestNode -> parent;
                smallestNode -> right = NULL;
                smallestNode -> parent = NULL;
            }
            // smallest has no children
            else
            {
                smallestNode -> parent -> left = NULL;
                smallestNode -> parent = NULL;
            }
        }
        //delete target;
        return;
    }
    
    // target is the root
    if(target == root)
    {
        // target is the root and no children
        if(target -> left == NULL && target -> right == NULL)
        {
            root = NULL;
        }
        // target is the root and it has only left child
        else if(target -> left && target -> right == NULL)
        {
            root = target -> left;
            target -> left = NULL;
        }
        // target is the root and it has only right child
        else
        {
            root = target -> right;
            target -> right = NULL;
        }
        
        delete target;
        return;
    }
    
    // target is a leaf
    if(target -> left == NULL && target -> right == NULL)
    {
        if(_isLeftChild(target)) // target is a left child of its parent
        {
            target -> parent -> left = NULL;
        }
        else
        {
            target -> parent -> right = NULL;
        }
        target -> parent = NULL;
        delete target;
        return;
    }
    
    // target has only one child which is its right child
    if(target -> left == NULL && target -> right)
    {
        if(_isLeftChild(target)) // target is a left child of its parent
        {
            target -> right -> parent = target -> parent;
            target -> parent -> left = target -> right;
        }
        else // target is a right child of its parent
        {
            target -> right -> parent = target -> parent;
            target -> parent -> right = target -> right;
        }
        target -> parent = NULL;
        target -> right = NULL;
        delete target;
        return;
    }
    
    // target has only one child which is its left child
    if(target -> left && target -> right == NULL)
    {
        if(_isLeftChild(target)) // target is a left child of its parent
        {
            target -> left -> parent = target -> parent;
            target -> parent -> left = target -> left;
        }
        else // target is a right child of its parent
        {
            target -> left -> parent = target -> parent;
            target -> parent -> right = target -> left;
        }
        target -> parent = NULL;
        target -> right = NULL;
        delete target;
        return;
    }
    

}


//***************************************************************************
//  This funtion searches a node by an unique key
//  The parameter is int target
//  returns the pointer if found, returns NULL if not
//***************************************************************************
BST::BST_Node* BST::_search(int target)
{
    if (!root) // tree is empty
        return NULL;
    
    // tree is not empty
    BST_Node* pWalk = root;
    while( pWalk )
    {
        if( target < pWalk->data->ID )
            pWalk = pWalk->left;
        else
            if( target > pWalk->data->ID )
                pWalk = pWalk->right;
            else
                return pWalk; // found
    }
    
    return NULL; // not found
}


//***************************************************************************
//  This funtion is inorder traverasl
//  The parameter is BST_Node* root
//***************************************************************************
void BST::_InorderTraverse(BST_Node* root) const
{
    if (root == NULL)
        return;
    
    Stack<BST_Node*> s;
    bool flag = true;
    BST_Node* temp = root;
    
    while(flag)
    {
        if(temp)
        {
            s.push(temp);
            temp = temp -> left;
        }
        else
        {
            if(!s.isEmpty())
            {
                s.getTop(temp);
                cout << temp -> data->ID << " ";
                s.pop(temp);
                temp = temp -> right;
            }
            else
                flag = false;
        }
    }
}


//***************************************************************************
//  This funtion deletes all the nodes in the tree
//  The parameter is BST_Node* root
//***************************************************************************
void BST::_destroy(BST_Node *root)
{
    if (root)
    {
        _destroy(root->left);
        _destroy(root->right);
        delete root;
        //cout << "destory" << endl;
    }
    return;
}


//***************************************************************************
//  This funtion prints tree as an indented list
//  The parameters are BST_Node* root and int level
//***************************************************************************
void BST::_printTree(BST_Node* root, int level) const
{
    if (root)
    {
        _printTree(root->right, level + 1);
        for(int i = 1; i < level; i++)
        {
            cout << "    ";
        }
        cout << level << ". " << root->data->ID << endl;
        _printTree(root->left, level + 1);
    }
}