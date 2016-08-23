/************************************************************************
* Class: ForwardIterator
*
* Purpose: This class represents a forward traversing iterator for a 
*		doubly linked list. 
*
* Manager functions:	
* 	ForwardIterator()
*		Default Constructor
*	ForwardIterator(DoubleLinkedList const* list, Node* node)
*		Creates forward iterator on list, starting at node
*	ForwardIterator(ForwardIterator const& copy)
*		Copy constructor
*	~ForwardIterator()
*		Destructor
*
* Methods:
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

#include "ListIterator.h"

template <class T>
class DoubleLinkedList;

template <class T>
class ForwardIterator : public ListIterator<T>{
	public:
		ForwardIterator();
		ForwardIterator(DoubleLinkedList<T> const* list, Node<T>* node);
		ForwardIterator(ForwardIterator<T> const& copy);
		~ForwardIterator();

		using ListIterator<T>::operator=;

		virtual void MoveNext();
		virtual void Reset();
};

/**********************************************************************	
* Purpose: ForwardIterator constructor
*
* Entry:
*	Parameters:
*		list: The list the iterator is for
*		node: The starting node for the iterator
*
* Exit: Constructs ForwardIterator with above settings.
************************************************************************/
template <class T>
ForwardIterator<T>::ForwardIterator(DoubleLinkedList<T> const* list, Node<T>* node) : ListIterator<T>(list, node) {}

/**********************************************************************	
* Purpose: ForwardIterator constructor
*
* Entry: None.
*
* Exit: Constructs ForwardIterator with default ListIterator settings.
************************************************************************/
template <class T>
ForwardIterator<T>::ForwardIterator() : ListIterator<T>() {}

/**********************************************************************	
* Purpose: ForwardIterator copy constructor
*
* Entry:
*	Parameters:
*		copy: The ForwardIterator to copy from
*
* Exit: Constructs ForwardIterator with same settings as copy.
************************************************************************/
template <class T>
ForwardIterator<T>::ForwardIterator(ForwardIterator<T> const& copy) : ListIterator<T>(copy) {}

/**********************************************************************	
* Purpose: ForwardIterator destructor
*
* Entry: None.
*
* Exit: Destroys ForwardIterator and resets to default
************************************************************************/
template <class T>
ForwardIterator<T>::~ForwardIterator() {}

/**********************************************************************	
* Purpose: Moves the iterator to the next node
*
* Entry: None.
*
* Exit: Iterator is now at the next node in the list
************************************************************************/
template <class T>
void ForwardIterator<T>::MoveNext(){
	m_current_node = m_current_node->m_next;
}

/**********************************************************************	
* Purpose: Resets the ForwardIterator to the start point of the list.
*
* Entry: None.
*
* Exit: Iterator's position is reset.
************************************************************************/
template <class T>
void ForwardIterator<T>::Reset(){
	m_current_node = m_list->getHead();
}