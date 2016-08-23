/************************************************************************
* Class: DoubleLinkedList
*
* Purpose: This class represents a doubly linked list. 
*
* Manager functions:	
* 	DoubleLinkedList()
*		Default constructor
*	DoubleLinkedList(DoubleLinkedList const& copy)
*		Copy constructor
*	~DoubleLinkedList()
*		Cleans up the list and resets it to default
*
* Methods:		
*	operator=(DoubleLinkedList const& rhs)
*		Overloaded op= operator.
*	getHead()
*		Returns address of head
*	getTail()
*		Returns address of tail
*	Find(T const& data, bool forward)
*		Returns a pointer to a node containing given data
*	isEmpty()
*		Returns a bool representing if the list is empty
*	First()
*		Returns first element of list
*	Last()
*		Returns last element of list
*	Prepend(T const& data)
*		Prepends data to the list
*	Append(T const& data)
*		Appends data to list
*	Purge()
*		Destroys list contents
*	Extract(T const& data)
*		Removes the first list element that is equal to data
*	InsertAfter(T const& data, T const& after)
*		Inserts data after the node containing after
*	InsertBefore(T const& data, T const& before)
*		Inserts data before the node containing before
*	PrintForwards()
*		Print the list traversing it forwards
*	PrintBackwards()
*		Print the list traversing it backwards
*	begin()
*		Returns forward iterator at head
*	end()
*		Returns forward iterator at tail
*	rbegin()
*		Returns backward iterator at tail
*	rend()
*		Returns backward iterator at head
*************************************************************************/
#pragma once

#include <iostream>
using std::cout;
using std::endl;
#include "Node.h"
#include "ForwardIterator.h"
#include "BackwardIterator.h"

template <class T>
class DoubleLinkedList{
	private:
		Node<T>* m_head;
		Node<T>* m_tail;

		Node<T>* Find(T const& data, bool forward = true);
	public:
		DoubleLinkedList();
		DoubleLinkedList(DoubleLinkedList const& copy);
		~DoubleLinkedList();

		Node<T>* getHead() const;
		Node<T>* getTail() const; 

		DoubleLinkedList const& operator=(DoubleLinkedList const& rhs);

		bool isEmpty() const;

		T const& First() const;
		T const& Last() const;

		void Prepend(T const& data);
		void Append(T const& data);

		void Purge();
		void Extract(T const& data);

		void InsertAfter(T const& data, T const& after);
		void InsertBefore(T const& data, T const& before);

		void PrintForwards() const;
		void PrintBackwards() const;

		ForwardIterator<T> begin() const;
		ForwardIterator<T> end() const;

		BackwardIterator<T> rbegin() const;
		BackwardIterator<T> rend() const;
};

/**********************************************************************	
* Purpose: DoubleLinkedList default constructor. Sets up empty DLL.
*
* Entry: None.
*
* Exit: Constructs a empty DLL.
************************************************************************/
template <class T>
DoubleLinkedList<T>::DoubleLinkedList() : m_head(0), m_tail(0){}

/**********************************************************************	
* Purpose: DoubleLinkedList copy constructor
*
* Entry:
*	Parameters:
*		copy: The DLL to copy from
*
* Exit: Constructs a DLL with the same data as the rhs.
************************************************************************/
template <class T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList const& copy) : m_head(0), m_tail(0){
	// first, we traverse the copy list and duplicate each node as we go
	Node<T>* traveling_ptr = copy.m_head;
	while(traveling_ptr){
		Append(traveling_ptr->getData());
		traveling_ptr = traveling_ptr->m_next;
	}
}

/**********************************************************************	
* Purpose: DoubleLinkedList destructor. Cleans up the list and resets.
*
* Entry: None.
*
* Exit: Cleans up memory and resets the DLL.
************************************************************************/
template <class T>
DoubleLinkedList<T>::~DoubleLinkedList(){
	// traverse the list, and delete data/nodes as we go
	Node<T>* trailing_ptr = 0;
	Node<T>* traveling_ptr = m_head;

	while(traveling_ptr){
		// advance the pointers
		trailing_ptr = traveling_ptr;
		traveling_ptr = traveling_ptr->m_next;

		// then delete the trailing node
		delete trailing_ptr;
	}
	m_head = m_tail = 0;
}

/**********************************************************************	
* Purpose: Returns head address of DLL
*
* Entry: None.
*
* Exit: Returns address of head.
************************************************************************/
template <class T>
Node<T>* DoubleLinkedList<T>::getHead() const{
	return m_head;
}

