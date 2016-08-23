/************************************************************************
* Class: ArrayBasedStack
*
* Purpose: This class represents a array based stack. Supports normal 
*		stack operations such as pop, push, peek, etc.
*
* Manager functions:	
* 	ArrayBasedStack(int size)
*		Creates a stack of size size.
*	ArrayBasedStack(Stack const& copy)
*		Copy constructor
*	~ArrayBasedStack()
*		Destructor
*
* Methods:		
*	operator=(Stack const& rhs)
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
*	isFull()
*		Determines if stack is full
*************************************************************************/
#pragma once

#include "Array.h"

template <class T>
class ArrayBasedStack
{
	private:
		Array<T> m_stack;
		unsigned m_max_size;
		int m_stack_pointer;

	public:
		ArrayBasedStack(int size = 0);
		ArrayBasedStack(ArrayBasedStack<T> const& copy);
		~ArrayBasedStack();

		ArrayBasedStack const& operator=(ArrayBasedStack<T> const& rhs);

		void Push(T const& data);
		T Pop(void);
		T const& Peek(void) const;

		unsigned Size(void) const;
		bool isEmpty(void) const;
		bool isFull(void) const;

		void Purge(void);
};

/**********************************************************************	
* Purpose: 1 arg Stack constructor
*
* Entry:
*	Parameters:
*		size: maximum size of the stack
*
* Exit: Stack of specified size created.
************************************************************************/
template <class T>
ArrayBasedStack<T>::ArrayBasedStack(int size = 0) : m_max_size(size), m_stack_pointer(0)
{
	m_stack.setLength(size);
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
ArrayBasedStack<T>::ArrayBasedStack(ArrayBasedStack<T> const& copy) : m_stack(copy.m_stack), m_max_size(copy.m_max_size), m_stack_pointer(copy.m_stack_pointer)
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
ArrayBasedStack<T>::~ArrayBasedStack()
{
	m_stack.Purge();
	m_max_size = 0;
	m_stack_pointer = 0;
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
ArrayBasedStack<T> const& ArrayBasedStack<T>::operator=(ArrayBasedStack<T> const& rhs)
{
	m_stack = rhs.m_stack;
	m_max_size = rhs.m_max_size;
	m_stack_pointer = rhs.m_stack_pointer;
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
void ArrayBasedStack<T>::Push(T const& data)
{
	if(!isFull())
	{
		m_stack[m_stack_pointer++] = data;
	}
	else
	{
		throw Exception("Cannot Push: Stack Overflow");
	}
}

/**********************************************************************	
* Purpose: Pops the top item off the stack. Returns the popped item.
*
* Entry: None.
*
* Exit: Returns popped item.
************************************************************************/
template <class T>
T ArrayBasedStack<T>::Pop()
{
	if(isEmpty())
	{
		throw Exception("Cannot Pop: Stack Underflow");
	}

	T value = m_stack[m_stack_pointer-1];
	++m_stack_pointer; // purposefully not removing data from the stack, as it will get overwritten on a push anyway
	return value;
}

/**********************************************************************	
* Purpose: Peeks at top element of stack, w/o popping it.
*
* Entry: None.
*
* Exit: Returns top item of stack
************************************************************************/
template <class T>
T const& ArrayBasedStack<T>::Peek() const
{
	if(isEmpty())
	{
		throw Exception("Cannot Peek: Stack Underflow");
	}
	return m_stack[m_stack_pointer-1];
}

/**********************************************************************	
* Purpose: Returns number of items on the stack
*
* Entry: None.
*
* Exit: Returns number of items on the stack
************************************************************************/
template <class T>
unsigned ArrayBasedStack<T>::Size() const
{
	return m_stack_pointer;
}

/**********************************************************************	
* Purpose: Determines if stack is empty
*
* Entry: None.
*
* Exit: Returns bool if stack is empty
************************************************************************/
template <class T>
bool ArrayBasedStack<T>::isEmpty() const
{
	return !m_stack_pointer;
}

/**********************************************************************	
* Purpose: Determines if stack is full
*
* Entry: None.
*
* Exit: Returns bool if stack is full.
************************************************************************/
template <class T>
bool ArrayBasedStack<T>::isFull() const
{
	return (m_max_size == m_stack_pointer);
}

template <class T>
void ArrayBasedStack<T>::Purge(void)
{
	m_stack.Purge();
	m_stack_pointer = 0;
}