// Specification file for the BST class
#ifndef BST_H
#define BST_H

using namespace std;

struct Data
{
   int num;
   // more fields could be added if needed
};

class BST
{
private:
    struct BST_Node
    {
        Data data;         // The value in this node
        BST_Node *left;    // To point to the left node
        BST_Node *right;   // To point to the right node
    } ;

    BST_Node *root;       // root of the tree
    int count;            // number of nodes in the tree

public:
    // Constructor
    BST();

    // Destructor
    ~BST();

    // Binary Tree operations
    void BST_insert(Data dataIn);
    bool Search(int target, Data &data);
    void BST_InorderTraverse() const;
    void display();
    void displayIndented();

private:
    BST_Node *_search(int target);
    void _BST_InorderTraverse( BST_Node *root ) const;
    void _BST_Destroy(BST_Node *root);
};
#endif
