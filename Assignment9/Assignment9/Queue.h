/************************************************************************
* Class: Queue
*
* Purpose: This class represents a list based queue. It supports enqueuing 
*	as well as dequeuing, and methods to "peek" at top of queue, and several 
*	short helper functions.
*
* Manager functions:	
* 	Queue()
*		Creates a queue
*	Queue(Queue const& copy)
*		Copy constructor
*	~Queue()
*		Destructor
*
* Methods:		
*	operator=(Queue const&)
*		Assignment operator
*	Enqueue(T const&)
*		Enqueues data onto the queue
*	Dequeue()
*		Pops first element from queue and returns it
*	Front()
*		Returns reference to the top of the queue
*	Size()
*		Returns current count of items in queue
*	isEmpty()
*		Returns bool representing if queue is empty
*************************************************************************/
#pragma once

#include "DoubleLinkedList.h"
#include "Exception.h"

template <class T>
class Queue{
	private:
		DoubleLinkedList<T> m_queue;
		unsigned m_size;
	public:
		Queue();
		Queue(Queue<T> const& copy);
		~Queue();

		Queue<T> const& operator=(Queue<T> const& rhs);
		void Enqueue(T const& data);
		T const& Dequeue();
		T & Front();
		unsigned Size();
		bool isEmpty();
};

/**********************************************************************	
* Purpose: 1arg constructor for queue. 
*
* Entry: None.
*
* Exit: Constructs a queue with the above settings.
************************************************************************/
template <class T>
Queue<T>::Queue() : m_size(0) {
}

/**********************************************************************	
* Purpose: copy constructor for queue. 
*
* Entry:
*	Parameters:
*		cppy: the queue to copy from
*
* Exit: Constructs a queue with the same settings as copy.
************************************************************************/
template <class T>
Queue<T>::Queue(Queue<T> const& copy) : m_queue(copy.m_queue), m_size(copy.m_size) {}


/**********************************************************************	
* Purpose: destructor for queue. 
*
* Entry: None.
*
* Exit: Resets queue to default and destroys any required memory
************************************************************************/
template <class T>
Queue<T>::~Queue(){
	m_queue.Purge();
	m_size = 0;
}

/**********************************************************************	
* Purpose: Assignment operator for queues
*
* Entry:
*	Parameters:
*		rhs: The queue on the right hand side
*
* Exit: Current queue now shares settings/data with rhs.
************************************************************************/
template <class T>
Queue<T> const& Queue<T>::operator=(Queue<T> const& rhs){
	m_queue = rhs.m_queue;
	m_size = rhs.m_size;
}

/**********************************************************************	
* Purpose: Enqueues data onto the queue.
*
* Entry:
*	Parameters:
*		data: the item to enqueue
*
* Exit: data is next in queue.
************************************************************************/
template <class T>
void Queue<T>::Enqueue(T const& data){
	m_queue.Append(data);
	m_size++;
}

/**********************************************************************	
* Purpose: Dequeues an item from the queue.
*
* Entry: None.
*
* Exit: Returns the first element of the queue and removes it from queue.
************************************************************************/
template <class T>
T const& Queue<T>::Dequeue(){
	if(isEmpty()){
		throw Exception("Can't Dequeue(); Queue is empty.");
	}
	T front = m_queue.First();
	m_queue.Extract(front);
	m_size--;
	return front;
}

/**********************************************************************	
* Purpose: Used to retrieve/change the front item in queue.
*
* Entry: None.
*
* Exit: Returns reference to front of queue.
************************************************************************/
template <class T>
T & Queue<T>::Front(){
	if(isEmpty()){
		throw Exception("Can't return Front; Queue is empty.");
	}
	return const_cast<T&>(m_queue.First());
}

/**********************************************************************	
* Purpose: Returns current size of queue.
*
* Entry: None.
*
* Exit: Returns current size of queue.
************************************************************************/
template <class T>
unsigned Queue<T>::Size(){
	return m_size;
}

/**********************************************************************	
* Purpose: Helper function to determine if queue is empty.
*
* Entry: None.
*
* Exit: Returns bool representing if the queue is empty.
************************************************************************/
template <class T>
bool Queue<T>::isEmpty(){
	return !m_size;
}