/**********************************************************************	
* Purpose: Returns address of tail.
*
* Entry: None.
*
* Exit: Returns address of tail.
************************************************************************/
template <class T>
Node<T>* DoubleLinkedList<T>::getTail() const{
	return m_tail;
}

/**********************************************************************	
* Purpose: DLL class op=
*
* Entry:
*	Parameters:
*		rhs: The DLL to copy from
*
* Exit: Constructs a DLL with the same data as the rhs.
************************************************************************/
template <class T>
DoubleLinkedList<T> const& DoubleLinkedList<T>::operator=(DoubleLinkedList<T> const& rhs){
	// first, we traverse the rhs list and duplicate each node as we go
	Node<T>* traveling_ptr = rhs.m_head;
	while(traveling_ptr){
		Append(traveling_ptr->getData());
		traveling_ptr = traveling_ptr->m_next;
	}
	return *this;
}

/**********************************************************************	
* Purpose: Returns if the list is empty
*
* Entry: None.
*
* Exit: Returns bool.
************************************************************************/
template <class T>
bool DoubleLinkedList<T>::isEmpty() const{
	return (!m_head);
}

/**********************************************************************	
* Purpose: Returns first element of list
*
* Entry: None.
*
* Exit: Returns first element of list
************************************************************************/
template <class T>
T const& DoubleLinkedList<T>::First() const{
	T* data;
	if(!isEmpty()){
		data = m_head->m_data;
	}else{
		throw "Cannot get first; Linked list is empty";
	}
	return *data;
}

/**********************************************************************	
* Purpose: Returns last element of list
*
* Entry: None.
*
* Exit: Returns last element of list
************************************************************************/
template <class T>
T const& DoubleLinkedList<T>::Last() const{
	T* data;
	if(!isEmpty()){
		data = m_tail->m_data;
	}else{
		throw "Cannot get last; Linked list is empty";
	}
	return *data;
}

/**********************************************************************	
* Purpose: Helper function to find address of a particular node
*
* Entry:
*	Parameters:
*		data: the data criteria to match in the node
*		forward: traverse the list forward? (true = yes, false = backward)
*
* Exit: Returns address of node, or throws exception if not found.
************************************************************************/
template <class T>
Node<T>* DoubleLinkedList<T>::Find(T const& data, bool forward = true){
	bool found = false;
	Node<T>* traveling_ptr = (forward)? m_head : m_tail;

	while(!found && traveling_ptr){
		if(traveling_ptr->getData() == data){
			found = true;
		}else{
			traveling_ptr = (forward)? traveling_ptr->m_next : traveling_ptr->m_prev;
		}
	}
	if(!found){
		throw "Element not found.";
	}
	return traveling_ptr;
}

/**********************************************************************	
* Purpose: Prepends data to the list
*
* Entry:
*	Parameters:
*		data: the data to prepend
*
* Exit: The data is prepended to the list.
************************************************************************/
template <class T>
void DoubleLinkedList<T>::Prepend(T const& data){
	T* new_data = new T;
	*new_data = data;

	Node<T>* new_node = new Node<T>(new_data, 0, m_head);
	if(m_head){
		m_head->m_prev = new_node;
	}
	if(!m_tail){
		m_tail = new_node;
	}

	m_head = new_node;
}

/**********************************************************************	
* Purpose: Appends data to the list
*
* Entry:
*	Parameters:
*		data: the data to append
*
* Exit: Data is appended to the list.
************************************************************************/
template <class T>
void DoubleLinkedList<T>::Append(T const& data){
	T* new_data = new T;
	*new_data = data;

	Node<T>* new_node = new Node<T>(new_data, m_tail, 0);
	
	// if we have an empty list, change the head to the new node
	if(!m_head){
		m_head = new_node;
	}

	// if there is a tail node, set its next to the new node
	if(m_tail){
		m_tail->m_next = new_node;
	}

	// set the tail to the newly appended node
	m_tail = new_node;
}

/**********************************************************************	
* Purpose: Purges the list of all elements
*
* Entry: None.
*
* Exit: List is now empty
************************************************************************/
template <class T>
void DoubleLinkedList<T>::Purge(){
	// traverse the list, and delete data/nodes as we go
	Node<T>* trailing_ptr = 0;
	Node<T>* traveling_ptr = m_head;

	while(traveling_ptr){
		// advance the pointers
		trailing_ptr = traveling_ptr;
		traveling_ptr = traveling_ptr->m_next;

		// then delete the trailing node
		delete trailing_ptr;
	}
	m_head = m_tail = 0;
}

