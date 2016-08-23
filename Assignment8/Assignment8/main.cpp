/***********************************************************
* Author:		Andrew Sparkes
* Title:		CST 211 Assignment 8
* Filename:		main.cpp
* Date Created:	5-2-12
* Modified:		5-3-12 : documentation, small tweaks
*
* Overview:
*	This program is a driver demonstrating the basic 
*	capabilities of array-based queue class
*
* Input:
*	None.
*
* Output:
*	Will output a basic test of the array-based queue class.
************************************************************/
#include <iostream>
using std::cout;
using std::endl;

#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

#include "Queue.h"
#include "Exception.h"

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	cout << "Setting up a queue of ints of length 3..." << endl;
	Queue<int> queue(3);

	cout << "Queue is " << (queue.isEmpty()?"empty":"not empty") << ". Queue is " << (queue.isFull()?"full":"not full") << ". Queue currently has " << queue.Size() << " items." << endl;

	cout << "Enqueue(123)" << endl;
	queue.Enqueue(123);

	cout << "Queue is " << (queue.isEmpty()?"empty":"not empty") << ". Queue is " << (queue.isFull()?"full":"not full") << ". Queue currently has " << queue.Size() << " items." << endl;

	cout << "Enqueue(456)" << endl;
	queue.Enqueue(456);

	cout << "Queue is " << (queue.isEmpty()?"empty":"not empty") << ". Queue is " << (queue.isFull()?"full":"not full") << ". Queue currently has " << queue.Size() << " items." << endl;

	cout << "Enqueue(789)" << endl;
	queue.Enqueue(789);

	cout << "Queue is " << (queue.isEmpty()?"empty":"not empty") << ". Queue is " << (queue.isFull()?"full":"not full") << ". Queue currently has " << queue.Size() << " items." << endl;

	try{
		cout << "Enqueue(123456)" << endl;
		queue.Enqueue(123456);
		
		cout << "Queue is " << (queue.isEmpty()?"empty":"not empty") << ". Queue is " << (queue.isFull()?"full":"not full") << ". Queue currently has " << queue.Size() << " items." << endl;
	}catch(Exception e){
		cout << "Exception: " << e << endl;
	}

	int dequeuedItem;

	cout << "Dequeue()" << endl;
	dequeuedItem = queue.Dequeue();
	cout << "Dequeued Item: " << dequeuedItem << endl;
	
	cout << "Queue is " << (queue.isEmpty()?"empty":"not empty") << ". Queue is " << (queue.isFull()?"full":"not full") << ". Queue currently has " << queue.Size() << " items." << endl;

	cout << "Dequeue()" << endl;
	dequeuedItem = queue.Dequeue();
	cout << "Dequeued Item: " << dequeuedItem << endl;
	
	cout << "Queue is " << (queue.isEmpty()?"empty":"not empty") << ". Queue is " << (queue.isFull()?"full":"not full") << ". Queue currently has " << queue.Size() << " items." << endl;

	cout << "Dequeue()" << endl;
	dequeuedItem = queue.Dequeue();
	cout << "Dequeued Item: " << dequeuedItem << endl;
	
	cout << "Queue is " << (queue.isEmpty()?"empty":"not empty") << ". Queue is " << (queue.isFull()?"full":"not full") << ". Queue currently has " << queue.Size() << " items." << endl;

	try{
		cout << "Dequeue()" << endl;
		dequeuedItem = queue.Dequeue();
		cout << "Dequeued Item: " << dequeuedItem << endl;
		
		cout << "Queue is " << (queue.isEmpty()?"empty":"not empty") << ". Queue is " << (queue.isFull()?"full":"not full") << ". Queue currently has " << queue.Size() << " items." << endl;
	}catch(Exception e){
		cout << "Exception: " << e << endl;
	}

	cout << "Queue is " << (queue.isEmpty()?"empty":"not empty") << ". Queue is " << (queue.isFull()?"full":"not full") << ". Queue currently has " << queue.Size() << " items." << endl;

	cout << "Now, enqueueing 123 and 456, and then changing the first item to 321..." << endl;
	queue.Enqueue(123);
	queue.Enqueue(456);
	queue.Front() = 321;

	cout << "Queue is " << (queue.isEmpty()?"empty":"not empty") << ". Queue is " << (queue.isFull()?"full":"not full") << ". Queue currently has " << queue.Size() << " items." << endl;

	cout << "Now, dequeuing the whole queue... (should see 321, 456)" << endl;

	cout << "Dequeue()" << endl;
	dequeuedItem = queue.Dequeue();
	cout << "Dequeued Item: " << dequeuedItem << endl;
	
	cout << "Queue is " << (queue.isEmpty()?"empty":"not empty") << ". Queue is " << (queue.isFull()?"full":"not full") << ". Queue currently has " << queue.Size() << " items." << endl;

	cout << "Dequeue()" << endl;
	dequeuedItem = queue.Dequeue();
	cout << "Dequeued Item: " << dequeuedItem << endl;
	
	cout << "Queue is " << (queue.isEmpty()?"empty":"not empty") << ". Queue is " << (queue.isFull()?"full":"not full") << ". Queue currently has " << queue.Size() << " items." << endl;
	system("pause");
	return 0;
}