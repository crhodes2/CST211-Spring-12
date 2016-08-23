/***********************************************************
* Author:		Andrew Sparkes
* Lab Number:	CST 211 Assignment 5
* Filename:		main.cpp
* Date Created:	5-3-12
* Modifications:	5-6-12 fixed issues relating to ++, tweaks
*
* Overview:
*	This program demos iterators, both forward and backward 
*	for a double linked list
* Input:
*	None.
*
* Output:
*	Output is written to console.
************************************************************/
#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include "ForwardIterator.h"
#include "BackwardIterator.h"
#include "DoubleLinkedList.h"

#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	DoubleLinkedList<int> list;
	list.Append(1);
	list.Append(2);
	list.Append(3);

	// vanilla demo of iterator
	ForwardIterator<int> fit(&list, list.getHead());
	while( !fit.IsDone() ){
		cout << fit.GetCurrent() << endl;
		fit.MoveNext();
	}

	// demo of iterator after resetting it
	fit.Reset();
	while( !fit.IsDone() ){
		cout << fit.GetCurrent() << endl;
		fit.MoveNext();
	}
	
	// for loop variant
	for(ForwardIterator<int> t(&list, list.getHead()); !t.IsDone(); t.MoveNext()){
		cout << t.GetCurrent() << endl;
	}

	// emulating the stl iterator
	for(ForwardIterator<int> t = list.begin(); t != list.end(); ++t){
		cout << *t << endl;
	}

	cout << "--------------------------------------------------------" << endl;
	
	// vanilla demo of iterator
	BackwardIterator<int> bit(&list, list.getTail());
	while( !bit.IsDone() ){
		cout << bit.GetCurrent() << endl;
		bit.MoveNext();
	}

	// demo of iterator after resetting it
	bit.Reset();
	while( !bit.IsDone() ){
		cout << bit.GetCurrent() << endl;
		bit.MoveNext();
	}
	
	// for loop variant
	for(BackwardIterator<int> t(&list, list.getTail()); !t.IsDone(); t.MoveNext()){
		cout << t.GetCurrent() << endl;
	}

	// emulating the stl iterator
	for(BackwardIterator<int> t = list.rbegin(); t != list.rend(); ++t){
		cout << *t << endl;
	}
	

	system("pause");
	return 0;
}