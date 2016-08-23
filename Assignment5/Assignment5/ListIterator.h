/************************************************************************
* Class: ListIterator
*
* Purpose: This class is an ABC representing a doubly linked list iterator
*
* Manager functions:	
* 	ListIterator()
*		Default Constructor
*	ListIterator(DoubleLinkedList const* list, Node* node)
*		Sets up Iterator on list starting at node
*	ListIterator(ListIterator const& copy)
*		Copy constructor
*	~ListIterator()
*		Destructor
*
* Methods:
*	operator=(ListIterator const& rhs)
*		Assignment operator
*	operator!=(ListIterator const& rhs)
*		Inequality operator
*	operator++()
*		Move the iterator to next position
*	operator*
*		Get the data at current position
*	MoveNext()
*		Moves the iterator to the next node
*	Reset()
*		Resets the iterator to its starting point
*	IsDone()
*		Returns bool representing if iterator has reached end of list
*	GetCurrent()
*		Returns the data in the current node
*************************************************************************/
#pragma once

#include "AbstractIterator.h"

template <class T>
class DoubleLinkedList;

template <class T>
class Node;

template <class T>
class ListIterator : public AbstractIterator<T>{
	protected:
		DoubleLinkedList<T> const* m_list;
		Node<T>* m_current_node;

	public:
		ListIterator();
		ListIterator(DoubleLinkedList<T> const* list, Node<T>* node);
		ListIterator(ListIterator<T> const& copy);
		~ListIterator();

		ListIterator<T> const& operator=(ListIterator<T> const& rhs);
		bool operator!=(ListIterator<T> const& rhs);

		ListIterator<T> & operator++(); // prefix
		//ListIterator<T> const operator++(int); // postfix

		T const& operator*();

		virtual void MoveNext() = 0;
		virtual void Reset() = 0;
		virtual bool IsDone();
		virtual T const& GetCurrent();
};

/**********************************************************************	
* Purpose: ListIterator constructor
*
* Entry: None.
*
* Exit: Constructs ListIterator with default settings.
************************************************************************/
template <class T>
ListIterator<T>::ListIterator() : m_list(0), m_current_node(0){}

/**********************************************************************	
* Purpose: ListIterator constructor
*
* Entry: 
*	Parameters:
*		list: The list the iterator is for
*		node: The starting node for the iterator
*
* Exit: Constructs ListIterator with above settings.
************************************************************************/
template <class T>
ListIterator<T>::ListIterator(DoubleLinkedList<T> const* list, Node<T>* node) : m_list(list), m_current_node(node){}

/**********************************************************************	
* Purpose: ListIterator copy constructor
*
* Entry: 
*	Parameters:
*		copy: The iterator to copy from
*
* Exit: Constructs ListIterator with same settings as the copy.
************************************************************************/
template <class T>
ListIterator<T>::ListIterator(ListIterator<T> const& copy) : m_list(copy.m_list), m_current_node(copy.m_current_node){}

/**********************************************************************	
* Purpose: ListIterator destructor
*
* Entry: None.
*
* Exit: Destroys iterator and resets to default settings
************************************************************************/
template <class T>
ListIterator<T>::~ListIterator(){
	m_list = 0;
	m_current_node = 0;
}

/**********************************************************************	
* Purpose: Inequality operator
*
* Entry: 
*	Parameters:
*		rhs: Right hand side of != operator
*
* Exit: Returns true if they are unequal
************************************************************************/
template <class T>
bool ListIterator<T>::operator!=(ListIterator<T> const& rhs){
	return m_current_node != rhs.m_current_node;
}

/**********************************************************************	
* Purpose: Assignment operator
*
* Entry: 
*	Parameters:
*		rhs: Right hand side of assignment
*
* Exit: Current iterator now has same settings as right hand iterator.
************************************************************************/
template <class T>
ListIterator<T> const& ListIterator<T>::operator=(ListIterator<T> const& rhs){
	m_current_node = rhs.m_current_node;
	m_list = rhs.m_list;
	return *this;
}

/**********************************************************************	
* Purpose: Prefix increment
*
* Entry: None.
*
* Exit: Moves the iterator to the next position
************************************************************************/
template <class T>
ListIterator<T> & ListIterator<T>::operator++(){ // prefix
	MoveNext();
	return *this;
}
/*
template <class T>
ListIterator<T> const ListIterator<T>::operator++(int x){ // postfix
	ListIterator<T> copy(*this);
	MoveNext();
	return copy;
}*/

/**********************************************************************	
* Purpose: Dereference operator overload
*
* Entry: None.
*
* Exit: Returns data at current position
************************************************************************/
template <class T>
T const& ListIterator<T>::operator*(){
	return GetCurrent();
}

/**********************************************************************	
* Purpose: Used to determine if the iterator has reached the end
*
* Entry: None.
*
* Exit: Returns bool representing if the iterator has reached end.
************************************************************************/
template <class T>
bool ListIterator<T>::IsDone(){
	bool done = false;
	if(m_current_node == 0){
		done = true;
	}
	return done;
}

/**********************************************************************	
* Purpose: Returns iterator's current data
*
* Entry: None.
*
* Exit: Returns data at current iterator position.
************************************************************************/
template <class T>
T const& ListIterator<T>::GetCurrent(){
	return m_current_node->getData();
}