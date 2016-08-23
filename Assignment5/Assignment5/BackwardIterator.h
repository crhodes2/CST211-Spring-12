/************************************************************************
* Class: BackwardIterator
*
* Purpose: This class represents a backward traversing iterator for a 
*		doubly linked list. 
*
* Manager functions:	
* 	BackwardIterator()
*		Default Constructor
*	BackwardIterator(DoubleLinkedList const* list, Node* node)
*		Creates Backward iterator on list, starting at node
*	BackwardIterator(BackwardIterator const& copy)
*		Copy constructor
*	~BackwardIterator()
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
class BackwardIterator : public ListIterator<T>{
	public:
		BackwardIterator();
		BackwardIterator(DoubleLinkedList<T> const* list, Node<T>* node);
		BackwardIterator(BackwardIterator<T> const& copy);
		~BackwardIterator();

		using ListIterator<T>::operator=;

		virtual void MoveNext();
		virtual void Reset();
};

/**********************************************************************	
* Purpose: BackwardIterator constructor
*
* Entry:
*	Parameters:
*		list: The list the iterator is for
*		node: The starting node for the iterator
*
* Exit: Constructs BackwardIterator with above settings.
************************************************************************/
template <class T>
BackwardIterator<T>::BackwardIterator(DoubleLinkedList<T> const* list, Node<T>* node) : ListIterator<T>(list, node){
}

/**********************************************************************	
* Purpose: BackwardIterator constructor
*
* Entry: None.
*
* Exit: Constructs BackwardIterator with default ListIterator settings.
************************************************************************/
template <class T>
BackwardIterator<T>::BackwardIterator() : ListIterator<T>() {}

/**********************************************************************	
* Purpose: BackwardIterator copy constructor
*
* Entry:
*	Parameters:
*		copy: The BackwardIterator to copy from
*
* Exit: Constructs BackwardIterator with same settings as copy.
************************************************************************/
template <class T>
BackwardIterator<T>::BackwardIterator(BackwardIterator<T> const& copy) : ListIterator<T>(copy) {}

/**********************************************************************	
* Purpose: BackwardIterator destructor
*
* Entry: None.
*
* Exit: Destroys BackwardIterator and resets to default
************************************************************************/
template <class T>
BackwardIterator<T>::~BackwardIterator() {}

/**********************************************************************	
* Purpose: Moves the iterator to the next node
*
* Entry: None.
*
* Exit: Iterator is now at the next node in the list
************************************************************************/
template <class T>
void BackwardIterator<T>::MoveNext(){
	m_current_node = m_current_node->m_prev;
}

/**********************************************************************	
* Purpose: Resets the BackwardIterator to the start point of the list.
*
* Entry: None.
*
* Exit: Iterator's position is reset.
************************************************************************/
template <class T>
void BackwardIterator<T>::Reset(){
	m_current_node = m_list->getTail();
}