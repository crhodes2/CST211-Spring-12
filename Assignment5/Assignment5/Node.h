/************************************************************************
* Class: Node
*
* Purpose: This class represents a node of a linked list.
*
* Manager functions:	
* 	Node(T* data, Node* prev, Node* next)
*		Creates a node with given prev, next pointers as well as data
*	Node(Node const& copy)
*		Copy constructor
*	~Node()
*		Destroys the node and its contents
*
* Methods:		
*	operator=(Node const& rhs)
*		Overloaded op= operator.
*	getData()
*		Returns the data the node holds.
*	
*************************************************************************/
#pragma once

template <class T>
class DoubleLinkedList;

template <class T>
class ForwardIterator;

template <class T>
class BackwardIterator;

template <class T>
class Node{
	friend class DoubleLinkedList<T>;
	friend class ForwardIterator<T>;
	friend class BackwardIterator<T>;
	private:
		Node* m_prev;
		Node* m_next;
		T* m_data;

		Node(T* data, Node<T>* prev, Node<T>* next);
		Node(Node<T> const& copy);
		Node<T> const& operator=(Node<T> const& rhs);
	public:
		~Node();
		T const& getData();
};

/**********************************************************************	
* Purpose: This function is the 3-arg constructor for the Node class. 
*		It sets the prev and next pointers as well as sets the data
*
* Entry:
*	Parameters:
*		data: The data to set inside the Node
*		prev: Pointer to the previous node
*		next: Pointer to the next node
*
* Exit: Constructs a Node with the given data, next, prev.
************************************************************************/
template <class T>
Node<T>::Node(T* data, Node* prev, Node* next) : m_data(data), m_prev(prev), m_next(next){}

/**********************************************************************	
* Purpose: Node class copy constructor
*
* Entry:
*	Parameters:
*		copy: The Node to copy from
*
* Exit: Constructs a Node with the same prev, next and data as the copy.
************************************************************************/
template <class T>
Node<T>::Node(Node const& copy) : m_prev(copy.m_prev), m_next(copy.m_next), m_data(new T){
	*m_data = *(copy.m_data);
}

/**********************************************************************	
* Purpose: Node class op=
*
* Entry:
*	Parameters:
*		rhs: The Node to copy from
*
* Exit: Constructs a Node with the same prev, next and data as the rhs.
************************************************************************/
template <class T>
Node<T> const& Node<T>::operator=(Node const& rhs){
	m_prev = rhs.m_prev;
	m_next = rhs.m_next;
	m_data = new T;
	*m_data = *(rhs.m_data);
}

/**********************************************************************	
* Purpose: Node class destructor
*
* Entry: None.
*
* Exit: Destroys current data and node and resets to default
************************************************************************/
template <class T>
Node<T>::~Node(){
	delete m_data;
	m_data = 0;
	m_prev = m_next = 0;
}

/**********************************************************************	
* Purpose: Returns the data contained by the node
*
* Entry: None
*
* Exit: Returns data
************************************************************************/
template <class T>
T const& Node<T>::getData(){
	return *m_data;
}