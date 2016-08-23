/************************************************************************
* Class: Queue
*
* Purpose: This class represents a array based queue. It supports enqueuing 
*	as well as dequeuing, and methods to "peek" at top of queue, and several 
*	short helper functions.
*
* Manager functions:	
* 	Queue(int max_size)
*		Creates a queue with given max_size
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
*	isFull()
*		Returns bool representing if queue is full
*************************************************************************/
#pragma once

#include "Array.h"
#include "Exception.h"

template <class T>
class Queue{
	private:
		Array<T> m_queue;
		unsigned m_max_size;
	public:
		Queue(int max_size);
		Queue(Queue<T> const& copy);
		~Queue();

		Queue<T> const& operator=(Queue<T> const& rhs);
		void Enqueue(T const& data);
		T const& Dequeue();
		T & Front();
		unsigned Size();
		bool isEmpty();
		bool isFull();
};

/**********************************************************************	
* Purpose: 1arg constructor for queue. 
*
* Entry:
*	Parameters:
*		max_size: maximum size of the queue
*
* Exit: Constructs a queue with the above settings.
************************************************************************/
template <class T>
Queue<T>::Queue(int max_size) : m_max_size(max_size) {
	m_queue.setLength(0);
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
Queue<T>::Queue(Queue<T> const& copy) : m_queue(copy.m_queue), m_max_size(copy.m_max_size) {}


/**********************************************************************	
* Purpose: destructor for queue. 
*
* Entry: None.
*
* Exit: Resets queue to default and destroys any required memory
************************************************************************/
template <class T>
Queue<T>::~Queue(){
	m_queue.setLength(0);
	m_max_size = 0;
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
	m_max_size = rhs.m_max_size;
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
	if(isFull()){
		throw Exception("Can't Enqueue(); Queue is full.");
	}
	
	int current_length = m_queue.getLength();
	m_queue.setLength(current_length+1);
	m_queue[current_length] = data;
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
	int current_length = m_queue.getLength();
	T item = m_queue[0];

	// remove from the array by making a new array w/o that element
	Array<T> new_queue(current_length-1, 0);
	for(int i=0; i < current_length-1; ++i){
		new_queue[i] = m_queue[i+1];
	}
	m_queue = new_queue;

	return item;
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
	return m_queue[0];
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
	return m_queue.getLength();
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
	return !m_queue.getLength();
}

/**********************************************************************	
* Purpose: Helper function to determine if queue is full.
*
* Entry: None.
*
* Exit: Returns bool representing if the queue is full.
************************************************************************/
template <class T>
bool Queue<T>::isFull(){
	return m_queue.getLength() == m_max_size;
}