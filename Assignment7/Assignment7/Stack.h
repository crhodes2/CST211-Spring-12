/************************************************************************
* Class: Stack
*
* Purpose: This class represents a list based stack. Supports normal 
*		stack operations such as pop, push, peek, etc.
*
* Manager functions:	
* 	Stack()
*		Creates a stack.
*	Stack(Stack const& copy)
*		Copy constructor
*	~Stack()
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
*************************************************************************/
#pragma once

#include "DoubleLinkedList.h"

template <class T>
class Stack{
	private:
		DoubleLinkedList<T> m_stack;
		unsigned m_current_size;
	public:
		Stack();
		Stack(Stack<T> const& copy);
		~Stack();

		Stack const& operator=(Stack<T> const& rhs);
		void Push(T const& data);
		T const& Pop();
		T const& Peek();
		unsigned Size();
		bool isEmpty();
};

/**********************************************************************	
* Purpose: 0 arg Stack constructor
*
* Entry: None.
*
* Exit: Stack created.
************************************************************************/
template <class T>
Stack<T>::Stack() : m_current_size(0){}

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
Stack<T>::Stack(Stack<T> const& copy) : m_stack(copy.m_stack), m_current_size(copy.m_current_size){}

/**********************************************************************	
* Purpose: Stack destructor
*
* Entry: None.
*
* Exit: Stack is cleaned up and reset to default
************************************************************************/
template <class T>
Stack<T>::~Stack(){
	m_stack.Purge();
	m_current_size = 0;
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
Stack<T> const& Stack<T>::operator=(Stack<T> const& rhs){
	m_stack = rhs.m_stack;
	m_current_size = rhs.m_current_size;
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
void Stack<T>::Push(T const& data){
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
T const& Stack<T>::Pop(){
	if(isEmpty()){
		throw Exception("Cannot Pop: Stack Underflow");
	}

	T temp = m_stack.First();
	m_stack.Extract(temp);
	m_current_size--;
	return temp;
}

/**********************************************************************	
* Purpose: Peeks at top element of stack, w/o popping it.
*
* Entry: None.
*
* Exit: Returns top item of stack
************************************************************************/
template <class T>
T const& Stack<T>::Peek(){
	if(isEmpty()){
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
unsigned Stack<T>::Size(){
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
bool Stack<T>::isEmpty(){
	return !m_current_size;
}