/**********************************************************************	
* Purpose: Removes an element from the list matching data
*
* Entry:
*	Parameters:
*		data: the data criteria to match the node
*
* Exit: Node with matching data is removed from list, or if not found, exception.
************************************************************************/
template <class T>
void DoubleLinkedList<T>::Extract(T const& data){
	Node<T>* x = Find(data); // called x for simplicity, represents the pointer to the node that contains matching data

	if(x == m_head && x == m_tail){
		// removing single element node
		m_head = 0;
		m_tail = 0;
	}else if(x == m_head){
		// head
		x->m_next->m_prev = 0;
		m_head = x->m_next;
	}else if(x == m_tail){
		// tail
		x->m_prev->m_next = 0;
		m_tail = x->m_prev;
	}else{
		// in the middle somewhere
		x->m_prev->m_next = x->m_next;
		x->m_next->m_prev = x->m_prev;
	}

	// and finally remove the node
	delete x;
}

/**********************************************************************	
* Purpose: Inserts data after a node matching data
*
* Entry:
*	Parameters:
*		data: the data to insert
*		after: the data criteria to insert after
*
* Exit: Node with data is inserted after the node matching after.
************************************************************************/
template <class T>
void DoubleLinkedList<T>::InsertAfter(T const& data, T const& after){
	Node<T>* x = Find(after);

	T* new_data = new T;
	*new_data = data;

	Node<T>* new_node = 0;
	if(x == m_tail){
		// inserting after the tail
		new_node = new Node<T>(new_data, x, 0);
		m_tail = new_node;
	}else{
		new_node = new Node<T>(new_data, x, x->m_next);
		x->m_next->m_prev = new_node;
	}

	x->m_next = new_node;

}

/**********************************************************************	
* Purpose: Inserts data before a node matching data
*
* Entry:
*	Parameters:
*		data: the data to insert
*		before: the data criteria to insert before
*
* Exit: Node with data is inserted before the node matching before.
************************************************************************/
template <class T>
void DoubleLinkedList<T>::InsertBefore(T const& data, T const& before){
	Node<T>* x = Find(before);
	
	T* new_data = new T;
	*new_data = data;

	Node<T>* new_node = 0;
	if(x == m_head){
		// inserting before the head
		new_node = new Node<T>(new_data, 0, m_head);
		m_head = new_node;
	}else{
		new_node = new Node<T>(new_data, x->m_prev, x);
		x->m_prev->m_next = new_node;
	}

	x->m_prev = new_node;
}

/**********************************************************************	
* Purpose: Prints the list via forward traversal
*
* Entry: None.
*
* Exit: The list is outputted to console.
************************************************************************/
template <class T>
void DoubleLinkedList<T>::PrintForwards() const{
	Node<T>* traveling_ptr = m_head;
	while(traveling_ptr){
		cout << traveling_ptr->getData() << " ";
		traveling_ptr = traveling_ptr->m_next;
	}
	cout << endl;
}

/**********************************************************************	
* Purpose: Prints the list via backward traversal
*
* Entry: None.
*
* Exit: The list is outputted to console.
************************************************************************/
template <class T>
void DoubleLinkedList<T>::PrintBackwards() const{
	Node<T>* traveling_ptr = m_tail;
	while(traveling_ptr){
		cout << traveling_ptr->getData() << " ";
		traveling_ptr = traveling_ptr->m_prev;
	}
	cout << endl;
}

/**********************************************************************	
* Purpose: Returns a forward iterator, starting at the beginning of list
*
* Entry: None.
*
* Exit: Iterator is returned by value
************************************************************************/
template <class T>
ForwardIterator<T> DoubleLinkedList<T>::begin() const{
	return ForwardIterator<T>(this, m_head);
}

/**********************************************************************	
* Purpose: Returns a forward iterator, starting at the end of list
*
* Entry: None.
*
* Exit: Iterator is returned by value
************************************************************************/
template <class T>
ForwardIterator<T> DoubleLinkedList<T>::end() const{
	return ForwardIterator<T>();
}

/**********************************************************************	
* Purpose: Returns a backward iterator, starting at the end of list
*
* Entry: None.
*
* Exit: Iterator is returned by value
************************************************************************/
template <class T>
BackwardIterator<T> DoubleLinkedList<T>::rbegin() const{
	return BackwardIterator<T>(this, m_tail);
}

/**********************************************************************	
* Purpose: Returns a backward iterator, starting at the beginning of list
*
* Entry: None.
*
* Exit: Iterator is returned by value
************************************************************************/
template <class T>
BackwardIterator<T> DoubleLinkedList<T>::rend() const{
	return BackwardIterator<T>();
}