/************************************************************************
* Class: Stack
*
* Purpose: This class represents a array based stack. Supports normal 
*		stack operations such as pop, push, peek, etc.
*
* Manager functions:	
* 	Stack(int size)
*		Creates a stack of size size.
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
*	isFull()
*		Determines if stack is full
*************************************************************************/
#pragma once

#include "Array.h"

template <class T>
class Stack{
	private:
		Array<T> m_stack;
		unsigned m_max_size;
		int m_stack_pointer;
	public:
		Stack(int size);
		Stack(Stack<T> const& copy);
		~Stack();

		Stack const& operator=(Stack<T> const& rhs);
		void Push(T const& data);
		T const& Pop();
		T const& Peek();
		unsigned Size();
		bool isEmpty();
		bool isFull();
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
Stack<T>::Stack(int size) : m_max_size(size), m_stack_pointer(0), m_stack(size,0){
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
Stack<T>::Stack(Stack<T> const& copy) : m_stack(copy.m_stack), m_max_size(copy.m_max_size), m_stack_pointer(copy.m_stack_pointer){}

/**********************************************************************	
* Purpose: Stack destructor
*
* Entry: None.
*
* Exit: Stack is cleaned up and reset to default
************************************************************************/
template <class T>
Stack<T>::~Stack(){
	m_stack.setLength(0);
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
Stack<T> const& Stack<T>::operator=(Stack<T> const& rhs){
	m_stack = rhs.m_stack;
	m_max_size = rhs.m_max_size;
	m_stack_pointer = rhs.m_stack_pointer;
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
	if(!isFull()){
		m_stack[m_stack_pointer++] = data;
	}else{
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
T const& Stack<T>::Pop(){
	if(isEmpty()){
		throw Exception("Cannot Pop: Stack Underflow");
	}
	return (m_stack[(m_stack_pointer--)-1]);
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
unsigned Stack<T>::Size(){
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
bool Stack<T>::isEmpty(){
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
bool Stack<T>::isFull(){
	return (m_max_size == m_stack_pointer);
}