// Implementation file for the BST class
#include <iostream>  // For cout and NULL

#include "BST.h"

using namespace std;

/**~*~*
   Constructor
*~**/
BST::BST()
{
    root = NULL;
    count = 0;
}

/**~*~*
   This function calls a recursive function to traverse the
   tree in inorder
*~**/
void BST::BST_InorderTraverse() const
{
    _BST_InorderTraverse(root);
}

/**~*~*
   Inorder Traversal of the Binary Tree:
   Left-Root-Right
*~**/
void BST::_BST_InorderTraverse(BST_Node *root) const
{
    if (root)
    {
        _BST_InorderTraverse(root->left);
        cout << root->data.num << endl;
        _BST_InorderTraverse(root->right);
    }
}

/**~*~*
   Insert data into a BST
*~**/
void BST::BST_insert(Data dataIn)
{
    BST_Node *newNode;
    BST_Node *pWalk;
    BST_Node *parent;

    // allocate the new node
    newNode = new BST_Node;
    newNode->data  = dataIn;
    newNode->left  = NULL;
    newNode->right = NULL;

    if (!root) // tree is empty
        root = newNode;
    else
    {
        pWalk = root;
        while( pWalk )
        {
            parent   = pWalk;
            if( dataIn.num < pWalk->data.num )
                pWalk = pWalk->left;
            else
                pWalk = pWalk->right;
        }

        // insert the new node
        if( dataIn.num < parent->data.num ) // no left child
             parent->left  = newNode;
        else
             parent->right = newNode;
    }

    count++;
}


/**~*~*
   Destructor
   This function calls a recursive function to delete all nodes in the binary tree
*~**/
BST::~BST()
{
    if (root)
        _BST_Destroy(root);
}

/**~*~*
   This function traverses the binary tree in postorder and deletes every node
*~**/
void BST::_BST_Destroy(BST_Node *root)
{
    if (root)
    {
        _BST_Destroy(root->left);
        _BST_Destroy(root->right);
        delete root;
    }
    return;
}

/**~*~*
   Search a BST for a given target: if found, returns true and passes back
   data, otherwise returns false. It calls the private _search to locate the node.
*~**/
bool BST::Search(int target, Data &data)
{
    BST_Node *found = _search(target);
    if (found)
    {
        data = found->data;
        return true;
    }
    return false;
}

/**~*~*
   Locates the node that contains a given target in a BST:
   - if found returns a pointer to that node
   - if not found returns NULL
*~**/
BST::BST_Node* BST::_search(int target)
{
    if (!root) // tree is empty
        return NULL;

    // tree is not empty
    BST_Node *pWalk = root;
    while( pWalk )
    {
        if( target < pWalk->data.num )
            pWalk = pWalk->left;
        else
            if( target > pWalk->data.num )
                pWalk = pWalk->right;
            else
                return pWalk; // found
    }

    return NULL; // not found
}


