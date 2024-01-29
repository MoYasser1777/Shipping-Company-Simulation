#ifndef QUEUE_
#define QUEUE_

#include "Node.h"

#include <vector>
using namespace std;


template <typename T>
class perQueue
{
private:

	int counter;
	Node<T>* frontPtr;
public:
	perQueue();
	bool isEmpty()const ;
	bool enqueue(const T& newEntry,int p);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	Node<T>* getfront()const;
	int getCount()const;
	~perQueue();

	//copy constructor
	perQueue(const perQueue<T>& LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
perQueue<T>::perQueue()
{
	counter = 0;
	frontPtr = nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool perQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool perQueue<T>::enqueue(const T& newEntry,int p)
{
	Node<T>* newNodePtr = new Node<T>(newEntry,p);
	// Insert the new node
	if (isEmpty() || p < frontPtr->getPriority())	//special case if this is the first node to insert

	{
		newNodePtr->setNext(frontPtr);
		
		frontPtr = newNodePtr;
		

	}

	else
	{
		Node<T>* ptr = frontPtr;
		while (ptr->getNext() && ptr->getNext()->getPriority() <= p)
			ptr = ptr->getNext();
		newNodePtr->setNext(ptr->getNext());
		ptr->setNext(newNodePtr);


	}
	counter++;
	return true;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool perQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	counter--;
	return true;

}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/
template <typename T>
bool perQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
template<typename T>
inline Node<T>* perQueue<T>::getfront()const
{
	return frontPtr;
}
template<typename T>
int perQueue<T>::getCount()const
{
	return counter;
}
///////////////////////////////////////////////////////////////////////////////////
/*
Function: destructor
removes all nodes from the queue by dequeuing them
*/
template <typename T>
perQueue<T>::~perQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: LinkedQueue<T>: The Queue to be copied
Output: none
*/

template <typename T>
perQueue<T>::perQueue(const perQueue<T>& LQ)
{
	Node<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr =  nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frontPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	Node<T>* ptr2 = frontPtr;
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		
		ptr2->setNext(ptr);
		ptr2 = ptr;
		NodePtr = NodePtr->getNext();
	}
}

#endif

