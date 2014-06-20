//
//  Created by Fangyuan Xing on 5/26/14.
//  Copyright (c) 2014 Emily. All rights reserved.
//***************************************************************************
//  Queue.h
//  Queue is used as an auxiliary data structure for the BST's Breadth-First
//  Traversal.
//***************************************************************************
#ifndef DYNAMICQUEUE_H // change DYNAMICSTACK to DYNAMICQUEUE
#define DYNAMICQUEUE_H // change DYNAMICSTACK to DYNAMICQUEUE
#include <iostream>
using namespace std;

template <class T>
class Queue
{
private:
    // Structure for the queue nodes
    struct QueueNode
    {
        T value;          // Value in the node
        QueueNode *next;  // Pointer to next node
    };
    
    QueueNode *front;    // Pointer to the queue front
    QueueNode *rear;     // Pointer to the queue rear
    int count;
    
public:
    //Constructor
    Queue(){front = rear = NULL; count = 0;}
    
    // Destructor
    ~Queue();
    
    // Stack operations
    bool enqueue(T);
    bool dequeue(T &);
    bool isEmpty();
    int  getCount();
    bool queueFront(T &);
    bool queueRear(T &);
};

/**~*~*
 Destructor
 *~**/
template <class T>
Queue<T>::~Queue()
{
    QueueNode *currNode, *nextNode;
    
    // Position nodePtr at the top of the stack.
    currNode = front;
    
    // Traverse the list deleting each node.
    while (currNode) //while (currNode != NULL)
    {
        nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
}


/**~*~*
 Member function getCount returns
 the number of elements in the queue
 *~**/
template <class T>
int Queue<T>::getCount()
{
    return count;
}

/**~*~*
 Member function isEmpty returns true if the stack
 is empty, or false otherwise.
 *~**/
template <class T>
bool Queue<T>::isEmpty()
{
    return count == 0;
}

/**~*~*
 Member function enqueue inserts the argument into
 the queue. It returns true for a successful operation,
 and false if the new node cannot be allocated because
 of memory issues.
 *~**/
template <class T>
bool Queue<T>::enqueue(T item)
{
    QueueNode *newNode; // Pointer to a new node
    
    // Allocate a new node and store num there.
    newNode = new QueueNode;
    if (!newNode)
        return false;
    newNode->value = item;
    
    // Update links and counter
    newNode->next = NULL;
    
    if( front == NULL )        // insert to an empty queue
        front = newNode;
    else
        rear->next = newNode;
    
    count++;
    rear = newNode;
    
    return true;
}

/**~*~*
 Member function dequeue deletes the value at the front
 of the queue, and copies it into the variable
 passed as an argument. It returns false if the queue is
 already empty and true if the dequeue works.
 *~**/
template <class T>
bool Queue<T>::dequeue(T &item)
{
    QueueNode *pDel; // Temporary pointer
    
    // empty queue
    if (count == 0)
        return false;
    
    // delete the value at the front of the queue
    item = front->value;
    pDel = front;
    
    if( count == 1 )
        rear = front = NULL;
    else
        front = front->next;
    
    count--;
    delete pDel;
    
    return true;
}

/**~*~*
 Member function queueFront copies the value at the front
 of the queue into the variable passed as an argument.
 If the queue is empty, it returns false; it returns true
 if the operations succeeds.
 *~**/
template <class T>
bool Queue<T>::queueFront(T &item)
{
    if( front == NULL )
        return false;
    
    item = front->value;
    
    return true;
}

/**~*~*
 Member function queueRear copies the value at the rear
 of the queue into the variable passed as an argument.
 If the queue is empty, it returns false; otherwise, it
 returns true.
 *~**/
template <class T>
bool Queue<T>::queueRear(T &item)
{
    if( rear == NULL )
        return false;
    
    item = rear->value;
    return false;
}

#endif
