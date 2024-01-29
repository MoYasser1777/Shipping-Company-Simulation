#ifndef _NODE
#define _NODE
template < typename T>
class Node
{
private:
	T item; // A data item
	Node<T>* next;// Pointer to next node
	int priority;
public:
	Node();
	Node(const T& r_Item, int p = 0);
	Node(const T& r_Item, Node<T>* nextNodePtr, int p = 0);
	void setItem(const T& r_Item);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const;
	Node<T>* getNext() const;
	void setPriority(int x);
	int getPriority()const;
}; // end Node


template < typename T>
Node<T>::Node()
{
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item, int p)
{
	item = r_Item;
	next = nullptr;
	priority = p;

}

template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr, int p)
{
	item = r_Item;
	next = nextNodePtr;
	priority = p;
}
template < typename T>
void Node<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T Node<T>::getItem() const
{
	return item;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}
template < typename T>
void Node<T>::setPriority(int x)
{
	priority = x;
}

template < typename T>
int Node<T>::getPriority() const
{
	return priority;
}
#endif
