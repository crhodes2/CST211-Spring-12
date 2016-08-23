/************************************************************************
* Class: ListBasedStack
*
* Purpose: This class represents a list based stack. Supports normal 
*		stack operations such as pop, push, peek, etc.
*
* Manager functions:	
* 	ListBasedStack()
*		Creates a stack.
*	ListBasedStack(ListBasedStack const& copy)
*		Copy constructor
*	~ListBasedStack()
*		Destructor
*
* Methods:		
*	operator=(ListBasedStack const& rhs)
*		Assignment operator
*	Push(T const& data)
*		Pushes data onto the stack
*	Pop()
*		Pops data off the stack
*	Peek()
*		Peeks at top item of stack
*	Size()
*		Returns how many items are on stack
*	isEmpty()
*		Determines if stack is empty
*************************************************************************/
#pragma once

#include "DoubleLinkedList.h"

template <class T>
class ListBasedStack
{
	private:
		DoubleLinkedList<T> m_stack;
		unsigned m_current_size;
	public:
		ListBasedStack();
		ListBasedStack(ListBasedStack<T> const& copy);
		~ListBasedStack();

		ListBasedStack const& operator=(ListBasedStack<T> const& rhs);

		void Push(T const& data);
		T Pop();
		T const& Peek();

		unsigned Size();
		bool isEmpty();

		void Purge(void);
};

/**********************************************************************	
* Purpose: 0 arg Stack constructor
*
* Entry: None.
*
* Exit: Stack created.
************************************************************************/
template <class T>
ListBasedStack<T>::ListBasedStack() : m_current_size(0)
{

}

/**********************************************************************	
* Purpose: Stack copy constructor
*
* Entry:
*	Parameters:
*		copy: the stack to copy
*
* Exit: Copy is duplicated to current stack
************************************************************************/
template <class T>
ListBasedStack<T>::ListBasedStack(ListBasedStack<T> const& copy) : m_stack(copy.m_stack), m_current_size(copy.m_current_size)
{

}

/**********************************************************************	
* Purpose: Stack destructor
*
* Entry: None.
*
* Exit: Stack is cleaned up and reset to default
************************************************************************/
template <class T>
ListBasedStack<T>::~ListBasedStack()
{
	Purge();
}

/**********************************************************************	
* Purpose: overloaded op= for stack
*
* Entry:
*	Parameters:
*		rhs: the right hand stack
*
* Exit: Stack now has same data/members as rhs
************************************************************************/
template <class T>
ListBasedStack<T> const& ListBasedStack<T>::operator=(ListBasedStack<T> const& rhs)
{
	m_stack = rhs.m_stack;
	m_current_size = rhs.m_current_size;
	return *this;
}

/**********************************************************************	
* Purpose: Pushes an item onto the stack
*
* Entry:
*	Parameters:
*		data: item to push onto stack
*
* Exit: data is pushed onto stack
************************************************************************/
template <class T>
void ListBasedStack<T>::Push(T const& data)
{
	m_stack.Prepend(data);
	m_current_size++;
}

/**********************************************************************	
* Purpose: Pops the top item off the stack. Returns the popped item.
*
* Entry: None.
*
* Exit: Returns popped item.
************************************************************************/
template <class T>
T ListBasedStack<T>::Pop()
{
	if(isEmpty())
	{
		throw Exception("Cannot Pop: Stack Underflow");
	}

	T element = m_stack.First();

	m_stack.Extract(element);

	m_current_size--;

	return element;
}

/**********************************************************************	
* Purpose: Peeks at top element of stack, w/o popping it.
*
* Entry: None.
*
* Exit: Returns top item of stack
************************************************************************/
template <class T>
T const& ListBasedStack<T>::Peek()
{
	if(isEmpty())
	{
		throw Exception("Cannot Peek: Stack Underflow");
	}
	return m_stack.First();
}

/**********************************************************************	
* Purpose: Returns number of items on the stack
*
* Entry: None.
*
* Exit: Returns number of items on the stack
************************************************************************/
template <class T>
unsigned ListBasedStack<T>::Size()
{
	return m_current_size;
}

/**********************************************************************	
* Purpose: Determines if stack is empty
*
* Entry: None.
*
* Exit: Returns bool if stack is empty
************************************************************************/
template <class T>
bool ListBasedStack<T>::isEmpty()
{
	return !m_current_size;
}

template <class T>
void ListBasedStack<T>::Purge(void)
{
	m_stack.Purge();
	m_current_size = 0;
}