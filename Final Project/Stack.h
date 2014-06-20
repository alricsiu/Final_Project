
//  Created by Fangyuan Xing on 5/26/14.
//  Copyright (c) 2014 Emily. All rights reserved.
//***************************************************************************
//  Stack.h
//  The stack class provides an auxiliary data structure to be used in
//  several of the BST traversals.
//***************************************************************************
//
//
#ifndef DYNAMICSTACK_H
#define DYNAMICSTACK_H
#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
    // Structure for the stach nodes
    struct StackNode
    {
        T value;          // Value in the node
        StackNode *next;  // Pointer to next node
    };
    
    StackNode *top;     // Pointer to the stack top
    int count;
    
public:
    //Constructor
    Stack(){top = NULL; count = 0;}
    
    // Destructor
    ~Stack();
    
    // Stack operations
    bool push(T);
    bool pop(T &);
    bool isEmpty();
    int getCount();
    bool getTop(T &item);
};

/**~*~*
 Destructor
 *~**/
template <class T>
Stack<T>::~Stack()
{
    StackNode *currNode, *nextNode;
    
    // Position nodePtr at the top of the stack.
    currNode = top;
    
    // Traverse the list deleting each node.
    while (currNode) //while (currNode != NULL)
    {
        nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
}

/**~*~*
 Member function push pushes the argument onto
 the stack. It returns false if the node cannot
 be pushed because of memory issues, true otherwise.
 *~**/
template <class T>
bool Stack<T>::push(T item)
{
    StackNode *newNode; // Pointer to a new node
    
    // Allocate a new node and store num there.
    newNode = new StackNode;
    if (!newNode)
        return false;
    newNode->value = item;
    
    // Update links and counter
    newNode->next = top;
    top = newNode;
    count++;
    
    return true;
}

/**~*~*
 Member function pop pops the value at the top
 of the stack off, and copies it into the variable
 passed as an argument. It returns false if the
 stack is empty, and true if pop succeeds.
 *~**/
template <class T>
bool Stack<T>::pop(T &item)
{
    StackNode *temp; // Temporary pointer
    
    // empty stack
    if (count == 0)
        return false;
    
    // pop value off top of stack
    item = top->value;
    temp = top->next;
    delete top;
    top = temp;
    count--;
    
    return true;
}

/**~*~*
 Member function isEmpty returns true if the stack
 is empty, or false otherwise.
 *~**/
template <class T>
bool Stack<T>::isEmpty()
{
    return count == 0;
}

// my code
/**~*~*
 Member function getCount returns the number of
 elements in the stack as an integer.
 *~**/
template <class T>
int Stack<T>::getCount()
{
    return count;
}

// my code
/**~*~*
 Member function getTop copies the value at the front
 of the stack into the variable passed as an argument.
 If the stack is empty, it returns false, but if getTop
 succeeds, it returns true.
 *~**/
template <class T>
bool Stack<T>::getTop(T &item)
{
    if(count == 0)
        return false;
    
    item = top -> value;
    return true;
}


#endif
